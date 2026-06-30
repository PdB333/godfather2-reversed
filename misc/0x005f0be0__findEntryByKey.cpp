// FUNC_NAME: findEntryByKey
// Function address: 0x005f0be0
// Binary search in a sorted array of 0x18-byte structures (first field is uint key).
// Returns pointer to the found entry, or 0 if not found.
// Parameters: key (uint), array (pointer to first element), count (int, number of elements).
// The count is passed in EAX register (custom calling convention), but reconstructed as normal parameter.

struct SortedEntry {
    uint key;       // +0x00
    // ... remaining 0x14 bytes (0x18 total)
};

SortedEntry* findEntryByKey(uint key, SortedEntry* array, int count) {
    int low = 0;
    int high = count - 1;
    int mid;

    if (count <= 0) {
        return 0;
    }

    while (low <= high) {
        mid = (low + high) / 2;
        uint midKey = array[mid].key;
        if (key == midKey) {
            return &array[mid];
        }
        if (key < midKey) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}