#include "midi_state_machine.h"
#include "midi_commands.h"
#include "midi_queue.h"
#include "midi_transport.h"
#include "../app/app_state.h"
#include <Arduino.h>

static const unsigned long REPLY_TIMEOUT_MS = 300;
static const unsigned long RIG_NAME_POLL_INTERVAL_MS = 1000;
static const byte RX_BUFFER_SIZE = 128;

enum MidiState : byte {
    STATE_IDLE,
    STATE_SENDING,
    STATE_AWAITING_REPLY,
    STATE_PARSING,
    STATE_ERROR
};

static MidiState     state          = STATE_IDLE;
static MidiCommand   currentCmd;
static unsigned long lastSendTime   = 0;
static unsigned long lastRigPoll    = 0;
static byte          rxBuffer[RX_BUFFER_SIZE];
static byte          rxLen          = 0;
static byte          retryCount     = 0;
static const byte    MAX_RETRIES    = 2;

static void enterSending(const MidiCommand& cmd);
static void tickSending();
static void tickAwaitingReply();
static void tickParsing();
static void tickError();
static MidiResponse parseSysExRigName(const byte* buf, byte len);
static void pushRigNameRequest();

void midiSM_init() {
    state        = STATE_IDLE;
    lastRigPoll  = millis();
    midiQueue_init();
    midiTransport_init();
}

void midiSM_update() {
    switch (state) {
        case STATE_IDLE: {
            unsigned long now = millis();
            if (now - lastRigPoll >= RIG_NAME_POLL_INTERVAL_MS) {
                lastRigPoll = now;
                pushRigNameRequest();
            }

            MidiCommand cmd;
            if (midiQueue_pop(cmd)) {
                enterSending(cmd);
            }
            break;
        }

        case STATE_SENDING:        tickSending();        break;
        case STATE_AWAITING_REPLY: tickAwaitingReply();  break;
        case STATE_PARSING:        tickParsing();        break;
        case STATE_ERROR:          tickError();          break;
    }
}

static void enterSending(const MidiCommand& cmd) {
    currentCmd   = cmd;
    retryCount   = 0;
    state        = STATE_SENDING;
}

static void tickSending() {
    switch (currentCmd.type) {

        case MIDI_CMD_NONE:
            state = STATE_IDLE;
            return;

        case MIDI_CMD_PROGRAM_CHANGE:
            midiTransport_sendProgramChange(currentCmd.data1, currentCmd.channel);
            state = STATE_IDLE;
            return;

        case MIDI_CMD_CONTROL_CHANGE:
            midiTransport_sendControlChange(
                currentCmd.data1, currentCmd.data2, currentCmd.channel);
            state = STATE_IDLE;
            return;

        case MIDI_CMD_SYSEX_RIG_NAME:
            midiTransport_clearReply();
            midiTransport_sendSysEx(
                KEMPER_RIG_NAME_REQUEST,
                KEMPER_RIG_NAME_REQUEST_LEN);
            lastSendTime = millis();
            state = STATE_AWAITING_REPLY;
            return;

        default:
            Serial.println(F("[MIDI] Unknown command type, skipping"));
            state = STATE_IDLE;
    }
}

static void tickAwaitingReply() {
    if (midiTransport_hasReply()) {
        rxLen = midiTransport_getReplyLength();
        if (rxLen > sizeof(rxBuffer)) {
            rxLen = sizeof(rxBuffer);
        }
        memcpy(rxBuffer, midiTransport_getReplyBuffer(), rxLen);
        midiTransport_clearReply();

        state = STATE_PARSING;
        return;
    }

    if (millis() - lastSendTime >= REPLY_TIMEOUT_MS) {
        Serial.println(F("[MIDI] Reply timeout"));
        state = STATE_ERROR;
    }
}

static void tickParsing() {
    if (currentCmd.type == MIDI_CMD_SYSEX_RIG_NAME) {
        MidiResponse resp = parseSysExRigName(rxBuffer, rxLen);
        if (resp.valid) {
            strncpy(appState.rigName, resp.text, sizeof(appState.rigName) - 1);
            appState.rigName[sizeof(appState.rigName) - 1] = '\0';
            appState.midiConnected = true;
            retryCount = 0;
        } else {
            Serial.println(F("[MIDI] Parse failed"));
            state = STATE_ERROR;
            return;
        }
    }
    state = STATE_IDLE;
}

static void tickError() {
    appState.midiConnected = false;

    if (retryCount < MAX_RETRIES) {
        retryCount++;
        Serial.print(F("[MIDI] Retrying (attempt "));
        Serial.print(retryCount);
        Serial.println(F(")"));
        state = STATE_SENDING;
    } else {
        Serial.println(F("[MIDI] Max retries reached, dropping command"));
        retryCount = 0;
        state = STATE_IDLE;
    }
}

static MidiResponse parseSysExRigName(const byte* buf, byte len) {
    MidiResponse resp;
    resp.valid   = false;
    resp.text[0] = '\0';

    const byte NAME_START = 10;

    if (len < NAME_START + 1) {
        Serial.println(F("[MIDI] SysEx reply too short"));
        return resp;
    }

    byte nameLen = 0;
    for (byte i = NAME_START; i < len && nameLen < (sizeof(resp.text) - 1); i++) {
        byte b = buf[i];
        
        if (b == 0xF7 || b == 0x00) {
            break;
        }

        if (b >= 0x20 && b <= 0x7E) {
            resp.text[nameLen++] = (char)b;
        }
    }

    resp.text[nameLen] = '\0';
    resp.valid = (nameLen > 0);

    return resp;
}

static void pushRigNameRequest() {
    MidiCommand cmd;
    cmd.type    = MIDI_CMD_SYSEX_RIG_NAME;
    cmd.channel = 0;
    cmd.data1   = 0;
    cmd.data2   = 0;
    midiQueue_push(cmd);
}