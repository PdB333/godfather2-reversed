// FUNC_NAME: ResourceSlotManager::releaseResourceByID

// Class: ResourceSlotManager
// Manages a fixed array of 9 resource slots (0-indexed) at offset 0x2E4.
// Each slot is 16 bytes (0x10) and contains a pointer to a dynamically allocated
// resource object. The resource object has an ID field at offset 0x48.

#include <cstddef>  // for offsetof if needed, but not used here

// Forward declaration: release function for a slot (likely frees memory and updates state)
void releaseSlot(void* slotPtr);  // Corresponds to FUN_004daf90

// Structure of a resource slot (size 0x10)
struct ResourceSlot {
    void* resourcePtr;       // +0x00: pointer to allocated resource object
    char unknown[0x0C];      // +0x04: remaining 12 bytes (possibly handle/refcount)
};

// Structure of the resource object (offset +0x48 holds ID)
struct ResourceObject {
    char unknown[0x48];      // +0x00..0x47: unknown fields
    int resourceID;          // +0x48: identifier used for matching
};

// Manager class that holds 9 resource slots at a fixed offset from 'this'
class ResourceSlotManager {
    // The following layout is assumed at compile time:
    // offset 0x000 - 0x2E3 : other members (irrelevant)
    // offset 0x2E4        : ResourceSlot slots[9];  // array of 9 slots (144 bytes)
    // The slot array starts at (this + 0x2E4).
    // Each slot is 16 bytes.
    // Slots are 0-indexed.

public:
    void releaseResourceByID(int resourceID);  // Replaces FUN_008fa130
};

void ResourceSlotManager::releaseResourceByID(int resourceID) {
    // Iterate over the 9 slots
    int idx = 0;
    // Use a pointer stepping by 4 bytes (size of resourcePtr) to loop through slots
    // This works because resourcePtr is the first member of each 16-byte slot.
    int* slotResourcePtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2E4);

    while (true) {
        int comparisonID;
        if (*slotResourcePtr == 0) {
            comparisonID = 0;
        } else {
            // The resource object's ID is at offset 0x48 from the pointer
            ResourceObject* res = reinterpret_cast<ResourceObject*>(*slotResourcePtr);
            comparisonID = reinterpret_cast<int*>(res)[0x48 / sizeof(int)]; // offset 0x48
            // Equivalent to: comparisonID = res->resourceID;
        }

        if (comparisonID == resourceID)
            break;  // Found matching slot

        idx++;
        slotResourcePtr += 1;  // Move to next slot (increment by 4 bytes = one pointer)
        if (idx > 8)           // 9 slots (indices 0..8)
            return;            // Not found, exit
    }

    // Recalculate the slot pointer to point to the beginning of the 16-byte slot
    // slotStart = (this + 0x2E4) + idx * 0x10
    void* slotStart = reinterpret_cast<char*>(this) + 0x2E4 + idx * 0x10;

    // If the slot's resource pointer is non‑null, release it
    if (*reinterpret_cast<int*>(slotStart) != 0) {
        releaseSlot(slotStart);
        // Clear the resource pointer in the slot (now zero indicates empty)
        *reinterpret_cast<int*>(slotStart) = 0;
    }

    return;
}