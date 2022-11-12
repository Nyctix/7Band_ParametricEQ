#pragma once

#include <JuceHeader.h>

namespace Gui
{
	class VisualMeter : public juce::Component, public juce::Timer
	{
	public:
		VisualMeter(std::function<float()>&& valuefunction) : valueSupplier(std::move(valuefunction))
		{
			startTimerHz(60);
			grill = juce::ImageCache::getFromMemory(BinaryData::MeterGrill_png, BinaryData::MeterGrill_pngSize);
		}

		void paint(juce::Graphics& g) override
		{
			const auto level = valueSupplier();
			auto bounds = getLocalBounds().toFloat().reduced(2.f);
			//For Gradient Meter
			g.setColour(juce::Colours::black);
			g.fillRect(bounds);

			g.setGradientFill(gradient);

			const auto scaledY = juce::jmap(level, -60.f, 6.0f, 0.f, static_cast<float>(getHeight()));
			g.fillRect(bounds.removeFromBottom(scaledY));
		}

		void paintOverChildren(juce::Graphics& g) override
		{
			g.drawImage(grill, getLocalBounds().toFloat());
		}

		void resized() override
		{
			const auto bounds = getLocalBounds().toFloat();
			gradient = juce::ColourGradient
			{
				juce::Colours::darkgreen,
				bounds.getBottomLeft(),
				juce::Colours::red,
				bounds.getTopLeft(),
				false
			};
			gradient.addColour(0.2, juce::Colours::green);
			gradient.addColour(0.4, juce::Colours::greenyellow);
			gradient.addColour(0.5, juce::Colours::yellow);
			gradient.addColour(0.7, juce::Colours::orange);
			gradient.addColour(0.9, juce::Colours::orangered);
		}

		void timerCallback() override
		{
			repaint();
		}

	private:
		std::function<float()> valueSupplier;
		juce::ColourGradient gradient{};
		juce::Image grill;

	};
}