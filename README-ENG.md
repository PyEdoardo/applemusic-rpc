# Discord RPC Apple Music

This project integrates Apple Music playback with Discord, using **Discord Rich Presence**. It allows the song name, artist, and album to be displayed directly on your Discord profile.

**IMPORTANT:** The project does not yet filter other audio sources (like YouTube, for example), so it may display playback information from other media sources in addition to Apple Music.

**Reason:** The Windows SDK is a bit tricky to work with, and I’m currently researching how to anchor the app to Apple Music, access it by PID, and prevent displaying information from other apps. Currently, it uses Windows::Media to retrieve data since Apple doesn't make it easy to create APIs.

## Features

- Displays the song, artist, and album currently playing on Apple Music.
- Shows the album cover image directly in Discord. Currently, this doesn't work because I need to figure out how to pull images on the fly using the song name, searching some CDN that stores images and covers. Discord doesn’t allow using a data stream as an image or a saved image.
- Updates the information every second (doesn't impact performance, it’s done in C++...) while the song is playing.

## Requirements

- **Windows 10 or higher**
- **Visual Studio 2019 or higher** with support for C++17 or higher
- **Discord**: An account configured to display activities on your profile.

## How to Compile the Project

1. **Clone the repository:**

   If you haven’t done so already, clone the repository with the following command:

   ```bash
   git clone https://github.com/PyEdoardo/applemusic-rpc

