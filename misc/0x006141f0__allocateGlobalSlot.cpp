// FUNC_NAME: allocateGlobalSlot
//
// Function at 0x006141f0: Allocates a slot from a fixed-size global array of 12-byte entries.
// Iterates through up to 4 entries; if the flag at offset +8 is null, stores two parameters
// and marks the entry as occupied. Returns the slot index or -1 if full.

// Global data referenced:
// 0x011f6bb8: base of entry data (first field)
// 0x011f6bbc: second field (param2)
// 0x011f6bc0: flag byte (written as int 1)
// Each entry is 0xC bytes.

#define MAX_SLOTS 4

struct GlobalSlotEntry {
    int param1;      // +0x00
    int param2;      // +0x04
    int usedFlag;    // +0x08 (treated as char in check, but stored as int)
};

// Global array of MAX_SLOTS entries
static GlobalSlotEntry g_slotEntries[MAX_SLOTS];

// Initialize the array pointers from the known addresses.
// In the actual binary these are placed at fixed addresses; here we use normal array.
// The code writes directly to those addresses, so we reinterpret_cast.
// For clarity, we just present the logic as operating on the global array.

int allocateGlobalSlot(int param1, int param2)
{
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (g_slotEntries[i].usedFlag == 0) {
            g_slotEntries[i].param1 = param1;
            g_slotEntries[i].param2 = param2;
            g_slotEntries[i].usedFlag = 1;
            return i;
        }
    }
    return -1;
}