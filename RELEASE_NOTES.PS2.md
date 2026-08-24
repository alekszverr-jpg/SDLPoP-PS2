# Prince of Persia for PlayStation 2 — release candidate

This is a native PlayStation 2 port of SDLPoP 1.24 RC. It runs directly on
the console and does not use DOS emulation.

## Highlights

- A self-contained `BOOT.ELF` with all original game resources embedded.
- Launch through wLaunchELF or the OPL Apps menu, including an ELF stored on
  an SMB share.
- Safe 240p boot for standard-definition CRT televisions.
- Optional 480p test mode with an automatic 10-second rollback to 240p.
- Screen size and position calibration for CRT overscan.
- DualShock 2 controls and PS2-specific control text.
- Working game saves, quicksave/quickload, Hall of Fame persistence and exit
  to the PS2 Browser.
- Lightweight DBOPL music playback tuned for the PS2, plus responsive menu
  sound feedback.
- PS2-focused settings that hide desktop-only or unsuitable options.

## Storage

The game first tries to store mutable files in `mass:/SDLPoP-PS2`. If no
writable USB drive is available, it falls back to `mc0:/SDLPoP-PS2` on the
memory card in slot 1.

The selected directory contains saves, Hall of Fame data, menu settings,
video calibration and `SDLPoP-PS2.log`.

## Installation

For wLaunchELF, copy and start `BOOT.ELF`. No `data` directory or INI file is
required.

For OPL, copy `BOOT.ELF` and `title.cfg` into:

```text
APPS/SDLPoP-PS2/
```

The release ZIP also includes `BOOT.ELF.sha256` for integrity verification.

## Known limitations

- 480p requires a compatible television or monitor and cable.
- External resource packs and mods are not loaded by the PS2 build; the stock
  game resources are compiled into the ELF.
- Real-hardware SMB boot and memory-card fallback remain final release-candidate
  smoke tests.
