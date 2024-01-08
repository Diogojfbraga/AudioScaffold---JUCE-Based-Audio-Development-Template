/*
  ==============================================================================

    DeckGUI.cpp
    Created: 24 Jul 2022 4:23:11pm
    Author:  Diogo

  ==============================================================================
*/

#include "JuceHeader.h"
#include "DeckGUI.h"
#include "WaveformDisplay.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse
) : player(_player),
waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    playButton.addListener(this);

    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    addAndMakeVisible(rewindButton);
    rewindButton.addListener(this);

    addAndMakeVisible(forwardButton);
    forwardButton.addListener(this);

    addAndMakeVisible(replayButton);
    replayButton.addListener(this);


    addAndMakeVisible(muteButton);
    muteButton.addListener(this);
    muteButton.setClickingTogglesState(true);
    muteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkgrey);

    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72,32);
    volSlider.setRange(0.0, 1.0, 0.01);
    volSlider.setValue(0.5);
    
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 32);
    speedSlider.setRange(0.0, 100.0, 1.0);
    speedSlider.setValue(1.0);


    addAndMakeVisible(posSlider);
    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0, 0.01);

    addAndMakeVisible(intervalSlider);
    intervalSlider.addListener(this);
    intervalSlider.setValue(0);
    intervalSlider.setRange(1.0, 10.0, 1.0);

    addAndMakeVisible(waveformDisplay);

    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posLabel);


    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    //g.drawText("DeckGUI", getLocalBounds(),
    //    juce::Justification::centred, true);   // draw some placeholder text
    volumeLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    volumeLabel.setJustificationType(juce::Justification::left);

    speedLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    speedLabel.setJustificationType(juce::Justification::left);

    posLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    posLabel.setText("AudioTrack Position", juce::dontSendNotification);
    posLabel.setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    posLabel.setJustificationType(juce::Justification::left);


}

void DeckGUI::resized()
{
    double rowH = getHeight() / 6;
    //auto sliderLeft = 1; // margin for sliders to fit labels


    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 2);
    posSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    rewindButton.setBounds((getWidth() / 2) - (getWidth() / 4), rowH * 3, getWidth() / 12, rowH / 3);
    forwardButton.setBounds(getWidth() - (getWidth() / 3), rowH * 3, getWidth() / 12, rowH / 3);
    playButton.setBounds((getWidth() / 2) - ((getWidth() / 6)/2), rowH * 2.9, getWidth() / 6, rowH * 0.5);
    muteButton.setBounds(0, rowH * 3.5, getWidth() / 3, rowH * 0.5);
    stopButton.setBounds(getWidth() / 3, rowH * 3.5, getWidth() / 3, rowH * 0.5);
    replayButton.setBounds(getWidth()-(getWidth() / 3), rowH * 3.5, getWidth() / 3, rowH * 0.5);
    volSlider.setBounds(getWidth()/5, rowH * 4, getWidth() / 5, getWidth() / 5);
    speedSlider.setBounds(getWidth() - (getWidth() / 2.5), rowH * 4, getWidth() / 5, getWidth() / 5);


    volumeLabel.setBounds(getWidth() / 8, rowH * 4.65, getWidth() / 5, getWidth() / 5);
    speedLabel.setBounds(getWidth()/1.85, rowH * 4.65, getWidth() / 5, getWidth() / 5);
    posLabel.setBounds((getWidth() / 2) - ((getWidth() / 5) / 2), rowH*1.3 , getWidth() / 5, getWidth() / 5);

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
        player->setPosition(player->getPositionAbsolute() - intervalSlider.getValue());
    }
    if (button == &forwardButton) { // FAST-FORWARD
        player->setPosition(player->getPositionAbsolute() + intervalSlider.getValue());
    }
    if (button == &replayButton) {
        restartButton(&replayButton, &posSlider);
        player->start();
    }


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
    if (button == &replayButton) {

        restartButton(&replayButton, &posSlider);
        player->start();
    }
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
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
}


void DeckGUI::restartButton(juce::Button* button, juce::Slider* slider) {
    slider->setValue(0);
    //waveformDisplay.setPositionRelative(0);
}

void DeckGUI::loadFile(juce::URL audioURL) {
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}