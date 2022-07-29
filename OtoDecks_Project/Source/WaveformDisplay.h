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

/// <summary>
/// // this class contains the logic and display for the waveform
/// </summary>
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener
{
public:
    WaveformDisplay(
        juce::AudioFormatManager& formatManagerToUse,                       // Keeps a list of available audio formats
        juce::AudioThumbnailCache& cacheToUse);                             // Manages multiple waveForms

    ~WaveformDisplay();

    void paint(juce::Graphics&) override;                                   // Graphics Component
    void resized() override;                                                // Rescaling of components on the application window

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;  // Listener to repaint whenever there has been a change to enable moving playhead

    void loadURL(juce::URL audioURL);                                       // Renders the Waveform based on input file URL

    void setPositionRelative(double pos);                                   // Set the relative position of the playhead

private:
    juce::AudioThumbnail audioThumb;                                        // Quickly draw scaled views of the waveform shape of an audio file
    bool fileLoaded;                                                        // Flag to determine if waveform can be rendered 
    double position;                                                        // Position of the audio head within the waveform 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
