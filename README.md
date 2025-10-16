# gnukebox 🎵

A simple command-line music player written in C using SDL2 for Linux/Unix. Play your MP3 collection with an intuitive terminal interface.

## Features

- 🎶 Play MP3 files from any directory
- 📁 Browse and switch between music folders
- ⏯️ Basic playback controls (play, pause, resume, stop)
- ⏭️ Next/previous song navigation
- 📋 List songs in current directory
- 🎯 Select songs by index
- 🖥️ Simple terminal-based interface

## Prerequisites

Before building, make sure you have the following dependencies installed:

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-mixer-dev pkg-config
```

### Fedora:
```bash
sudo dnf install SDL2-devel SDL2_mixer-devel pkgconf-pkg-config
```

### Arch Linux:
```bash
sudo pacman -S sdl2 sdl2_mixer pkgconf
```

## Building

1. Clone the repository:
```bash
git clone https://github.com/duphan2014/gnukebox.git
cd gnukebox
```

2. Build the project:
```bash
./build.sh
```

This will create an executable called `gnukebox`.

## Usage

### Running the Player

```bash
./gnukebox
```

The player will start with your default music directory (`~/Music`).

### Controls

| Key | Action |
|-----|--------|
| `L` | List songs in current directory |
| `P` | Play a song (enter index number) |
| `p` | Pause current song |
| `r` | Resume paused song |
| `s` | Stop current song |
| `n` | Play next song |
| `l` | Play last/previous song |
| `c` | Change to different music folder |
| `q` | Quit the application |

### Example Session

```
== gnukebox ==
  L to list songs
  P to play song
  p to pause
  s to stop
  q to quit
  n to play next song
  l to play last song
  c to change folder

> L
Available Songs:
0. song1.mp3
1. song2.mp3
2. favorite_track.mp3

> P
Enter song index to play: 1
Playing: 1. song2.mp3

> n
Playing: 2. favorite_track.mp3
```

## Project Structure

```
gnukebox/
├── player.c        # Main program and music player implementation
├── player.h        # Player header with structs and function declarations
├── build.sh        # Build script
└── README.md       # This file
```

## Code Overview

### Core Components

- **Player**: Main music player structure that manages song library and playback state
- **Song**: Individual song structure containing metadata and SDL_mixer music object
- **PlayerStatus**: Enum for tracking playback state (PLAYING, PAUSED, STOPPED)

### Key Functions

- `Player_init()`: Initialize the player and load default music directory
- `Player_loadFolder()`: Load MP3 files from a specified directory
- `Player_play()`: Play a song by index with wraparound support
- `Player_changeFolder()`: Switch to a different music directory

## Dependencies

- **SDL2**: Cross-platform multimedia library
- **SDL2_mixer**: Audio mixing library for MP3 playback
- **pkg-config**: For managing library compile and link flags
- **Standard C libraries**: stdio, stdlib, string, dirent

## Supported Audio Formats

Currently supports MP3 files only. The player scans directories for files with `.mp3` extension.

## Known Limitations

- Only supports MP3 format
- Maximum of 200 songs per directory
- Hardcoded paths in some functions
- Basic error handling

## Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b new-feature`
3. Make your changes and commit: `git commit -am 'Add new feature'`
4. Push to the branch: `git push origin new-feature`
5. Submit a pull request

## License

This project is open source. Feel free to use and modify as needed.

## Troubleshooting

### Common Issues

**cannot initalize default folder because path != /home/pc/Music:**
- just update the corresponding part in Player_init()

**Build fails with missing headers:**
- Make sure all SDL2 development packages are installed
- Ensure pkg-config is installed and working

**No songs found:**
- Check that your music directory contains MP3 files
- Verify directory permissions
- Use the 'c' command to change to the correct music folder

**Audio playback issues:**
- Ensure your system has working audio output
- Check that MP3 files are not corrupted
- Verify SDL2_mixer is properly installed

---

*Happy listening! 🎵*
