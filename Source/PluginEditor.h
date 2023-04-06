/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Control.h"
//==============================================================================
/**
*/
class TestSignalAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	TestSignalAudioProcessorEditor(TestSignalAudioProcessor& p, AudioProcessorValueTreeState& apvts);
	~TestSignalAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	TestSignalAudioProcessor& audioProcessor;
	AudioProcessorValueTreeState& apvts;
	std::unique_ptr<ComboBoxAttachment> noiseTypeAttachment;
	ComboBox noiseTypeComboBox;
	Control gainControl;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestSignalAudioProcessorEditor)
};
