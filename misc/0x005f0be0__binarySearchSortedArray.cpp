// FUNC_NAME: binarySearchSortedArray
// Address: 0x005f0be0
// Binary search over a sorted array of 0x18-byte entries.
// The first 4 bytes of each entry are a uint32_t key.
// The caller passes the highest valid index (count-1) in EAX.
// Returns pointer to the matching entry, or nullptr (0) if not found.

struct SortedEntry {
    uint32_t key;      // +0x00
    // rest is 0x14 bytes of data (total 0x18)
};

// Note: The original calling convention uses EAX to pass highIndex (the last index).
// For clarity, we include it as an explicit parameter here.
// In the binary, this function is called with __cdecl or __fastcall convention.
SortedEntry* binarySearchSortedArray(uint32_t key, SortedEntry* array, int highIndex) {
    int low = 0;
    int mid;
    
    if (highIndex < 0) {
        return nullptr;
    }
    
    while (low <= highIndex) {
        mid = (highIndex + low) / 2;
        uint32_t midKey = array[mid].key;
        if (key == midKey) {
            return &array[mid];
        }
        if (key < midKey) {
            highIndex = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return nullptr;
}