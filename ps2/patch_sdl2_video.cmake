if(NOT DEFINED SDL_PS2_RENDER_SOURCE)
    message(FATAL_ERROR "SDL_PS2_RENDER_SOURCE is required")
endif()

file(READ "${SDL_PS2_RENDER_SOURCE}" SDL_PS2_RENDER_CONTENT)

# SDL's PS2 renderer always selects 640x448 NTSC interlaced output. Let the
# application request 720x480 progressive output through a private hint while
# retaining the original mode as a fallback build.
set(SDL_PS2_MODE_OLD [[    gsGlobal->Mode = GS_MODE_NTSC;
    gsGlobal->Height = 448;]])
set(SDL_PS2_MODE_NEW [[    const char *videoMode = SDL_GetHint("SDL_PS2_VIDEO_MODE");
    if (videoMode && SDL_strcasecmp(videoMode, "480p") == 0) {
        gsGlobal->Mode = GS_MODE_DTV_480P;
        gsGlobal->Interlace = GS_NONINTERLACED;
        gsGlobal->Field = GS_FRAME;
        gsGlobal->Width = 720;
        gsGlobal->Height = 480;
    } else {
        gsGlobal->Mode = GS_MODE_NTSC;
        gsGlobal->Interlace = GS_INTERLACED;
        gsGlobal->Field = GS_FIELD;
        gsGlobal->Width = 640;
        gsGlobal->Height = 448;
    }]])

# With GS texture modulation, 0x80 is neutral. SDL supplies 0xFF for an
# unmodified texture, which the old backend passed through and consequently
# rendered at roughly double brightness. Map SDL's 0..255 modulation range to
# the GS 0..128 range for textured geometry only.
set(SDL_PS2_COLOR_OLD [[            vertices->rgbaq = color_to_RGBAQ(col_.r, col_.g, col_.b, col_.a, 0);]])
set(SDL_PS2_COLOR_NEW [[            vertices->rgbaq = color_to_RGBAQ(
                (uint8_t)((col_.r + 1) >> 1),
                (uint8_t)((col_.g + 1) >> 1),
                (uint8_t)((col_.b + 1) >> 1),
                (uint8_t)((col_.a + 1) >> 1), 0);]])

foreach(PAIR MODE COLOR)
    string(FIND "${SDL_PS2_RENDER_CONTENT}" "${SDL_PS2_${PAIR}_OLD}" SDL_PS2_${PAIR}_POSITION)
    if(SDL_PS2_${PAIR}_POSITION EQUAL -1)
        message(FATAL_ERROR "Expected SDL2 PS2 ${PAIR} code was not found")
    endif()
    string(REPLACE
        "${SDL_PS2_${PAIR}_OLD}"
        "${SDL_PS2_${PAIR}_NEW}"
        SDL_PS2_RENDER_CONTENT
        "${SDL_PS2_RENDER_CONTENT}"
    )
endforeach()

file(WRITE "${SDL_PS2_RENDER_SOURCE}" "${SDL_PS2_RENDER_CONTENT}")
