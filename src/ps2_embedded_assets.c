#include "common.h"

#ifdef __PS2__

#include "ps2_embedded_assets.h"
#include <delaythread.h>
#include <limits.h>

static char ps2_selected_storage[POP_MAX_PATH] = "";

static const char* normalize_asset_path(const char* path) {
	while (path[0] == '.' && path[1] == '/') path += 2;
	while (path[0] == '/') path++;
	return path;
}

const unsigned char* ps2_embedded_asset_find(const char* path, size_t* size) {
	if (size != NULL) *size = 0;
	if (path == NULL) return NULL;
	path = normalize_asset_path(path);

	size_t low = 0;
	size_t high = ps2_embedded_asset_count;
	while (low < high) {
		size_t middle = low + (high - low) / 2;
		int comparison = strcmp(path, ps2_embedded_asset_entries[middle].path);
		if (comparison == 0) {
			const ps2_embedded_asset_entry* entry = &ps2_embedded_asset_entries[middle];
			if (entry->offset + entry->size > ps2_embedded_asset_blob_size) return NULL;
			if (size != NULL) *size = entry->size;
			return ps2_embedded_asset_blob + entry->offset;
		}
		if (comparison < 0) high = middle;
		else low = middle + 1;
	}
	return NULL;
}

bool ps2_embedded_asset_exists(const char* path) {
	return ps2_embedded_asset_find(path, NULL) != NULL;
}

bool ps2_embedded_directory_exists(const char* path) {
	if (path == NULL) return false;
	path = normalize_asset_path(path);
	char prefix[POP_MAX_PATH];
	snprintf_check(prefix, sizeof(prefix), "%s/", path);
	size_t prefix_length = strlen(prefix);
	for (size_t index = 0; index < ps2_embedded_asset_count; ++index) {
		if (strncmp(ps2_embedded_asset_entries[index].path, prefix, prefix_length) == 0) return true;
	}
	return false;
}

SDL_RWops* ps2_embedded_asset_rwops(const char* path) {
	size_t size = 0;
	const unsigned char* data = ps2_embedded_asset_find(path, &size);
	if (data == NULL || size > INT_MAX) return NULL;
	return SDL_RWFromConstMem(data, (int)size);
}

static bool probe_storage_root(const char* device, const char* directory) {
	struct stat device_status;
	if (stat(device, &device_status) != 0) return false;

	mkdir(directory, 0777);
	struct stat directory_status;
	if (stat(directory, &directory_status) != 0 || !S_ISDIR(directory_status.st_mode)) return false;

	char probe_path[POP_MAX_PATH];
	snprintf_check(probe_path, sizeof(probe_path), "%s/.write-test", directory);
	FILE* probe = fopen(probe_path, "wb");
	if (probe == NULL) return false;
	static const char marker[] = "SDLPoP";
	bool ok = fwrite(marker, 1, sizeof(marker), probe) == sizeof(marker);
	if (fclose(probe) != 0) ok = false;
	remove(probe_path);
	if (!ok) return false;

	snprintf_check(ps2_selected_storage, sizeof(ps2_selected_storage), "%s", directory);
	return true;
}

bool ps2_storage_init(void) {
	if (ps2_selected_storage[0] != '\0') return true;
	// USB devices can need a moment after the IOP reset. A bounded retry keeps
	// SMB/HDD launches responsive when no flash drive is connected.
	for (int attempt = 0; attempt < 20; ++attempt) {
		if (probe_storage_root("mass:/", "mass:/SDLPoP-PS2")) return true;
		DelayThread(100000);
	}
	if (probe_storage_root("mc0:/", "mc0:/SDLPoP-PS2")) return true;
	return false;
}

const char* ps2_storage_root(void) {
	return ps2_selected_storage[0] != '\0' ? ps2_selected_storage : NULL;
}

const char* ps2_storage_path(const char* filename, char* dst, size_t size) {
	const char* root = ps2_storage_root();
	if (root == NULL) {
		snprintf_check(dst, size, "%s", filename);
	} else {
		snprintf_check(dst, size, "%s/%s", root, filename);
	}
	return dst;
}

#endif
