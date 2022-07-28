/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 24 Jul 2022 4:24:33pm
    Author:  Diogo

  ==============================================================================
*/

#include "JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(
                            juce::AudioFormatManager& formatManagerToUse,
                            juce::AudioThumbnailCache& cacheToUse) :
                            audioThumb(1000, formatManagerToUse, cacheToUse),
                            fileLoaded(false),
                            position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::orange);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f
        );
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont(20.0f);
        g.drawText(
            "File not loaded...", 
            getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        repaint();
    }
    else {
        DBG("WaveformDisplay::loadURL: not loaded!");
    }

}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
     repaint();
}

/* Position the audio head in the audio file */
void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && pos > 0)
    {
        position = pos;
        repaint();
    }
}
