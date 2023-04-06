/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
TestSignalAudioProcessorEditor::TestSignalAudioProcessorEditor(TestSignalAudioProcessor& p, AudioProcessorValueTreeState& apvts)
	: AudioProcessorEditor(&p), audioProcessor(p), apvts(apvts)
	//gainControl(
	//	std::make_unique<juce::Slider>(),
	//	std::make_unique<juce::Label>(),
	//	std::make_unique<SliderAttachment>()
	//)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	DBG("Editor Constructed");
	constexpr int width = 600;
	constexpr int height = 300;
	constexpr float centerX = width / 2;
	constexpr float centerY = height / 2;
	constexpr float fontSize = 14.0f;

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(width, height);

	// Create a ComboBox
	noiseTypeComboBox.addItemList(Constants::NOISE_OPTIONS, 1);
	noiseTypeComboBox.setBounds(10, 50, 100, 30);
	noiseTypeAttachment.reset(
		new ComboBoxAttachment(
			apvts,
			Constants::PARAMETER_ID::NOISE_TYPE_ID,
			noiseTypeComboBox
		)
	);

	//// Add the ComboBox to this component
	addAndMakeVisible(noiseTypeComboBox);

	auto slider = std::make_unique<juce::Slider>();
	slider->setRange(0.0, 1.0, 0.01);
	slider->setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 200, fontSize + 5);
	slider->setBounds(200, 200, 400, 400);

	//Make label for knobs
	auto label = std::make_unique<juce::Label>();
	label->setFont(juce::Font(fontSize));
	label->setText(Constants::PARAMETER_NAME::GAIN_NAME, juce::dontSendNotification);
	label->setJustificationType(juce::Justification::centred);
	label->setBounds(
		slider->getX(),
		slider->getBottom() - 5,
		slider->getWidth(),
		fontSize
	);

	addAndMakeVisible(slider.get());
	addAndMakeVisible(label.get());

	auto attachment = std::make_unique<SliderAttachment>(apvts, Constants::PARAMETER_ID::GAIN_ID, *slider);
	//attachment.reset(new SliderAttachment(apvts, Constants::PARAMETER_ID::GAIN_ID, *slider));

	// Add the slider, label, and attachment to a new Controll instance
	gainControl.initialize(std::move(slider), std::move(label), std::move(attachment));

}

TestSignalAudioProcessorEditor::~TestSignalAudioProcessorEditor()
{
}

//==============================================================================
void TestSignalAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void TestSignalAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
}
