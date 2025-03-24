/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Vocoder.h"

//==============================================================================
VocoderAudioProcessor::VocoderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true) // Modulator - Bus: 0 - input, Channels: 0 and 1
                       .withInput ("Sidechain", juce::AudioChannelSet::stereo(), true) // Carrier - Bus: 1 - input, Channels: 2 and 3
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true) // Output - Bus: 0 - output, Channels
     ), vocoder (Vocoder())
#endif
{
}

VocoderAudioProcessor::~VocoderAudioProcessor()
{
}

//==============================================================================
const juce::String VocoderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VocoderAudioProcessor::acceptsMidi() const
{
    return false;
}

bool VocoderAudioProcessor::producesMidi() const
{
    return false;
}

bool VocoderAudioProcessor::isMidiEffect() const
{
    return false;
}

double VocoderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VocoderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VocoderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VocoderAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VocoderAudioProcessor::getProgramName (int index)
{
    return {};
}

void VocoderAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VocoderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock), 2 };
    vocoder.prepare(spec);
}

void VocoderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VocoderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VocoderAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    int totalNumInputChannels  = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();
    juce::AudioBuffer<float>& modulator = getBusBuffer(buffer, true, 0);
    juce::AudioBuffer<float>& carrier = getBusBuffer(buffer, true, 1);
    juce::AudioBuffer<float>& output = getBusBuffer(buffer, false, 0);

    vocoder.process(carrier, modulator, output);
}

//==============================================================================
bool VocoderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VocoderAudioProcessor::createEditor()
{
    return new VocoderAudioProcessorEditor (*this);
}

//==============================================================================
void VocoderAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VocoderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocoderAudioProcessor();
}
