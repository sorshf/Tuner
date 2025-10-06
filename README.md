# 🎤Audio Frequency Meter (Tuner)

An **Audio Frequency Meter** built using **C++** and **SDL3** that captures live audio input and visualizes its spectrum and its frequency that is calculated using the Autocorrelation Function.

## Features

- 🎙️ Captures audio input from your microphone
- 📊 Performs real-time frequency analysis using Autocorrelation Function
- 📈 Sample Rate: 15000/s
- 🔈 Audio Buffer Duration: 300ms
- 📺 App window stays always on top

![Screenshot of the app measuring pure 440Hz audio.](/assets/screenshots/Screenshot%202025-10-05%20at%208.12.35 PM.png)

## Dependencies

- [SDL3](https://www.libsdl.org) – Audio capture and window rendering
- [SDL_ttf 3.0](https://wiki.libsdl.org/SDL3_ttf/FrontPage) - Text rendering
- C++17 or later

## Build

```bash
git clone https://github.com/sorshf/tuner.git
cd Tuner
mkdir build && cd build
cmake ..
make
./bin/Tuner
```