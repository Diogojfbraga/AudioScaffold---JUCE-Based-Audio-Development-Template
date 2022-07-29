/*
  ==============================================================================

    SoundTrack.cpp
    Created: 26 Jul 2022 9:12:00pm
    Author:  Diogo

  ==============================================================================
*/

#include "SoundTrack.h"


/// <summary>
/// Definition of Sountrack prepares the data to be used in the components
/// </summary>
SoundTrack::SoundTrack(juce::File _file) :
    file(_file),                                        // File/track used
    fileTitle(_file.getFileNameWithoutExtension()),     // Returns the last part of the filename, without its file extension.
    fileType(_file.getFileExtension()),                 // Returns the type of file
    fileURL(juce::URL{ _file })                         // Track location in the current file
{
}



