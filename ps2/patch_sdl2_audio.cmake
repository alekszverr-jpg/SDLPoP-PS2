if(NOT DEFINED SDL_PS2_AUDIO_SOURCE)
    message(FATAL_ERROR "SDL_PS2_AUDIO_SOURCE is required")
endif()

file(READ "${SDL_PS2_AUDIO_SOURCE}" SDL_PS2_AUDIO_CONTENT)
set(SDL_PS2_AUDIO_EXPECTED "this->spec.samples = 512;")
string(FIND "${SDL_PS2_AUDIO_CONTENT}" "${SDL_PS2_AUDIO_EXPECTED}" SDL_PS2_AUDIO_POSITION)

if(SDL_PS2_AUDIO_POSITION EQUAL -1)
    message(FATAL_ERROR "Expected SDL2 PS2 audio buffer setting was not found")
endif()
