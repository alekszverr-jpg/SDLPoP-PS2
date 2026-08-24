# Prince of Persia for PlayStation 2

[![Build PlayStation 2](https://github.com/alekszverr-jpg/SDLPoP-PS2/actions/workflows/ps2.yml/badge.svg?branch=ps2)](https://github.com/alekszverr-jpg/SDLPoP-PS2/actions/workflows/ps2.yml)
[![Latest release](https://img.shields.io/github/v/release/alekszverr-jpg/SDLPoP-PS2?display_name=release&sort=semver)](https://github.com/alekszverr-jpg/SDLPoP-PS2/releases/latest)

A native PlayStation 2 port of the 1989 DOS version of **Prince of Persia**,
based on [SDLPoP](https://github.com/NagyD/SDLPoP). It runs directly on the PS2
and does not use DOS emulation.

The port is designed for real hardware: it boots in CRT-safe 240p, uses the
DualShock 2, supports USB and memory-card saves, and can be launched locally or
through OPL over SMB.

## Features

- Self-contained `PRINCE.ELF` with the required game resources embedded.
- Native 240p output with screen size and position calibration for CRT overscan.
- Optional 480p mode with a 10-second automatic rollback to 240p.
- DualShock 2 controls and PS2-specific menu text.
- Saves, quicksave/quickload, Hall of Fame entry and a pause-menu Hall of Fame
  viewer.
- Lightweight DBOPL music playback tuned for the PS2.
- Launch through wLaunchELF or OPL Apps, including from an SMB share.
- Configurable exit to the PS2 Browser or uLaunchELF.
- PS2-focused settings profiles and access to SDLPoP's optional fixes and game
  modifications.

## Download

Download the latest package from
[GitHub Releases](https://github.com/alekszverr-jpg/SDLPoP-PS2/releases/latest).

The release archive contains:

- `PRINCE.ELF` — the self-contained game executable;
- `title.cfg` — OPL Apps metadata;
- `PRINCE.ELF.sha256` — an integrity checksum;
- PS2 documentation, release notes and GPL license text.

No external `data` directory or `SDLPoP.ini` is required.

## Installation

### wLaunchELF

Copy `PRINCE.ELF` to a USB drive, memory card or another accessible device and
start it from wLaunchELF.

### OPL Apps

Place `PRINCE.ELF` and `title.cfg` together in:

```text
APPS/SDLPoP-PS2/
```

The directory may be on a local OPL device or an SMB share.

## Saves and settings

The game first tries to write mutable files to:

```text
mass:/SDLPoP-PS2
```

If no writable USB drive is available, it falls back to the memory card in
slot 1:

```text
mc0:/SDLPoP-PS2
```

This directory stores saves, Hall of Fame data, quicksaves, menu settings,
video calibration and `SDLPoP-PS2.log`. The ELF itself can therefore remain on
a read-only SMB share.

## Video output

The port always starts in safe 640x224 NTSC 240p. Under
**Settings > Visuals > PS2 video mode**, 720x480p at 60 Hz can be tested on a
compatible display and cable. If the confirmation is not accepted within 10
seconds, the renderer automatically returns to 240p.

Screen width, height and position can be adjusted in the same menu to fit a
television's overscan area.

## DualShock 2 controls

| Button | Action |
| --- | --- |
| D-pad / left analog stick | Move and navigate menus |
| Cross | Crouch, climb down, confirm |
| Triangle | Jump, climb up |
| Square / R1 | Action, careful step, attack, grab |
| Circle | Cancel or go back |
| Start / Select | Pause menu |

During Hall of Fame name entry, Up/Down changes the character, Right adds a
character, Left or Circle erases, and Cross confirms.

## Building

The PS2 toolchain is provided by GitHub Actions; a local PS2SDK installation is
not needed. Push a commit or run the **Build PlayStation 2** workflow manually,
then download the `SDLPoP-PS2` artifact.

The workflow uses the open-source ps2dev toolchain, SDL2 and SDL2_image. It
cross-compiles the MIPS ELF, verifies the embedded resources and checksum, and
creates the self-contained release ZIP.

## Test status

The port has been tested on a real PlayStation 2 for 240p video, calibration,
DualShock 2 input, music and effects, gameplay, saves, quicksave/quickload,
Hall of Fame persistence, USB and memory-card storage, SMB launch, and exit to
the PS2 Browser or uLaunchELF.

Accepted 480p output has not yet been tested on a compatible physical display.
The 480p rollback path has been verified in PCSX2.

See [RELEASE_CHECKLIST.PS2.md](RELEASE_CHECKLIST.PS2.md) for the complete test
matrix and [README.PS2.md](README.PS2.md) for detailed platform notes.

## Known limitations

- 480p requires a compatible television or monitor and cable.
- External resource packs and mods are not loaded; the stock resources are
  compiled into the ELF.
- The original unstable level 0 demonstration is skipped on PS2. After the
  automatic Hall of Fame screen, the title sequence restarts instead.

## Credits

This port is based on [SDLPoP](https://github.com/NagyD/SDLPoP), created by
NagyD and developed by the SDLPoP contributors. The PlayStation 2 build uses
the [ps2dev](https://github.com/ps2dev) homebrew toolchain and SDL.

Prince of Persia was created by Jordan Mechner. This is an unofficial community
port and is not affiliated with or endorsed by the original publisher or
rights holders.

## License

The source code is distributed under the GNU General Public License. See
[COPYING](COPYING) and the notices in the source tree for details.
