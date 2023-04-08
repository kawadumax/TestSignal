/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

using PARAMETER_ID = Constants::PARAMETER_ID;

//==============================================================================
TestSignalAudioProcessor::TestSignalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	), apvts(*this, nullptr, "PARAMETERS", {
		std::make_unique<juce::AudioParameterChoice>(
			PARAMETER_ID::NOISE_TYPE_ID,
			"Noise Type",
			Constants::NOISE_OPTIONS,
			0
			),
		std::make_unique<juce::AudioParameterFloat>(
			PARAMETER_ID::GAIN_ID,
			"Gain",
			NormalisableRange<float>(0.0f, 1.0f, 0.01f),
			0.3
			),
		})
#endif
{
	apvts.addParameterListener(Constants::PARAMETER_ID::GAIN_ID, this);
}

TestSignalAudioProcessor::~TestSignalAudioProcessor()
{
}

//==============================================================================
const juce::String TestSignalAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool TestSignalAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool TestSignalAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool TestSignalAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double TestSignalAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int TestSignalAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int TestSignalAudioProcessor::getCurrentProgram()
{
	return 0;
}

void TestSignalAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String TestSignalAudioProcessor::getProgramName(int index)
{
	return {};
}

void TestSignalAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void TestSignalAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void TestSignalAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestSignalAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
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

void TestSignalAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.

	const int numChannels = buffer.getNumChannels();
	const int numSamples = buffer.getNumSamples();

	// �X�e���I�o�͂�z�肵�Ă��邽�߁A2�`�����l�����K�v�ł��B
	jassert(numChannels == 2);

	// �o�b�t�@�̓��e���N���A���܂��B
	buffer.clear();

	// ���E�̃`�����l���ɓ����z���C�g�m�C�Y���������݂܂��B
	for (int sample = 0; sample < numSamples; ++sample)
	{
		float noise = (random.nextFloat() * 2.0f - 1.0f) * gain; // -1.0 ���� 1.0 �͈̔͂Ń����_���Ȓl�𐶐�

		for (int channel = 0; channel < numChannels; ++channel)
		{
			buffer.setSample(channel, sample, noise);
		}
	}

}

//==============================================================================
bool TestSignalAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TestSignalAudioProcessor::createEditor()
{
	return new TestSignalAudioProcessorEditor(*this, apvts);
}

//==============================================================================
void TestSignalAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void TestSignalAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new TestSignalAudioProcessor();
}

// AudioProcessorValueTreeState::Listener �� parameterChanged ���I�[�o�[���C�h
void TestSignalAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
	// �p�����[�^���ύX���ꂽ�Ƃ��Ɏ��s����鏈���������ɏ���
	DBG("Parameter " << parameterID << " changed to " << newValue);
	if (parameterID == Constants::PARAMETER_ID::GAIN_ID) {
		gain = newValue;
	}
}