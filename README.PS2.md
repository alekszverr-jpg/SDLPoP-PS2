# SDLPoP for PlayStation 2

This port builds SDLPoP as a PS2 homebrew application with the open-source
ps2dev toolchain, SDL2 and SDL2_image. The toolchain is used only by GitHub
Actions; a local PS2SDK installation is not required.

## Build

Open the **Build PlayStation 2** workflow in GitHub Actions and run it, or push
a commit. Download the `SDLPoP-PS2` artifact when the job finishes. It contains
`SDLPoP-PS2.zip` and standalone ELF files for progressive and interlaced
output.

## Run

Extract the complete `SDLPoP-PS2` directory to a PS2-accessible device. Keep
`BOOT.ELF`, `SDLPoP.ini` and the `data` directory together. Start `BOOT.ELF`
with wLaunchELF or another homebrew launcher. SDL2 mounts and waits for the
launch device, including `mass:`, `host:`, memory card and optical media.

## Video modes

- `BOOT.ELF` / `BOOT-480P.ELF`: 720x480 progressive at 60 Hz. This is the
  preferred version and requires a display and cable which accept 480p.
- `BOOT-480I.ELF`: 640x448 NTSC interlaced fallback for standard-definition
  televisions which cannot synchronize to 480p.

Both versions expand the original 320x200 DOS framebuffer over the complete
4:3 PS2 raster. PS2-specific defaults force sharp nearest-neighbour scaling
and disable integer scaling, avoiding the incomplete render-to-texture path in
the SDL PS2 backend. The backend is also patched to use the GS neutral texture
modulation value, preventing the washed-out, approximately double-bright image
produced by an unmodified SDL 2.32 PS2 renderer.

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
