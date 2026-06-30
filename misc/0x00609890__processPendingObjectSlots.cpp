// FUNC_NAME: processPendingObjectSlots

// Function at 0x00609890: Processes pending object slots based on a bitmask.
// Iterates over 5 slots (0-4). For each slot, checks a specific bit in the mask:
//   - Slot 4 uses bit 1 (value 2)
//   - All other slots use bit 0 (value 1)
// If the bit is set and the slot's object ID is non-zero, retrieves the object data
// from a global table (0x38 bytes per entry) and calls processObject().

#include <cstdint>

// Global array of object IDs for each slot (5 slots, each 8 bytes? Only first 4 bytes used)
// Offset from base: slotIndex * 8
extern uint32_t g_slotObjectIds[10]; // Actually accessed as g_slotObjectIds[slotIndex * 2]

// Global table of object data blocks (0x38 bytes each), indexed by object ID
// Base address: 0x011a0f28
extern uint8_t g_objectDataTable[]; // Each entry is 0x38 bytes

// Forward declaration of the function that processes a single object
void processObject(uint32_t objectId, void* objectData);

void processPendingObjectSlots(uint8_t slotMask)
{
    for (int slotIndex = 0; slotIndex < 5; ++slotIndex)
    {
        uint8_t slotBit;
        if (slotIndex == 4)
        {
            slotBit = slotMask & 2; // Bit 1 for slot 4
        }
        else
        {
            slotBit = slotMask & 1; // Bit 0 for other slots
        }

        if (slotBit != 0)
        {
            uint32_t objectId = g_slotObjectIds[slotIndex * 2]; // Read first uint32 of slot entry
            if (objectId != 0)
            {
                void* objectData = nullptr;
                if (objectId < 0x1000)
                {
                    // Each object data block is 0x38 bytes
                    objectData = &g_objectDataTable[objectId * 0x38];
                }
                processObject(objectId, objectData);
            }
        }
    }
}