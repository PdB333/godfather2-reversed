// FUNC_NAME: ResourceManager::findEntryByFilename
// Function address: 0x005d17d0
// Searches an array of resource entries (type 3 or 4) by filename (case-insensitive).
// Extracts the filename from a full path (handles '/' and '\\').
// Returns pointer to matching entry or NULL.

// Assumed structure of a resource entry (size 0xd4)
struct ResourceEntry {
    // char unknown[0x30];
    int     type;        // +0x30 (compared to 3 or 4)
    char    filename[0xa0]; // +0x34 (160 bytes, enough for a filename)
};

// The class containing the array
class ResourceManager {
public:
    char unknown_header[4]; // +0x00 (maybe size or something)
    ResourceEntry entries[192]; // +0x04 (each 0xd4 bytes)
    // total size at least 0x04 + 192*0xd4 = 0x04 + 0xa8c0 = 0xa8c4
};

// __thiscall (ECX = this)
ResourceEntry* __thiscall ResourceManager::findEntryByFilename(const char* fullPath)
{
    const char* iter = fullPath;
    const char* filename = nullptr; // will point to last component

    // Find the last slash or backslash
    while (*iter != '\0') {
        iter++;
    }
    iter--; // now points to last char before terminator

    // Scan backwards looking for separator
    while (iter >= fullPath) {
        if (*iter == '/' || *iter == '\\') {
            filename = iter + 1;
            break;
        }
        iter--;
    }
    if (filename == nullptr) {
        filename = fullPath; // no separator, use whole path
    }

    // Search the entries array
    // Entries start at offset +0x04 from this, so first entry at (this+4)
    ResourceEntry* entry = reinterpret_cast<ResourceEntry*>(reinterpret_cast<char*>(this) + 0x04);
    for (int i = 0; i < 192; i++) {
        // Check type: must be 3 or 4
        if (entry->type == 3 || entry->type == 4) {
            // Compare filename (case-insensitive)
            if (_stricmp(filename, entry->filename) == 0) {
                return entry;
            }
        }
        entry++; // advance by 0xd4 bytes (sizeof ResourceEntry)
    }
    return nullptr;
}