// FUNC_NAME: findEntryByFilename
// Address: 0x00444bf0
// Role: Locates a resource entry in a hash map by computing a case-insensitive hash of the base filename (without path or extension).
//        Uses a linear search with hash prefiltering. The hash table is stored as a dynamic array of pointers to entries,
//        each entry having a hash field at offset 0. The container structure is at +0x10 of the manager object.

struct HashArray {
    void** entries; // +0x00: begin of pointer array
    int count;      // +0x04: number of entries
};

struct Entry {
    int hash;       // +0x00: hash value of filename
    // ... additional data follows (unknown size)
};

// Returns pointer to the Entry if found, nullptr otherwise.
Entry* __fastcall findEntryByFilename(const char* filename, void* containerBase) {
    Entry* result = nullptr;

    if (filename != nullptr) {
        int hash = 0;
        const char* baseName = filename;

        // Extract the base name: skip last path separator ('\\' or '/')
        while (*filename) {
            if (*filename == '\\' || *filename == '/') {
                baseName = filename + 1;
            }
            filename++;
        }

        // Compute hash of the base name (excluding the extension '.' and after)
        // Converts uppercase letters to lowercase for case-insensitivity.
        while (*baseName && *baseName != '.') {
            byte c = (byte)*baseName;
            if (c >= 'A' && c <= 'Z') {
                c = c + 0x20; // to lowercase
            }
            hash = hash * 0x1003f + c; // 65599 multiplier (common hash)
            baseName++;
        }

        // Retrieve the hash array from the container
        HashArray* array = *(HashArray**)((byte*)containerBase + 0x10);
        void** entries = array->entries;
        void** end = entries + array->count;

        if (entries != end) {
            do {
                if (hash == *(int*)*entries) {
                    result = (Entry*)*entries;
                }
                entries++;
            } while (entries != end);
        }
    }
    return result;
}