if(NOT DEFINED SDL_PS2_MAIN_SOURCE)
    message(FATAL_ERROR "SDL_PS2_MAIN_SOURCE is required")
endif()

file(READ "${SDL_PS2_MAIN_SOURCE}" SDL_PS2_MAIN_TEXT)
set(SDL_PS2_MAIN_OLD [=[
    getcwd(cwd, sizeof(cwd));
    waitUntilDeviceIsReady(cwd);
]=])
set(SDL_PS2_MAIN_NEW [=[
    /* SDLPoP carries its read-only resources inside the ELF. Do not wait for
       the launch device: an ELF started by OPL over SMB loses OPL's SMB mount
       after the mandatory IOP reset. Writable storage is selected by the app. */
    getcwd(cwd, sizeof(cwd));
]=])
string(FIND "${SDL_PS2_MAIN_TEXT}" "${SDL_PS2_MAIN_OLD}" SDL_PS2_MAIN_MATCH)
if(SDL_PS2_MAIN_MATCH EQUAL -1)
    message(FATAL_ERROR "Expected SDL PS2 launch-device wait block was not found")
endif()
string(REPLACE "${SDL_PS2_MAIN_OLD}" "${SDL_PS2_MAIN_NEW}" SDL_PS2_MAIN_TEXT "${SDL_PS2_MAIN_TEXT}")
file(WRITE "${SDL_PS2_MAIN_SOURCE}" "${SDL_PS2_MAIN_TEXT}")
