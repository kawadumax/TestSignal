#pragma once

#include <JuceHeader.h>
using namespace juce;

class Control
{
public:
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	Control(std::unique_ptr<juce::Slider> slider, std::unique_ptr<juce::Label> label, std::unique_ptr<SliderAttachment> attachment)
		: slider(std::move(slider)), label(std::move(label)), attachment(std::move(attachment))
	{
	}

	Control() {}

	void initialize(std::unique_ptr<juce::Slider> _slider, std::unique_ptr<juce::Label> _label, std::unique_ptr<SliderAttachment> _attachment)
	{
		this->slider = std::move(_slider);
		this->label = std::move(_label);
		this->attachment = std::move(_attachment);
	};

	std::unique_ptr<juce::Slider> slider;
	std::unique_ptr<juce::Label> label;
	std::unique_ptr<SliderAttachment> attachment;
};