#include "IO.h"

IO::IO() {}

// Set MIDI Device Based on index in midiInputList and starts listening
void IO::setDevice(int index) {
  auto list = juce::MidiInput::getAvailableDevices();

  deviceManager.removeMidiInputDeviceCallback(list[lastInputIndex].identifier,
                                              this);

  auto newInput = list[index];

  if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
    deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);

  deviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
  midiInputList.setSelectedId(index + 1, juce::dontSendNotification);

  lastInputIndex = index;
}

// Handle incoming MIDI Msg
void IO::handleMsg(juce::MidiInput *source, const juce::MidiMessage &message) {
  const juce::ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput,
                                                      true);
  keyboardState.processNextMidiEvent(message);
  postMsg(message, source->getName());
}

// Post incoming MIDI Msg
void IO::postMsg(const juce::MidiMessage &message, const juce::String &source) {
  (new IncomingMessageCallback(this, message, source))->post();
}

// Adding the incoming Msg
void IO::addMsgtoList(const juce::MidiMessage &message,
                      const juce::String &source) {
  auto time = message.getTimeStamp() - startTime;

  auto hours = ((int)(time / 3600.0)) % 24;
  auto minutes = ((int)(time / 60.0)) % 60;
  auto seconds = ((int)time) % 60;
  auto millis = ((int)(time * 1000.0)) % 1000;

  auto timecode = juce::String::formatted("%02d:%02d:%02d.%03d", hours, minutes,
                                          seconds, millis);

  auto description = getMsgDesc(message);

  juce::String midiMessageString(timecode + "  -  " + description + " (" +
                                 source + ")");
  logMsg(midiMessageString);
}

// Log the incoming MIDI Msg into the MsgBox.
void IO::logMsg(const juce::String &m) {
  midiMessagesBox.moveCaretToEnd();
  midiMessagesBox.insertTextAtCaret(m + juce::newLine);
}

// Concatencate a Description of the MIDI Event.
static juce::String IO::getMsgDesc(const juce::MidiMessage &m) {
  if (m.isNoteOn())
    return "Note on " +
           juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
  if (m.isNoteOff())
    return "Note off " +
           juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
  if (m.isProgramChange())
    return "Program change " + juce::String(m.getProgramChangeNumber());
  if (m.isPitchWheel())
    return "Pitch wheel " + juce::String(m.getPitchWheelValue());
  if (m.isAftertouch())
    return "After touch " +
           juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true,
                                              3) +
           ": " + juce::String(m.getAfterTouchValue());
  if (m.isChannelPressure())
    return "Channel pressure " + juce::String(m.getChannelPressureValue());
  if (m.isAllNotesOff())
    return "All notes off";
  if (m.isAllSoundOff())
    return "All sound off";
  if (m.isMetaEvent())
    return "Meta event";

  if (m.isController()) {
    juce::String name(
        juce::MidiMessage::getControllerName(m.getControllerNumber()));

    if (name.isEmpty())
      name = "[" + juce::String(m.getControllerNumber()) + "]";

    return "Controller " + name + ": " + juce::String(m.getControllerValue());
  }

  return juce::String::toHexString(m.getRawData(), m.getRawDataSize());
}
