if(NOT DEFINED SDL_PS2_AUDIO_SOURCE)
    message(FATAL_ERROR "SDL_PS2_AUDIO_SOURCE is required")
endif()

file(READ "${SDL_PS2_AUDIO_SOURCE}" SDL_PS2_AUDIO_CONTENT)
set(SDL_PS2_AUDIO_EXPECTED "this->spec.samples = 512;")
string(FIND "${SDL_PS2_AUDIO_CONTENT}" "${SDL_PS2_AUDIO_EXPECTED}" SDL_PS2_AUDIO_POSITION)

if(SDL_PS2_AUDIO_POSITION EQUAL -1)
    message(FATAL_ERROR "Expected SDL2 PS2 audio buffer setting was not found")
endif()

# SDL only raises its PS2 audio thread by one priority level. Rendering and
# rapid menu input can still delay callbacks even when synthesis itself is far
# below budget, so give the short real-time callback a little more precedence.
set(SDL_PS2_AUDIO_PRIORITY_OLD
    "ChangeThreadPriority(thid, status.current_priority - 1);")
set(SDL_PS2_AUDIO_PRIORITY_NEW
    "ChangeThreadPriority(thid, status.current_priority - 3);")
string(FIND "${SDL_PS2_AUDIO_CONTENT}"
    "${SDL_PS2_AUDIO_PRIORITY_OLD}" SDL_PS2_AUDIO_PRIORITY_POSITION)

if(SDL_PS2_AUDIO_PRIORITY_POSITION EQUAL -1)
    message(FATAL_ERROR "Expected SDL2 PS2 audio thread priority setting was not found")
endif()

string(REPLACE
    "${SDL_PS2_AUDIO_PRIORITY_OLD}"
    "${SDL_PS2_AUDIO_PRIORITY_NEW}"
    SDL_PS2_AUDIO_CONTENT
    "${SDL_PS2_AUDIO_CONTENT}"
)
file(WRITE "${SDL_PS2_AUDIO_SOURCE}" "${SDL_PS2_AUDIO_CONTENT}")
