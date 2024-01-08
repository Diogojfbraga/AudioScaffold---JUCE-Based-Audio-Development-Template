/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 25 Jul 2022 12:11:51am
    Author:  Diogo

  ==============================================================================
*/

//#include <JuceHeader.h>
//#include "PlaylistComponent.h"
//#include <fstream>
//
//
////==============================================================================
//PlaylistComponent::PlaylistComponent(
//    DeckGUI* _deckGUI1,
//    DeckGUI* _deckGUI2,
//    DJAudioPlayer* _metaPlayer)
//    : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2), metaPlayer(_metaPlayer) {
//    addAndMakeVisible(loadButton);
//    addAndMakeVisible(searchbox);
//    addAndMakeVisible(tableComponent);
//    addAndMakeVisible(deck1Button);
//    addAndMakeVisible(deck2Button);
//    loadButton.addListener(this);
//    searchbox.addListener(this);
//    deck1Button.addListener(this);
//    deck2Button.addListener(this);
//    searchbox.setTextToShowWhenEmpty("Search SoudTracks", juce::Colours::ghostwhite);
//    searchbox.onReturnKey = [this] { search(searchbox.getText()); };
//    tableComponent.getHeader().addColumn("SoundTrack title", 1, 350);
//    tableComponent.getHeader().addColumn("Duration", 2, 100);
//    tableComponent.getHeader().addColumn("", 3, 50);
//    tableComponent.setModel(this);
//    addAndMakeVisible(tableComponent);
//    loadPlaylist();
//}
//
//PlaylistComponent::~PlaylistComponent()
//{
//    savePlaylist();
//}
//
//void PlaylistComponent::paint (juce::Graphics& g)
//{
//    /* This demo code just fills the component's background and
//       draws some placeholder text to get you started.
//
//       You should replace everything in this method with your own
//       drawing code..
//    */
//
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("PlaylistComponent", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
//}
//
//void PlaylistComponent::resized()
//{
//    //double rowW = getWidth() / 8;
//    double rowH = getHeight() / 5;
//
//    deck1Button.setBounds(0, 0, getWidth() / 3, rowH * 0.5);
//    loadButton.setBounds(getWidth() / 3, 0, getWidth() / 3, rowH * 0.5);
//
//    deck2Button.setBounds((getWidth() / 3) * 2, 0, getWidth() / 3, rowH * 0.5);
//    searchbox.setBounds(0, rowH*0.5, getWidth(), rowH*0.5);
//    tableComponent.setBounds(getWidth() / 2 - ((getWidth() / 2)/2), rowH, getWidth() / 2, getHeight());
//}
//
//int PlaylistComponent::getNumRows()
//{
//    return songs.size(); //tracjsize
//
//}
//void PlaylistComponent::paintRowBackground(juce::Graphics& g,
//    int rowNumber,
//    int width,
//    int height,
//    bool rowIsSelected)
//{
//    if (rowIsSelected)
//    {
//        g.fillAll(juce::Colours::slategrey);
//    }
//    else {
//        g.fillAll(juce::Colours::darkgrey);
//    }
//}
//
//void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
//    g.setFont(juce::Font(14.0f, juce::Font::bold));
//    g.setColour(juce::Colours::ghostwhite);
//    if (columnId == 1) {
//        g.drawText(songs[rowNumber].fileTitle,
//            2,
//            0,
//            width - 4,
//            height,
//            juce::Justification::centredLeft,
//            true);
//    }
//    if (columnId == 2) {
//        g.drawText(songs[rowNumber].duration,
//            2,
//            0,
//            width - 4,
//            height,
//            juce::Justification::centred,
//            true);
//    }
//}
//
//juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) {
//    if (columnId == 3) {
//        if (existingComponentToUpdate == nullptr) {
//            juce::TextButton* btn = new juce::TextButton{ "Remove" };
//            juce::String id{ std::to_string(rowNumber) };
//            btn->setComponentID(id);
//            btn->addListener(this);
//            existingComponentToUpdate = btn;
//        }
//    }
//    return existingComponentToUpdate;
//}
//
//void PlaylistComponent::buttonClicked(juce::Button* button) {
//    if (button == &loadButton) {
//        loadSongs();
//        tableComponent.updateContent();
//    }
//    else if (button == &deck1Button) {
//        loadToDeck(deckGUI1);
//    }
//    else if (button == &deck2Button) {
//        loadToDeck(deckGUI2);
//    }
//    else {
//        int id = std::stoi(button->getComponentID().toStdString());
//        deleteSongs(id);
//        tableComponent.updateContent();
//    }
//}
//
//void PlaylistComponent::loadSongs() {
//    juce::FileChooser chooser{ "Select file(s)" };
//    if (chooser.browseForMultipleFilesToOpen() || chooser.browseForFileToOpen()) {
//        for (const juce::File& file : chooser.getResults()) {
//            juce::String fileTitle{ file.getFileNameWithoutExtension() };
//            if (!isAdded(fileTitle)) { // if track not loaded yet in playlist
//                SoundTrack newTrack{ file };
//                juce::URL trackURL{ file };
//                newTrack.duration = timeToDisplay(trackURL);
//                songs.push_back(newTrack);
//            }
//            else { // display alert message if track is already loaded
//                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
//                    "Alert:",
//                    fileTitle + " is already added to playlist",
//                    "OK",
//                    nullptr
//                );
//            }
//        }
//    }
//}
//
//bool PlaylistComponent::isAdded(juce::String trackName) {
//    for (int i = 0; i < songs.size(); i++) {
//        if (songs[i].trackName == trackName) {
//            return true;
//        }
//        else if (i < songs.size()) {
//            continue;
//        }
//        else {
//            return false;
//        }
//    }
//}
//
//void PlaylistComponent::deleteSongs(int trackId) {
//    songs.erase(songs.begin() + trackId);
//}
//
//juce::String PlaylistComponent::timeToDisplay(juce::URL audioURL) {
//    metaPlayer->loadURL(audioURL);
//    double seconds{ metaPlayer->getLengthInSeconds() };
//    juce::String duration{ getTime(seconds) };
//    return duration;
//}
//
//juce::String PlaylistComponent::getTime(double seconds) {
//    int newSeconds{ int(std::round(seconds)) };
//    juce::String minute{ std::to_string(newSeconds / 60) };
//    juce::String sec{ std::to_string(newSeconds % 60) };
//    if (sec.length() < 2) {
//        //if seconds = 2, then add '0' in front to make it look more presentable and accurate
//        sec = sec.paddedLeft('0', 2);
//    }
//    return juce::String{ minute + ":" + sec }; //make it into string for formatting
//}
//
//void PlaylistComponent::search(juce::String searchText) {
//    if (searchText != "") {
//        for (int i = 0; i < songs.size(); i++) {
//            if (songs[i].fileTitle.contains(searchText)) {
//                tableComponent.selectRow(i);
//            }
//        }
//    }
//    else {
//        tableComponent.deselectAllRows();
//    }
//}
//
//void PlaylistComponent::savePlaylist() {
//    // outputs a .csv file stream to save playlist to be loaded later
//    std::ofstream musicPlaylist("musicPlaylist.csv");
//    // save library to file using "," for differentiating
//    for (SoundTrack& s : songs) {
//        musicPlaylist << s.file.getFullPathName() << "," << s.duration << "\n";
//    }
//}
//
//void PlaylistComponent::loadPlaylist() {
//    // calls input stream from saved playlist
//    std::ifstream musicPlaylist("musicPlaylist.csv");
//    std::string path;
//    std::string duration;
//    if (musicPlaylist.is_open()) {
//        while (getline(musicPlaylist, path, ',')) {
//            juce::File newFile{ path };
//            SoundTrack newTrack{ newFile };
//            getline(musicPlaylist, duration);
//            newTrack.duration = duration;
//            songs.push_back(newTrack);
//        }
//    }
//    musicPlaylist.close();
//}
//
//void PlaylistComponent::loadToDeck(DeckGUI* deckGUI) {
//    int songSelectedId{ tableComponent.getSelectedRow() };
//    if (songSelectedId != -1) {
//        deckGUI->loadFile(songs[songSelectedId].fileURL);
//    }
//    else {
//        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
//            "Alert:",
//            "Please select a song to load in deck",
//            "Close",
//            nullptr
//        );
//    }
//}

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <fstream>

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1,
    DeckGUI* _deckGUI2,
    DJAudioPlayer* _metaPlayer)
    : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2), metaPlayer(_metaPlayer) {
    addAndMakeVisible(loadButton);
    addAndMakeVisible(searchbox);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(deck1Button);
    addAndMakeVisible(deck2Button);
    loadButton.addListener(this);
    searchbox.addListener(this);
    deck1Button.addListener(this);
    deck2Button.addListener(this);
    searchbox.setTextToShowWhenEmpty("Search tracks", juce::Colours::grey);
    searchbox.onReturnKey = [this] { search(searchbox.getText()); };
    tableComponent.getHeader().addColumn("Track title", 1, 350);
    tableComponent.getHeader().addColumn("Time", 2, 100);
    tableComponent.getHeader().addColumn("", 3, 50);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
    loadPlaylist();
}

