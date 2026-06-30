// FUNC_NAME: SlotTable::findOrAllocateEntry

#include <cstdint>

// Structure for a 20-byte slot in the table
struct SlotEntry {
    uint8_t data[20]; // exact layout unknown, but consists of two uint64-like fields and a pointer
};

// Global table base (0x01206408)
// This is a fixed-size array of 32 SlotEntry objects
static SlotEntry g_slotTable[32];

// Global reference pattern to search for (0x00e274ac)
static const SlotEntry g_pattern; // Initialized elsewhere

// Returns index of existing matching slot, or allocates a new one, or -1 if table full
int SlotTable::findOrAllocateEntry() {
    int index = 0;
    SlotEntry* current = g_slotTable;

    while (reinterpret_cast<intptr_t>(current) < reinterpret_cast<intptr_t>(g_slotTable + 32)) {
        // Compare the current slot with g_pattern (20 bytes)
        uint32_t remaining = 20;
        uint8_t* pSlot = reinterpret_cast<uint8_t*>(current);
        uint8_t* pPattern = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(&g_pattern));

        bool match = true;
        while (remaining > 0) {
            // Compare up to 4 bytes at a time where possible
            if (remaining >= 4) {
                if (*reinterpret_cast<uint32_t*>(pSlot) != *reinterpret_cast<uint32_t*>(pPattern)) {
                    match = false;
                    break;
                }
                pSlot += 4;
                pPattern += 4;
                remaining -= 4;
            } else {
                // Compare remaining bytes one by one
                for (uint32_t i = 0; i < remaining; ++i) {
                    int diff = pSlot[i] - pPattern[i];
                    if (diff != 0) {
                        match = false;
                        break;
                    }
                }
                break;
            }
        }

        if (match) {
            // Exact match found
            return index;
        }

        ++current;
        ++index;
    }

    // No match found; search for an empty slot (first 8 bytes zero)
    for (int i = 0; i < 32; ++i) {
        if (*reinterpret_cast<uint64_t*>(&g_slotTable[i]) == 0) {
            // Found empty slot; copy the pattern into it
            // Copy first 8 bytes
            *reinterpret_cast<uint64_t*>(&g_slotTable[i]) = *reinterpret_cast<const uint64_t*>(&g_pattern);
            // Copy next 8 bytes (at offset 8)
            *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(&g_slotTable[i]) + 8) = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(&g_pattern) + 8);
            // Copy remaining 4 bytes (pointer at offset 16)
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(&g_slotTable[i]) + 16) = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(&g_pattern) + 16);

            return i;
        }
    }

    // Table is full
    return -1;
}