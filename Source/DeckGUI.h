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


//==============================================================================
/*
*/
class DeckGUI : 
            public juce::Component,
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
                                                                                    // Component override
    void paint(juce::Graphics&) override;
    void resized() override;


    void buttonClicked(juce::Button*) override;                                     // Function that respondes to a button clicked and points to the correspondent button clicked


    void sliderValueChanged(juce::Slider* slider) override;                         // Function that takes the slider value

    bool isInterestedInFileDrag(const juce::StringArray& files) override;           // Fmplement file draganddrop to drag and load files
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    void timerCallback() override;                                                  // Implement timer
    void loadFile(juce::URL audioURL);                                              // Function that loads the audio file directly to the decks
    
    void restartButton(juce::Button* button, juce::Slider* slider);                 // Function that restarts the audio file



private:
                                                                                    // Player Control buttons
    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    //juce::ArrowButton rewindButton{ "REWIND" , 0.5, juce::Colours::ghostwhite };
    //juce::ArrowButton forwardButton{ "FORWARD" , 0.0, juce::Colours::ghostwhite };
    juce::TextButton rewindButton{ "<<" };
    juce::TextButton forwardButton{ ">>" };
    juce::TextButton replayButton{ "REPEAT" };
    juce::TextButton muteButton{ "MUTE" };
                                                                                    // Sliders
    juce::Slider intervalSlider;
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
                                                                                    // Labels            
    juce::Label volumeLabel;
    juce::Label speedLabel;
    juce::Label posLabel;

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

