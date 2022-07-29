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

/// <summary>
/// Constructor of WaveformDisplay
/// </summary>
WaveformDisplay::WaveformDisplay(
                            juce::AudioFormatManager& formatManagerToUse,               // Keeps a list of available audio formats
                            juce::AudioThumbnailCache& cacheToUse) :                    // Manages multiple waveForms
                            audioThumb(1000, formatManagerToUse, cacheToUse),           // Scales view of soundtrack waveform
                            fileLoaded(false),                                          // Starts with no loaded file
                            position(0)                                                 // Initial Position of the SoundTrack position marker
{
                                                                                        // add the change listener to waveform
    audioThumb.addChangeListener(this);
}


/// <summary>
/// Destructor of WaveformDisplay
/// </summary>
WaveformDisplay::~WaveformDisplay()
{
}



/// <summary>
/// Paint is only called when the window is resized or when u recall repaint
/// </summary>
void WaveformDisplay::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));  // Clear the background

    g.setColour(juce::Colours::grey);                                                   // Selected Colour
    g.drawRect(getLocalBounds(), 1);                                                    // Draw an outline around the component

    g.setColour(juce::Colours::ghostwhite);                                                 // Selected Colour
    
    if (fileLoaded)                                                                     // If the file is loaded draw the waveForm
    {
        audioThumb.drawChannel(g,                                                       // Graphics
                 getLocalBounds(),                                                      // Area
                 0,                                                                     // StartTimeSeconds
                 audioThumb.getTotalLength(),                                           // EndTimeSeconds
                 0,                                                                     // ChannelNum,
                 1.0f                                                                   // VerticalZoomFactor
            );

        g.setColour(juce::Colours::lightgreen);                                         // Selected Colour                                     
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());             // SoundTrack position marker
    }
    else                                                                                // Else if the file is not loaded, print message
    {
        g.setFont(26.0f);                                                               // Font Size
        g.drawText(                                                                     // Message
            "Please load a file...", 
            getLocalBounds(),                                                           // Size of the section
            juce::Justification::centred, true);                                        // justified in the centre
    }
}

void WaveformDisplay::resized()                                                         // Size of the components already set in the paint function
{
}

void WaveformDisplay::loadURL(juce::URL audioURL)                                       // Loads the file
{
    audioThumb.clear();                                                                 //Clears out any stored thumbnails.
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));              // Specifies stream that contains the audio file.
    if (fileLoaded)
    {
        repaint();                                                                      // If the file is loaded we print a new qwaveform
    }
    else {
        DBG("WaveformDisplay::loadURL: not loaded!");                                   // if not we display a error message in the Immediate Window
    }

}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)           // Receives change event callbacks that are sent out by a ChangeBroadcaster
{
     repaint();
}

void WaveformDisplay::setPositionRelative(double pos)                                   // Position the audio head in the audio file
{
    if (pos != position && pos > 0)
    {
        position = pos;
        repaint();
    }
}
