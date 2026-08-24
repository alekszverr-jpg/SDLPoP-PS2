# PlayStation 2 release checklist

## Automated

- [x] Cross-compile with the pinned PS2DEV toolchain in GitHub Actions.
- [x] Embed every file from `data` and the base INI in `PRINCE.ELF`.
- [x] Reject a release ZIP containing an external `data` directory or INI.
- [x] Generate and verify `PRINCE.ELF.sha256`.
- [x] Package OPL `title.cfg`, documentation and GPL license text.

## Confirmed on real PlayStation 2

- [x] Boot and gameplay in 240p.
- [x] Self-contained ELF starts without an external `data` directory.
- [x] `PRINCE.ELF` starts from the OPL Apps menu over SMB.
- [x] DualShock 2 input, including the corrected R1 action mapping.
- [x] Screen size and position calibration.
- [x] Game saves and quicksave/quickload.
- [x] Exit returns to the PS2 Browser.
- [x] Title music and dense passages play without crackling or slowdown.
- [x] Gameplay no longer freezes around falling-gate sound playback.

## Confirmed in PCSX2

- [x] Hall of Fame controller text entry and persistence.
- [x] Menu sounds remain responsive during rapid navigation.
- [x] 480p confirmation dialog rolls back to 240p when not accepted.

## Final smoke tests

- [ ] With USB connected, confirm files are created in `mass:/SDLPoP-PS2`.
- [x] Without USB, confirm files are created in `mc0:/SDLPoP-PS2`.
- [ ] Confirm Hall of Fame persistence on real hardware.
- [ ] If a compatible display is available, confirm accepted 480p persists.
