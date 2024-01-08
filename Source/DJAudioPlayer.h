/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 24 Jul 2022 4:21:27pm
    Author:  Diogo

  ==============================================================================
*/


#pragma once

#include "JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource {
public:

    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);


    void start();
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();

    /** get the absolute position of the playhead (seconds) */
    double getPositionAbsolute();

    /** get length of audio file in seconds */
    double getLengthInSeconds();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};




