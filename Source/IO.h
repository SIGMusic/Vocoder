#ifndef IO
#define IO

#include <JuceHeader.h>

class IO {
public:
  IO();
  void setDevice(int index);
  void handleMsg(juce::MidiInput *source, const juce::MidiMessage &message);

private:
  void postMsg(const juce::MidiMessage &message, const juce::String &source);
  void addMsgtoList(const juce::MidiMessage &message,
                    const juce::String &source);
  void logMsg(const juce::String &m);
  static juce::String getMsgDesc(const juce::MidiMessage &m);

  // This is used to dispach an incoming message to the message thread
  class IncomingMessageCallback : public juce::CallbackMessage {
  public:
    IncomingMessageCallback(MainContentComponent *o, const juce::MidiMessage &m,
                            const juce::String &s)
        : owner(o), message(m), source(s) {}

    void messageCallback() override {
      if (owner != nullptr)
        owner->addMsgtoList(message, source);
    }

    Component::SafePointer<MainContentComponent> owner;
    juce::MidiMessage message;
    juce::String source;
  };

  juce::AudioDeviceManager deviceManager;
  juce::ComboBox midiInputList;
  int lastInputIndex = 0;
  bool isAddingFromMidiInput = false;

  juce::MidiKeyboardState keyboardState;

  juce::TextEditor midiMessagesBox;
};

#endif // !IO
