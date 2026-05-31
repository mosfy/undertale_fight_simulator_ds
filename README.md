# Undertale Fight Simulator DS

Undertale Fight Simulator DS is a Nintendo DS homebrew project where I try to recreate some Undertale boss fights on real DS hardware.

The goal isn't to remake the full game. I mainly want to recreate the battle system and some of my favorite fights from Undertale.

The first fights I plan to make are:

* Toriel
* Papyrus
* Sans

This project is also an excuse for me to learn more about Nintendo DS development and to make a YouTube video about the whole process.

Sorry in advance, the video will probably be in French. If enough people are interested, I may add English subtitles later.

## Current state

The project is still at a very early stage.

Right now I'm mostly working on:

* sprite rendering
* player movement
* touch screen controls
* battle box rendering
* collision detection
* basic attacks
* menus
* HP system

A lot of things are still missing.

## Controls

Current controls:

* D-Pad → Move the soul
* Stylus → Move the soul
* A → Confirm
* B → Back

Controls may change during development.

## Requirements

This project uses BlocksDS.

Installation guide:

https://blocksds.skylyrac.net/docs/

You will also need:

* make
* a DS emulator (melonDS recommended) or real hardware
* basic knowledge of C if you want to modify the code

## Building

Load the BlocksDS environment:

```bash
source /opt/wonderful/bin/wf-env
```

Set the environment variables if needed:

```bash
export BLOCKSDS=/opt/wonderful/thirdparty/blocksds/core
export BLOCKSDSEXT=/opt/wonderful/thirdparty/blocksds/external
```

Compile:

```bash
make clean
make
```

If everything goes well, a `.nds` file will be generated.

## Running

The generated ROM should work on:

* melonDS
* Nintendo DS flashcards
* Nintendo DSi
* Nintendo 3DS (homebrew)

## Prebuilt ROM

A prebuilt ROM is included.

If you just want to try the project, you don't need to compile anything.

Only compile it if you want to modify the source code or contribute.

## Future plans

Things I want to add later:

* Toriel fight
* Papyrus fight
* Sans fight
* battle menu
* sound effects
* music
* KR (Karma) system
* easier way to create custom bosses
* more attacks

## YouTube

I am documenting the development of this project for a YouTube video.

The video will show:

* how the project started
* DS homebrew development
* problems I encountered
* testing on real hardware
* the final result

## Disclaimer

Undertale belongs to Toby Fox.

This is a fan project made for learning and fun.

Please support the original game.
