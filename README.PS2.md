# SDLPoP for PlayStation 2

This port builds SDLPoP as a PS2 homebrew application with the open-source
ps2dev toolchain, SDL2 and SDL2_image. The toolchain is used only by GitHub
Actions; a local PS2SDK installation is not required.

## Build

Open the **Build PlayStation 2** workflow in GitHub Actions and run it, or push
a commit. Download the `SDLPoP-PS2` artifact when the job finishes. It contains
`SDLPoP-PS2.zip` and a standalone `BOOT.ELF`.

## Run

Extract the complete `SDLPoP-PS2` directory to a PS2-accessible device. Keep
`BOOT.ELF`, `SDLPoP.ini` and the `data` directory together. Start `BOOT.ELF`
with wLaunchELF or another homebrew launcher. SDL2 mounts and waits for the
launch device, including `mass:`, `host:`, memory card and optical media.

The game writes normal saves, Hall of Fame data and quicksaves next to the ELF.
Use writable media if those features are needed.

## DualShock 2 controls

- D-pad or left analog stick: move
- Cross: crouch/climb down
- Triangle: jump/climb up
- Square or R1: action, careful step, attack and grab
- Start or Select: pause menu

## Current test boundary

GitHub Actions is configured to verify that the MIPS ELF links against the PS2
versions of SDL2 and SDL2_image and to package all runtime data. Rendering,
audio timing, controller behaviour and saves still need a smoke test in PCSX2
followed by a test on a real PS2.