PlaylistComponent::~PlaylistComponent() {
    savePlaylist();
}

void PlaylistComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
}

void PlaylistComponent::resized() {
    //double rowW = getWidth() / 8;
    //double rowH = getHeight() / 7;
    //tableComponent.setBounds(0, 0, rowW * 5, getHeight());
    //loadButton.setBounds(rowW * 5, 0, rowW * 3, rowH * 2);
    //deck1Button.setBounds(rowW * 5, rowH * 2, rowW * 3, rowH * 2);
    //deck2Button.setBounds(rowW * 5, rowH * 4, rowW * 3, rowH * 2);
    //searchbox.setBounds(rowW * 5, rowH * 6, rowW * 3, rowH);
    //    //double rowW = getWidth() / 8;
    double rowH = getHeight() / 5;

    deck1Button.setBounds(0, 0, getWidth() / 3, rowH * 0.5);
    loadButton.setBounds(getWidth() / 3, 0, getWidth() / 3, rowH * 0.5);

    deck2Button.setBounds((getWidth() / 3) * 2, 0, getWidth() / 3, rowH * 0.5);
    searchbox.setBounds(0, rowH*0.5, getWidth(), rowH*0.5);
    tableComponent.setBounds(getWidth() / 2 - ((getWidth() / 2)/2), rowH, getWidth() / 2, getHeight());

}

