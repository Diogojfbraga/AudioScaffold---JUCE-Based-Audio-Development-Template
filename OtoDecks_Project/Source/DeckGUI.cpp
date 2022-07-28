/*
  ==============================================================================

    DeckGUI.cpp
    Created: 24 Jul 2022 4:23:11pm
    Author:  Diogo

  ==============================================================================
*/

#include "JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse
) : player(_player),
waveformDisplay(formatManagerToUse, cacheToUse)
{



    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(rewindButton);
    addAndMakeVisible(rewindLabel);
    addAndMakeVisible(forwardButton);
    addAndMakeVisible(forwardLabel);
    //addAndMakeVisible(pauseButton);

    addAndMakeVisible(granularityLabel);

    addAndMakeVisible(granularitySlider);
    addAndMakeVisible(waveformDisplay);

    addAndMakeVisible(muteButton);


    addAndMakeVisible(trackName);
    addAndMakeVisible(loopButton);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    rewindButton.addListener(this);
    forwardButton.addListener(this);
    granularitySlider.addListener(this);

    muteButton.addListener(this);

    loopButton.addListener(this);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    speedSlider.setRange(0.0, 100.0);
    speedSlider.setValue(1.0);
    posSlider.setRange(0.0, 1.0);
    granularitySlider.setValue(0);
    granularitySlider.setRange(1.0, 10.0, 1.0);

    startTimer(500);

    rewindLabel.setText("REWIND", juce::dontSendNotification); // add REWIND as text to arrow button
    forwardLabel.setText("FORWARD", juce::dontSendNotification); // ditto but FORWARD

    rewindLabel.attachToComponent(&rewindButton, false);
    forwardLabel.attachToComponent(&forwardButton, false);
    granularityLabel.attachToComponent(&granularitySlider, true);

    granularityLabel.setText("Granularity", juce::dontSendNotification);

    muteButton.setClickingTogglesState(true);
    muteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkslategrey);

    //track name displayed on top of the deck is only readable
    trackName.setReadOnly(true);
    trackName.setTextToShowWhenEmpty("No track loaded", juce::Colours::orange);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("DeckGUI", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 11;
    auto sliderLeft = 1; // margin for sliders to fit labels


    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 2);

    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);

    trackName.setBounds((getWidth() / 7) * 2, 0, (getWidth() / 7) * 3, rowH);
    loopButton.setBounds((getWidth() / 7) * 5, 0, getWidth() / 7, rowH);

    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);

    rewindButton.setBounds(getWidth() / 2 -50, rowH *2.1, getWidth() / 14, rowH / 3);
    forwardButton.setBounds(getWidth() / 2 +50, rowH *2.1, getWidth() / 14, rowH/3);

    granularitySlider.setBounds(0, rowH * 8, getWidth() - sliderLeft - 36, rowH);
    muteButton.setBounds(0, rowH * 9, getWidth(), rowH);
    playButton.setBounds(0, rowH * 10, getWidth(), rowH);

    trackName.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);
    trackName.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);

}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
    if (button == &rewindButton) { // REWIND
        player->setPosition(player->getPositionAbsolute() - granularitySlider.getValue());
    }
    if (button == &forwardButton) { // FAST-FORWARD
        player->setPosition(player->getPositionAbsolute() + granularitySlider.getValue());
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags =
            juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                player->loadURL(juce::URL{ chooser.getResult() });
                // and now the waveformDisplay as well
                waveformDisplay.loadURL(juce::URL{ chooser.getResult() });

                trackName.setText(juce::URL{ chooser.getResult() }.getFileName(), juce::NotificationType::dontSendNotification);
            });
    }
    // Mutes the volume if on
    if (button == &muteButton)
    {
        if (muteButton.getToggleState())
        {
            player->setGain(0);
        }
        else
        {
            player->setGain(volSlider.getValue());
        }
    }
    // if (button == &loadButton)
    // {
    //     FileChooser chooser{"Select a file..."};
    //     if (chooser.browseForFileToOpen())
    //     {
    //         player->loadURL(URL{chooser.getResult()});
    //         waveformDisplay.loadURL(URL{chooser.getResult()});

    //     }


    // }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (const auto& filename : files)
    {
        auto audioURL = juce::URL{ juce::File{filename} };
        player->loadURL(audioURL);
        waveformDisplay.loadURL(audioURL);
        // Load only 1 file dropped then return
        // and do not process the rest of the files
        return;
    }
}

void DeckGUI::timerCallback()
{
    if (std::to_string(loopButton.getToggleState()) == "1") { //If loop button is checked
        if (player->getPositionRelative() >= 1) {// and the position more than 1 meaning it is the end of the audio file
            player->setPositionRelative(0); // Sets position back to the start of the audio file
            player->start(); // Plays the audio file
        }
    }

    if (std::to_string(loopButton.getToggleState()) == "0") { //If loop button is not checked
        if (player->getPositionRelative() >= 1) { //and the position more than 1 meaning it is the end of the audio file
            player->setPositionRelative(0); //Sets position back to the start of the audio file
            player->stop(); // Stops the audio file
        }
    }
    waveformDisplay.setPositionRelative(player->getPositionRelative()); //Every 100ms, updates the waveform display to show current timestamp for the audio file
}


void DeckGUI::playlistToDeckGUI() { //function rea

    std::ifstream file("playlist.txt"); //Opens playlist.txt which contains the audio file URL which the user loads from the playlist into the deck
    std::string str;
    std::getline(file, str);
    std::string URL = "file:///" + str; //adds file:/// to the audio file URL, which converts the URL into a file
    DBG(URL);
    juce::URL audioURL{ URL };
    player->loadURL(audioURL); //Loads the file into the DJAudioPlayer
    waveformDisplay.loadURL(audioURL); //Loads the file and returns the waveform of the audio file
    DBG(audioURL.getFileName());

    mtrackName = audioURL.getFileName(); //Gets the file name from the URL

    trackName.setText(mtrackName, juce::NotificationType::dontSendNotification);


}
