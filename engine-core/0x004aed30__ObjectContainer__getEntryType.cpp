// FUNC_NAME: ObjectContainer::getEntryType
#include <cstdint>

// Structure representing a container of 8-byte entries (e.g., an array of ghost objects or packet slots)
struct ObjectContainer {
    int* m_end;    // +0x8: pointer to the end of the allocated array (one past last entry)
    int* m_array;  // +0xC: pointer to the start of the entry array

    // Retrieves and checks the type of an entry by its index (1‑based)
    // Returns a status/type‑encoded value:
    //   - If the entry exists and its type is 3 or 4, returns (0x01000000 | (address high 24 bits))
    //   - Otherwise, returns address & 0xFFFFFF00 (low byte cleared)
    uint32_t getEntryType(int32_t index);
};

uint32_t ObjectContainer::getEntryType(int32_t index) {
    int32_t* entryPtr;

    // If index < 1, use a default/head entry returned by an external function
    if (index < 1) {
        entryPtr = (int32_t*)FUN_00625430();  // likely returns a base or first entry pointer
    } else {
        // Calculate address of the entry at 1‑based index: array + (index‑1)*8
        entryPtr = (int32_t*)(*(int32_t*)(this + 0xC) - 8 + index * 8);
        // Bounds check: if the computed address is beyond the end pointer, skip type check
        if (*(int32_t**)(this + 0x8) <= entryPtr) {
            goto out_of_bounds;
        }
    }

    // Check if the entry exists and its first field (type) is 3 or 4
    if (entryPtr != nullptr && (*entryPtr == 3 || *entryPtr == 4)) {
        // Return special value: high byte 0x01, low 24 bits = (address >> 8) & 0xFFFFFF
        return (uint32_t)(( (intptr_t)entryPtr >> 8 ) & 0xFFFFFF) | 0x01000000;
    }

out_of_bounds:
    // Default return: clear the low byte of the address (presumably to indicate invalid/untagged)
    return (uint32_t)entryPtr & 0xFFFFFF00;
}