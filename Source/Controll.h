#pragma once

#include <JuceHeader.h>
using namespace juce;

class Controll
{
public:
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	Controll(std::unique_ptr<juce::Slider> slider, std::unique_ptr<juce::Label> label, std::unique_ptr<SliderAttachment> attachment)
		: slider(std::move(slider)), label(std::move(label)), attachment(std::move(attachment))
	{
	}

	std::unique_ptr<juce::Slider> slider;
	std::unique_ptr<juce::Label> label;
	std::unique_ptr<SliderAttachment> attachment;
};