int PlaylistComponent::getNumRows() {
    return songs.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(juce::Colours::cadetblue);
    }
    else {
        g.fillAll(juce::Colours::darkslategrey);
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.setColour(juce::Colours::lightcoral);
    if (columnId == 1) {
        g.drawText(songs[rowNumber].fileTitle,
            2,
            0,
            width - 4,
            height,
            juce::Justification::centredLeft,
            true);
    }
    if (columnId == 2) {
        g.drawText(songs[rowNumber].duration,
            2,
            0,
            width - 4,
            height,
            juce::Justification::centred,
            true);
    }
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) {
    if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{ "Delete" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button) {
    if (button == &loadButton) {
        loadSongs();
        tableComponent.updateContent();
    }
    else if (button == &deck1Button) {
        loadToDeck(deckGUI1);
    }
    else if (button == &deck2Button) {
        loadToDeck(deckGUI2);
    }
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        deleteSongs(id);
        tableComponent.updateContent();
    }
}

void PlaylistComponent::loadSongs() {
    juce::FileChooser chooser{ "Select file(s)" };
    if (chooser.browseForMultipleFilesToOpen() || chooser.browseForFileToOpen()) {
        for (const juce::File& file : chooser.getResults()) {
            juce::String trackName{ file.getFileNameWithoutExtension() };
            if (!isAdded(trackName)) { // if track not loaded yet in playlist
                SoundTrack newTrack{ file };
                juce::URL trackURL{ file };
                newTrack.duration = timeToDisplay(trackURL);
                songs.push_back(newTrack);
            }
            else { // display alert message if track is already loaded
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
                    "Alert:",
                    trackName + " is already added to playlist",
                    "OK",
                    nullptr
                );
            }
        }
    }
}

bool PlaylistComponent::isAdded(juce::String trackName) {
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].fileTitle == trackName) {
            return true;
        }
        else if (i < songs.size()) {
            continue;
        }
        else {
            return false;
        }
    }
}

void PlaylistComponent::deleteSongs(int trackId) {
    songs.erase(songs.begin() + trackId);
}

juce::String PlaylistComponent::timeToDisplay(juce::URL audioURL) {
    metaPlayer->loadURL(audioURL);
    double seconds{ metaPlayer->getLengthInSeconds() };
    juce::String time{ getTime(seconds) };
    return time;
}

juce::String PlaylistComponent::getTime(double seconds) {
    int newSeconds{ int(std::round(seconds)) };
    juce::String minute{ std::to_string(newSeconds / 60) };
    juce::String sec{ std::to_string(newSeconds % 60) };
    if (sec.length() < 2) {
        //if seconds = 2, then add '0' in front to make it look more presentable and accurate
        sec = sec.paddedLeft('0', 2);
    }
    return juce::String{ minute + ":" + sec }; //make it into string for formatting
}

void PlaylistComponent::search(juce::String searchText) {
    if (searchText != "") {
        for (int i = 0; i < songs.size(); i++) {
            if (songs[i].fileTitle.contains(searchText)) {
                tableComponent.selectRow(i);
            }
        }
    }
    else {
        tableComponent.deselectAllRows();
    }
}

void PlaylistComponent::savePlaylist() {
    // outputs a .csv file stream to save playlist to be loaded later
    std::ofstream musicPlaylist("musicPlaylist.csv");
    // save library to file using "," for differentiating
    for (SoundTrack& s : songs) {
        musicPlaylist << s.file.getFullPathName() << "," << s.duration << "\n";
    }
}

void PlaylistComponent::loadPlaylist() {
    // calls input stream from saved playlist
    std::ifstream musicPlaylist("musicPlaylist.csv");
    std::string path;
    std::string time;
    if (musicPlaylist.is_open()) {
        while (getline(musicPlaylist, path, ',')) {
            juce::File newFile{ path };
            SoundTrack newTrack{ newFile };
            getline(musicPlaylist, time);
            newTrack.duration = time;
            songs.push_back(newTrack);
        }
    }
    musicPlaylist.close();
}

void PlaylistComponent::loadToDeck(DeckGUI* deckGUI) {
    int songSelectedId{ tableComponent.getSelectedRow() };
    if (songSelectedId != -1) {
        deckGUI->loadFile(songs[songSelectedId].fileURL);
    }
    else {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
            "Alert:",
            "Please select a song to load in deck",
            "Close",
            nullptr
        );
    }
}