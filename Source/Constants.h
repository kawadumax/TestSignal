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

	inline static const juce::StringArray FILTER_OPTIONS = { "LowPass","HighPass", "BandPass",
				"Notch", "LowShelf" , "HighShelf", "Peaking" ,"AllPass"
	};

	inline static const struct PARAMETER_ID {
		using String = juce::String;
		inline static const String FREQUENCY_ID = "FREQUENCY_ID";
		inline static const String Q_ID = "Q_ID";
		inline static const String BANDWIDTH_ID = "BANDWIDTH_ID";
		inline static const String GAIN_ID = "GAIN_ID";
		inline static const String FILTER_TYPE_ID = "FILTER_TYPE_ID";
	};

	inline static const struct PARAMETER_NAME {
		using String = juce::String;
		inline static const String FREQUENCY_NAME = "Frequency";
		inline static const String Q_NAME = "Q";
		inline static const String BANDWIDTH_NAME = "Bandwidth";
		inline static const String GAIN_NAME = "Gain";
		inline static const String FILTER_TYPE_NAME = "Filter Type";
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
		controls.add({ PARAMETER_ID::FREQUENCY_ID, PARAMETER_NAME::FREQUENCY_NAME });
		controls.add({ PARAMETER_ID::Q_ID, PARAMETER_NAME::Q_NAME });
		controls.add({ PARAMETER_ID::BANDWIDTH_ID, PARAMETER_NAME::BANDWIDTH_NAME });
		controls.add({ PARAMETER_ID::GAIN_ID, PARAMETER_NAME::GAIN_NAME });
		return controls;
	}

	inline static const juce::Array<PARAMETER> CONTROLS = createControlsArray();
};

//double pi = Constants::getConstants()["PI"];
//double g = Constants::getConstants()["GRAVITY"];