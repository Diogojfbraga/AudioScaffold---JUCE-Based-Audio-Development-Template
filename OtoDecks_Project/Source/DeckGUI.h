/*
  ==============================================================================

    DeckGUI.h
    Created: 24 Jul 2022 4:23:11pm
    Author:  Diogo

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI();

    void paint(juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    void timerCallback() override;
    void playlistToDeckGUI(); // This function reads which audio file the user has selected to be added into either Deck 1 or 2

private:

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::TextButton muteButton{ "MUTE" };

    juce::ArrowButton rewindButton{ "REWIND" , 0.5, juce::Colours::lightgreen };
    juce::ArrowButton forwardButton{ "FORWARD" , 0.0, juce::Colours::lightgreen };

    juce::ToggleButton loopButton{ "LOOP" };

    juce::Slider granularitySlider;

    juce::TextEditor trackName;
    juce::String mtrackName;


    juce::Label rewindLabel;
    juce::Label forwardLabel;
    juce::Label granularityLabel;

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    juce::FileChooser fChooser{ "Select a file..." };


    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

