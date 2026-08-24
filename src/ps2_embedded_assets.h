#ifndef PS2_EMBEDDED_ASSETS_H
#define PS2_EMBEDDED_ASSETS_H

#ifdef __PS2__

#include <SDL.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct ps2_embedded_asset_entry {
	const char* path;
	size_t offset;
	size_t size;
} ps2_embedded_asset_entry;

extern const unsigned char ps2_embedded_asset_blob[];
extern const ps2_embedded_asset_entry ps2_embedded_asset_entries[];
extern const size_t ps2_embedded_asset_count;
extern const size_t ps2_embedded_asset_blob_size;

const unsigned char* ps2_embedded_asset_find(const char* path, size_t* size);
bool ps2_embedded_asset_exists(const char* path);
bool ps2_embedded_directory_exists(const char* path);
SDL_RWops* ps2_embedded_asset_rwops(const char* path);

bool ps2_storage_init(void);
const char* ps2_storage_root(void);
const char* ps2_storage_path(const char* filename, char* dst, size_t size);

#endif

#endif
