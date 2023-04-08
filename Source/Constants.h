#pragma once

#include <JuceHeader.h>

class Constants
{
public:
	static juce::NamedValueSet& getConstants()
	{
		static juce::NamedValueSet constants;
		if (constants.isEmpty())
		{
			constants.set("PI", 3.14159);
			constants.set("GRAVITY", 9.81);
		}
		return constants;
	}

	inline static const juce::StringArray NOISE_OPTIONS = {
		"WhiteNoise","PinkNoise(Unimplemented)"
	};

	inline static const struct PARAMETER_ID {
		using String = juce::String;
		inline static const String GAIN_ID = "GAIN_ID";
		inline static const String NOISE_TYPE_ID = "NOISE_TYPE_ID";
	};

	inline static const struct PARAMETER_NAME {
		using String = juce::String;
		inline static const String GAIN_NAME = "Gain";
		inline static const String NOISE_TYPE_NAME = "NOISE Type";
	};

	struct PARAMETER {
		using String = juce::String;
		String id;
		String name;

		PARAMETER() = default;

		PARAMETER(const String& id, const String& name)
			: id(id), name(name) {}
	};

	inline static juce::Array<PARAMETER> createControlsArray() {
		juce::Array<PARAMETER> controls;
		controls.add({ PARAMETER_ID::GAIN_ID, PARAMETER_NAME::GAIN_NAME });
		controls.add({ PARAMETER_ID::NOISE_TYPE_ID, PARAMETER_NAME::NOISE_TYPE_NAME });
		return controls;
	}

	inline static const juce::Array<PARAMETER> CONTROLS = createControlsArray();
};

//double pi = Constants::getConstants()["PI"];
//double g = Constants::getConstants()["GRAVITY"];