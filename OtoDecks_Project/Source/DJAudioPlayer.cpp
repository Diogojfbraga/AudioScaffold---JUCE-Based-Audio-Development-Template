/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 24 Jul 2022 4:21:27pm
    Author:  Diogo

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(
                    juce::AudioFormatManager& _formatManager)
                        : formatManager(_formatManager)
{

}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // audio-processing code goes here
    resampleSource.getNextAudioBlock(bufferToFill);

}
void DJAudioPlayer::releaseResources()
{
    // This will be called when the audio device stops
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    /* This function loads the file using its URL and attaches it to the audio source */
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        transportSource.start();
    }
    else {
        DBG("Something went wrong when loading the file");
    }
}
void DJAudioPlayer::setGain(double gain)
{
    //Volume slider
    if (gain < 0 || gain > 1.0)
    {
        DBG("DJAudioPlayer::setGain gain should be between 0 and 1.5 ");
    }
    else {
        transportSource.setGain(gain);
    }

}
void DJAudioPlayer::setSpeed(double ratio)
{
    //Speed slider
    if (ratio <= 0 || ratio > 100.0)
    {
        DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 1 ");
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    //track position slider
    transportSource.setPosition(posInSecs);
}

/// <summary>
/// function that sets the position in the tracker so that can be visible the position it is
/// </summary>
/// <param name="pos"></param>
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1 ");
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    if (transportSource.getLengthInSeconds()) {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
    else {
        return 0.0;
    }
}

double DJAudioPlayer::getPositionAbsolute()
{
    if (transportSource.getCurrentPosition()) {
        return transportSource.getCurrentPosition();
    }
    else {
        return 0.0;
    }
}

//function to get the total length in seconds of the audio file
double DJAudioPlayer::getLengthInSeconds()

{
    if (transportSource.getLengthInSeconds()) {
        return transportSource.getLengthInSeconds();
    }
    else {
        return 0.0;
    }
}