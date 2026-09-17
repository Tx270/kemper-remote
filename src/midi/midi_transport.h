#pragma once
#include <Arduino.h>

void midiTransport_init();

void midiTransport_read();

void midiTransport_sendSysEx(const byte* payload, size_t len);

void midiTransport_sendProgramChange(byte program, byte channel);
void midiTransport_sendControlChange(byte cc, byte value, byte channel);

bool  midiTransport_hasReply();
byte* midiTransport_getReplyBuffer();
size_t  midiTransport_getReplyLength();
void  midiTransport_clearReply();