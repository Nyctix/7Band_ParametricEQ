#pragma once

#include <JuceHeader.h>

namespace Gui
{
	class WhiteMeter : public juce::Component
	{
	public:

		void paint(juce::Graphics& g) override
		{
			auto bounds = getLocalBounds().toFloat();

			g.setColour(juce::Colours::white.withBrightness(0.4f));
			g.fillRoundedRectangle(bounds, 5.f);

			g.setColour(juce::Colours::white);

			const auto scaledY = juce::jmap(level, -60.f, 6.0f, 0.f, static_cast<float>(getHeight()));
			g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5.f);

		}

		void setLevel(const float value)
		{
			level = value;
		}

	private:
		float level = -60.f;

	};
}