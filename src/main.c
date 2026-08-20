/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2025  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

The authors of this program may be contacted at https://forum.princed.org
*/

#include "common.h"

#ifdef __PS2__
#include <debug.h>
#include <delaythread.h>
#include <iopcontrol.h>
#include <kernel.h>
#include <sifrpc.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

int ps2_trace_frame = -1;

// SDL2main calls this weak hook before it initializes the launch-device
// drivers. Keeping the standard reset sequence here lets us display progress
// even if the real console stalls before SDL_main is reached.
void reset_IOP(void) {
	init_scr();
	scr_printf("SDLPoP PS2 diagnostic boot\n\n");
	scr_printf("[1/3] Resetting IOP...\n");
	SifInitRpc(0);
	while (!SifIopReset(NULL, 0)) {
	}
	while (!SifIopSync()) {
	}
	scr_printf("[2/3] IOP reset complete. Mounting devices...\n");
}

void ps2_boot_log(const char* format, ...) {
	FILE* fp = fopen("SDLPoP-PS2.log", "a");
	if (fp == NULL) return;
	va_list args;
	va_start(args, format);
	vfprintf(fp, format, args);
	va_end(args);
	fputc('\n', fp);
	fclose(fp);
}

void ps2_boot_fatal(const char* message) {
	ps2_boot_log("FATAL: %s", message);
	init_scr();
	scr_printf("SDLPoP PS2 startup error\n\n%s\n\n", message);
	scr_printf("See SDLPoP-PS2.log beside BOOT.ELF.\n");
	SleepThread();
}

static int ps2_wait_for_game_data(void) {
	struct stat path_stat;
	for (int attempt = 0; attempt < 150; ++attempt) {
		if (stat("data/PRINCE", &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
			return attempt;
		}
		if ((attempt % 10) == 0) scr_printf(".");
		DelayThread(100000);
	}
	return -1;
}
#endif


#ifdef __amigaos4__
static const char version[] = "\0$VER: SDLPoP " SDLPOP_VERSION " (" __AMIGADATE__ ")";
static const char stack[] = "$STACK:200000";
#endif

#ifdef __PSP__
#include <psppower.h>
#endif

int main(int argc, char *argv[])
{
	#ifdef __PSP__
	scePowerSetClockFrequency(333,333,166);
	#endif
	g_argc = argc;
	g_argv = argv;
#ifdef __PS2__
	char cwd[POP_MAX_PATH] = ".";
	getcwd(cwd, sizeof(cwd));
	scr_printf("[3/3] Application reached.\n");
	scr_printf("Path: %s\n", cwd);
	scr_printf("Waiting for data/PRINCE");
	int data_wait_attempts = ps2_wait_for_game_data();
	if (data_wait_attempts < 0) {
		ps2_boot_fatal("USB is mounted, but data/PRINCE was not found after 15 seconds.");
	}
	FILE* log_file = fopen("SDLPoP-PS2.log", "w");
	if (log_file != NULL) fclose(log_file);
	ps2_boot_log("main: cwd=%s argv0=%s", cwd, argc > 0 && argv[0] != NULL ? argv[0] : "(none)");
	ps2_boot_log("main: data/PRINCE ready after %d ms", data_wait_attempts * 100);
	scr_printf("\nGame data found after %d ms.\nStarting SDL...\n", data_wait_attempts * 100);
	DelayThread(2000000);
#endif
	pop_main();
	return 0;
}

