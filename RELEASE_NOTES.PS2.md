# Prince of Persia for PlayStation 2 — release candidate

This is a native PlayStation 2 port of SDLPoP 1.24 RC. It runs directly on
the console and does not use DOS emulation.

## Highlights

- A self-contained `PRINCE.ELF` with all original game resources embedded.
- Launch through wLaunchELF or the OPL Apps menu, including an ELF stored on
  an SMB share.
- Safe 240p boot for standard-definition CRT televisions.
- Optional 480p test mode with an automatic 10-second rollback to 240p.
- Screen size and position calibration for CRT overscan.
- DualShock 2 controls and PS2-specific control text.
- Working game saves, quicksave/quickload, Hall of Fame persistence and exit
  to either the PS2 Browser or uLaunchELF.
- Hall of Fame viewer available directly from the pause menu.
- Safe title attract loop that returns to the title after Hall of Fame instead
  of entering the unstable level 0 demonstration.
- Lightweight DBOPL music playback tuned for the PS2. Menu navigation sounds
  are disabled to keep rapid scrolling from disturbing audio playback.
- PS2-focused settings that hide desktop-only or unsuitable options.

## Storage

The game first tries to store mutable files in `mass:/SDLPoP-PS2`. If no
writable USB drive is available, it falls back to `mc0:/SDLPoP-PS2` on the
memory card in slot 1.

The selected directory contains saves, Hall of Fame data, menu settings,
video calibration and `SDLPoP-PS2.log`.

The exit destination is selected under **Settings > General**. uLaunchELF is
normally expected at `mc0:/BOOT/BOOT.ELF`; alternate memory-card and USB paths
are also checked, with an automatic fallback to the PS2 Browser.

## Installation

For wLaunchELF, copy and start `PRINCE.ELF`. No `data` directory or INI file is
required.

For OPL, copy `PRINCE.ELF` and `title.cfg` into:

```text
APPS/SDLPoP-PS2/
```

The release ZIP also includes `PRINCE.ELF.sha256` for integrity verification.

## Known limitations

- 480p requires a compatible television or monitor and cable.
- External resource packs and mods are not loaded by the PS2 build; the stock
  game resources are compiled into the ELF.
- Accepted 480p output still needs testing on a compatible display.
