#pragma once

#include "USB-MIDI_Namespace.h"

BEGIN_USBMIDI_NAMESPACE

using namespace MIDI_NAMESPACE;

// from https://www.usb.org/sites/default/files/midi10.pdf
// 4 USB-MIDI Event Packets
// Table 4-1: Code Index Number Classifications

static uint8_t type2cin[][2] = { {InvalidType,0}, {NoteOff,8}, {NoteOn,9}, {AfterTouchPoly,0xA}, {ControlChange,0xB}, {ProgramChange,0xC}, {AfterTouchChannel,0xD}, {PitchBend,0xE} };

static uint8_t system2cin[][2] = { {SystemExclusive,0}, {TimeCodeQuarterFrame,2}, {SongPosition,3}, {SongSelect,2}, {0,0}, {0,0}, {TuneRequest,5}, {SystemExclusiveEnd,0}, {Clock,0xF}, {0,0}, {Start,0xF}, {Continue,0xF}, {Stop,0xF}, {0,0}, {ActiveSensing,0xF}, {SystemReset,0xF} };

static byte cin2Len[][2] = { {0,0}, {1,0}, {2,2}, {3,3}, {4,0}, {5,0}, {6,0}, {7,0}, {8,3}, {9,3}, {10,3}, {11,3}, {12,2}, {13,2}, {14,3}, {15,1} };

#define GETCABLENUMBER(packet) (packet.header >> 4);
#define GETCIN(packet) (packet.header & 0x0f);
#define MAKEHEADER(cn, cin) (((cn & 0x0f) << 4) | cin)
#define RXBUFFER_PUSHBACK1 { mRxBuffer[mRxLength++] = mPacket.byte1; }
#define RXBUFFER_PUSHBACK2 { mRxBuffer[mRxLength++] = mPacket.byte1; mRxBuffer[mRxLength++] = mPacket.byte2; }
#define RXBUFFER_PUSHBACK3 { mRxBuffer[mRxLength++] = mPacket.byte1; mRxBuffer[mRxLength++] = mPacket.byte2; mRxBuffer[mRxLength++] = mPacket.byte3; }

#define RXBUFFER_POPFRONT(byte) auto byte = mRxBuffer[mRxIndex++]; mRxLength--;
#define SENDMIDI(packet) { MidiUSB.sendMIDI(packet); MidiUSB.flush(); }

END_USBMIDI_NAMESPACE
