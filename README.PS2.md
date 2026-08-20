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

## Video modes

- The game always boots in safe 640x224 NTSC 240p, which is progressive and
  compatible with standard-definition CRT televisions.
- The **Settings > Visuals > PS2 video mode** item can test 720x480p at 60 Hz.
  480p requires a compatible display and cable.
- After switching to 480p, select **OK** within 10 seconds. If the display
  cannot show the confirmation dialog, the game automatically recreates the
  renderer in 240p.
- Use **Screen width**, **Screen height**, **Horizontal position** and
  **Vertical position** in the same menu to fit the picture to a CRT's
  overscan area. Changes appear immediately and are saved in
  `SDLPoP-PS2.video` next to the ELF.

Both modes expand the original 320x200 DOS framebuffer over the complete 4:3
PS2 raster. PS2-specific defaults force sharp nearest-neighbour scaling
and disable integer scaling, avoiding the incomplete render-to-texture path in
the SDL PS2 backend. The backend is also patched to use the GS neutral texture
modulation value, preventing the washed-out, approximately double-bright image
produced by an unmodified SDL 2.32 PS2 renderer.

The game writes normal saves, Hall of Fame data and quicksaves next to the ELF.
Use writable media if those features are needed.

## DualShock 2 controls

- D-pad or left analog stick: move
- Cross: crouch/climb down and confirm menu items
- Triangle: jump/climb up
- Square or R1: action, careful step, attack and grab
- Start or Select: pause menu
- D-pad Left/Right: change the selected setting

The launch information screen and **Settings > Controls** use these PS2 button
names instead of the original PC keyboard shortcuts.

## Console settings layout

- **Gameplay > Gameplay profile > Original DOS** preserves the original DOS
  mechanics and tricks.
- **Recommended** enables SDLPoP's bug fixes while leaving optional moves and
  rule changes disabled.
- **Advanced > Detailed bug fixes** exposes every individual fix for users who
  want a custom profile.
- Cheats, copy protection and the full game/level modification tools are kept
  under **Advanced** instead of the normal gameplay menu.
- The experimental torch-shadow renderer is hidden on PS2. Fade and flash
  controls remain available because they are part of the normal presentation
  and accessibility options.

## Current test boundary

GitHub Actions is configured to verify that the MIPS ELF links against the PS2
versions of SDL2 and SDL2_image and to package all runtime data. Rendering,
audio timing, controller behaviour and saves still need a smoke test in PCSX2
followed by a test on a real PS2.
