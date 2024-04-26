#include <Arduino.h>
#include <MIDI.h>

// Create a MIDI object
// MIDI_CREATE_DEFAULT_INSTANCE();

// Create a SerialMIDI instance
midi::SerialMIDI<HardwareSerial> serialMIDI(Serial2);

// Create a custom MIDI instance
midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> MIDI(serialMIDI);

// Callback function to handle Note On events
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Print the received note and velocity to the serial console
  Serial.print("Note On - Note: ");
  Serial.print(pitch);
  Serial.print(", Velocity: ");
  Serial.println(velocity);
}

void setup() {
  // Initialize serial for Console Monnitor
  Serial.begin(115200);

  // Initialize MIDI communication
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Set the callback for Note On events
  MIDI.setHandleNoteOn(handleNoteOn);
}

void loop() {
  // // Check for incoming MIDI messages
  // MIDI.read();

  // Send a loop of three notes with a short pause between each note
  int channel = 1; // MIDI channel 10 (zero-indexed)
  MIDI.sendNoteOn(60, 127, channel); // Note: C4, Velocity: 127
  delay(500);
  MIDI.sendNoteOff(60, 0, channel); // Turn off the note
  MIDI.sendNoteOn(62, 127, 2); // Note: D4, Velocity: 127
  delay(500);
  MIDI.sendNoteOff(62, 0, 2); // Turn off the note
  MIDI.sendNoteOn(64, 127, 3); // Note: E4, Velocity: 127
  delay(500);
  MIDI.sendNoteOff(64, 0, 3); // Turn off the note
  delay(1000); // Pause before repeating the loop
}