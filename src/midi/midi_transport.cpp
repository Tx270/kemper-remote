#include "midi_transport.h"
#include <USB.h>
#include <USBMIDI.h>

static USBMIDI MIDI;

static byte replyBuffer[256];
static size_t replyLen       = 0;
static bool replyReady       = false;
static bool sysexInProgress  = false;
static unsigned long lastHeartbeatTime = 0;

static void appendReplyByte(byte b) {
    if (replyLen < sizeof(replyBuffer)) {
        replyBuffer[replyLen++] = b;
    } else {
        Serial.println(F("[MIDI ERR] Reply buffer overflow"));
    }
}

void midiTransport_init() {
    MIDI.begin();
    USB.begin();
    delay(2000);
}

static void midiTransport_onRealtimeByte(byte statusByte) {
    if (statusByte == 0xFE) { // Active Sensing
        lastHeartbeatTime = millis();
    }
}

void midiTransport_read() {
    midiEventPacket_t packet;

    while (MIDI.readPacket(&packet)) {
        byte cin = packet.header & 0x0F;

        switch (cin) {
            case 0x4: // SysEx start or continue
                if (!sysexInProgress) {
                    replyLen        = 0;
                    sysexInProgress = true;
                }
                appendReplyByte(packet.byte1);
                appendReplyByte(packet.byte2);
                appendReplyByte(packet.byte3);
                break;

            case 0x5: // SysEx ends (1 byte) OR Single-byte Real-Time / Common
                if (packet.byte1 == 0xF7) {
                    if (sysexInProgress) {
                        appendReplyByte(packet.byte1);
                        sysexInProgress = false;
                        replyReady      = true;
                    }
                } else {
                    midiTransport_onRealtimeByte(packet.byte1);
                }
                break;

            case 0x6: // SysEx ends (2 bytes)
                if (sysexInProgress) {
                    appendReplyByte(packet.byte1);
                    appendReplyByte(packet.byte2);
                    sysexInProgress = false;
                    replyReady      = true;
                }
                break;

            case 0x7: // SysEx ends (3 bytes)
                if (sysexInProgress) {
                    appendReplyByte(packet.byte1);
                    appendReplyByte(packet.byte2);
                    appendReplyByte(packet.byte3);
                    sysexInProgress = false;
                    replyReady      = true;
                }
                break;

            case 0x0F: // Single Byte System Real-Time
                midiTransport_onRealtimeByte(packet.byte1);
                break;

            default:
                break;
        }
    }
}

bool midiTransport_isAlive() {
    return (millis() - lastHeartbeatTime) < 1000;
}

static void sendSysExPacketized(const byte* data, size_t length) {
    size_t pos = 0;

    while (pos < length) {
        size_t remaining = length - pos;
        midiEventPacket_t packet;
        packet.header = 0x00; // Cable 0

        if (remaining >= 3) {
            packet.header |= (remaining == 3) ? 0x07 : 0x04;
            packet.byte1 = data[pos++];
            packet.byte2 = data[pos++];
            packet.byte3 = data[pos++];
        } else if (remaining == 2) {
            packet.header |= 0x06;
            packet.byte1 = data[pos++];
            packet.byte2 = data[pos++];
            packet.byte3 = 0x00;
        } else { // remaining == 1
            packet.header |= 0x05;
            packet.byte1 = data[pos++];
            packet.byte2 = 0x00;
            packet.byte3 = 0x00;
        }

        MIDI.writePacket(&packet);
    }
}

void midiTransport_sendSysEx(const byte* payload, size_t len) {
    byte fullFrame[256];
    if (len + 2 > sizeof(fullFrame)) {
        Serial.println(F("[MIDI ERR] SysEx payload too large"));
        return;
    }

    fullFrame[0] = 0xF0;
    memcpy(&fullFrame[1], payload, len);
    fullFrame[len + 1] = 0xF7;

    sendSysExPacketized(fullFrame, len + 2);
}

void midiTransport_sendProgramChange(byte program, byte channel) {
    midiEventPacket_t packet = {
        0x0C,
        (uint8_t)(0xC0 | (channel & 0x0F)),
        program,
        0x00
    };
    MIDI.writePacket(&packet);
}

void midiTransport_sendControlChange(byte cc, byte value, byte channel) {
    midiEventPacket_t packet = {
        0x0B,
        (uint8_t)(0xB0 | (channel & 0x0F)),
        cc,
        value
    };
    MIDI.writePacket(&packet);
}

bool midiTransport_hasReply()        { return replyReady; }
byte* midiTransport_getReplyBuffer() { return replyBuffer; }
size_t midiTransport_getReplyLength()  { return replyLen; }
void midiTransport_clearReply()      { replyReady = false; replyLen = 0; }