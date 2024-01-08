# OtoDecks Project Application

This project is a JUCE-based application providing a basic startup code template for audio-related development. It sets up the structure for a JUCE application with a main window containing an instance of `MainComponent`.

## Overview

The OtoDecks Project Application serves as a starting point for audio application development using the JUCE framework. It includes a basic structure for a desktop window that houses the main user interface component.

## Features

- **Main Window:** The application creates a main window with basic functionalities.
- **DocumentWindow:** The main window is derived from `juce::DocumentWindow` and contains a content component.
- **Close Button:** The close button on the window triggers a system quit request.
- **Cross-Platform:** The application is designed to work on multiple platforms, thanks to JUCE's cross-platform capabilities.

## How to Use

1. **Build and Run:** Compile and run the application to see the basic setup in action.
2. **MainComponent:** Customize the `MainComponent` class to implement the desired audio functionality and user interface.

## Application Structure

- **OtoDecks_ProjectApplication:** The main application class derived from `juce::JUCEApplication`.
- **MainWindow:** A subclass of `juce::DocumentWindow` representing the main application window.
- **MainComponent:** The main user interface component where you can implement your audio-related features.

## JUCE Framework

The application utilizes the JUCE framework, a powerful C++ library for building audio applications, plugins, and more. JUCE provides cross-platform support and a range of tools for audio development.

## How to Run

To run the application, build the project in a JUCE-supported development environment, and execute the generated executable.

## Credits

- JUCE Framework: [JUCE](https://juce.com/)
- OtoDecks Project Team

Feel free to use this project as a starting point for your audio-related applications using JUCE!

## License

[Include information about the license for your project.]
