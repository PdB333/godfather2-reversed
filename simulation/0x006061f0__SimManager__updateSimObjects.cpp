// FUNC_NAME: SimManager::updateSimObjects
// Address: 0x006061f0
// This function iterates over the global sim object table (indices 1..4095) and calls
// updateSimObject() on any entry that is allocated (first byte non-zero) and not marked as dead
// (bit 7 at offset 0x0c cleared). Each entry is 0x38 bytes.
// The table is stored at DAT_011a0f60 (gSimObjectTable).
// Offsets:
//   +0x00 : byte – non‑zero if slot is in use (e.g. type/name)
//   +0x0c : byte – bit 7 = dead flag (1 means dead, skip)

struct SimObject {
    char unknown00[0x0c]; // +0x00
    char flags;           // +0x0c: bit7 = dead
    char unknown0d[0x2b]; // +0x0d to +0x37
};

// Forward declaration of the per‑object update function
void updateSimObject(uint objectIndex, int arg);

void SimManager::updateSimObjects() {
    // The global table; index 0 is reserved (unused)
    SimObject* simObjectTable = (SimObject*)0x011a0f60;

    uint objectIndex = 1;                // start at index 1
    SimObject* entry = &simObjectTable[1]; // pointer to first valid entry
    int loopCount = 0xfff;               // process indices 1..4095 (0xfff iterations)

    do {
        char* raw = (char*)entry;

        // Check if slot is allocated and not dead
        if (*raw != '\0' && ((raw[0x0c] & 0x80) == 0)) {
            updateSimObject(objectIndex, 0); // second parameter is 0 (maybe update type)
        }

        objectIndex++;
        entry++;
        loopCount--;
    } while (loopCount != 0);
}