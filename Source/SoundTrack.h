/*
  ==============================================================================

    SoundTrack.h
    Created: 26 Jul 2022 9:12:00pm
    Author:  Diogo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/// <summary>
/// Initialization of a SoundTrack class with following attributes
/// </summary>
class SoundTrack {
public:
    SoundTrack(juce::File _file);                       // Constructor takes in the file
    juce::File file;                                    // The file loaded
    juce::String fileTitle;                             // Name of the song
    juce::String duration;                              // Duration of the song
    juce::String fileType;                              // Type of file
    juce::URL fileURL;                                  // Source on the playlist
};
