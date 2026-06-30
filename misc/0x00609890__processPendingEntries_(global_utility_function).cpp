// FUNC_NAME: processPendingEntries (global utility function)
// Address: 0x00609890
// Purpose: Iterates over 5 pending entry slots, processes those whose corresponding flag bit is set in processFlags.
// Slots 0-3 are controlled by bit 0 (flag 0x01), slot 4 by bit 1 (flag 0x02).
// Each slot holds a handle (uint) from gPendingHandleTable; if valid (non-zero and < 0x1000), 
// retrieves a descriptor from gObjectDescriptorTable at offset handle * 0x38 and calls processDescriptorEntry.
// The descriptor table has 0x38-byte entries.

#include <cstdint>

// Size of each descriptor entry: 0x38 = 56 bytes
struct DescriptorEntry {
    uint8_t data[0x38]; // opaque struct
};

// Global tables
// gPendingHandleTable: array of 5 uint32 entries, accessed with stride 2 (indices 0,2,4,6,8)
// gObjectDescriptorTable: base pointer, each entry is 0x38 bytes
extern uint32_t gPendingHandleTable[5 * 2]; // actually 5 elements at indices 0,2,4,6,8
extern DescriptorEntry* gObjectDescriptorTable; // base address of descriptor array

// Forward declaration of the descriptor processing function
void processDescriptorEntry(uint32_t handle, DescriptorEntry* entry);

void processPendingEntries(uint8_t processFlags) {
    int32_t slotIndex = 0;

    do {
        uint8_t bitMask;
        if (slotIndex == 4) {
            bitMask = processFlags & 0x02; // slot 4 uses bit 1
        } else {
            bitMask = processFlags & 0x01; // slots 0-3 use bit 0
        }

        if ((bitMask != 0) && (gPendingHandleTable[slotIndex * 2] != 0)) {
            uint32_t handle = gPendingHandleTable[slotIndex * 2];
            DescriptorEntry* entry = nullptr;

            // Only process if handle is within valid range (< 4096)
            if (handle < 0x1000) {
                entry = &gObjectDescriptorTable[handle]; // each entry is 0x38 bytes
            }

            processDescriptorEntry(handle, entry);
        }

        slotIndex++;
    } while (slotIndex < 5);
}