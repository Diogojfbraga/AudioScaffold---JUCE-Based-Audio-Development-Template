/*
  ==============================================================================

    WaveformDisplay.h
    Created: 24 Jul 2022 4:24:33pm
    Author:  Diogo

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener
{
public:
    WaveformDisplay(
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);

    ~WaveformDisplay();

    void paint(juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    /** Renders the Waveform based on input file URL */
    void loadURL(juce::URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded; // Flag to determine if waveform can be rendered 
    double position; // Position of the audio head within the waveform 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
