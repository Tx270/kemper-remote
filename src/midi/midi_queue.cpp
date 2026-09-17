#include "midi_queue.h"

static MidiCommand buffer[MIDI_QUEUE_SIZE];
static byte head = 0;  // next slot to pop
static byte tail = 0;  // next slot to push
static byte count = 0;

void midiQueue_init() { head = tail = count = 0; }

bool midiQueue_push(const MidiCommand& cmd) {
    if (count >= MIDI_QUEUE_SIZE) {
        Serial.println(F("[MidiQueue] Full, command dropped"));
        return false;
    }
    buffer[tail] = cmd;
    tail = (tail + 1) % MIDI_QUEUE_SIZE;
    count++;
    return true;
}

bool midiQueue_pop(MidiCommand& out) {
    if (count == 0) return false;
    out = buffer[head];
    head = (head + 1) % MIDI_QUEUE_SIZE;
    count--;
    return true;
}

bool midiQueue_isEmpty() { return count == 0; }