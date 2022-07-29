/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1024, 800);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }  

    addAndMakeVisible(deckGUI1); 
    addAndMakeVisible(deckGUI2);  

    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);

    addAndMakeVisible(playlist);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();


}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    //mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

 }
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


    //deck1.setFont(juce::Font(16.0f, juce::Font::bold));
    //deck1.setText("Deck 1", juce::dontSendNotification);
    //deck1.setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    //deck1.setJustificationType(juce::Justification::centred);

    //deck2.setFont(juce::Font(16.0f, juce::Font::bold));
    //deck2.setText("Deck 2", juce::dontSendNotification);
    //deck2.setColour(juce::Label::textColourId, juce::Colours::ghostwhite);
    //deck2.setJustificationType(juce::Justification::centred);
}

void MainComponent::resized()
{
                                                                                // Deck Component located on the top half Deck 1 on the left Deck 2 on the roight
    deckGUI1.setBounds(0, 0, getWidth()/2, getHeight()/2);
    deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()/2);
                                                                                //SoundTrack playlist on the buttom
    playlist.setBounds(0, getHeight()/2, getWidth(), getHeight() / 2);


}
