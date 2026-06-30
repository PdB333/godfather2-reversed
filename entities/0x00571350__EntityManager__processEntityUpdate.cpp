// FUNC_NAME: EntityManager::processEntityUpdate
// Function at 0x00571350: Handles updating entity data for a given slot.
// Returns a status code (nonzero on success). On failure, original decompiler shows (in_EAX & 0xFFFFFF00) but we use 0 for consistency.

#include <cstdint>

// Forward declarations: global function and member function for data retrieval
uint32_t sub_586970(void);
uint32_t sub_579450(EntityManager* self, uint8_t* buffer); // possibly returns size or status

class EntityManager {
public:
    uint32_t processEntityUpdate(int32_t slotIndex);
};

uint32_t EntityManager::processEntityUpdate(int32_t slotIndex) {
    // Stack buffer to hold entity data (size unknown, assume at least 0x94 bytes)
    uint8_t localBuffer[0x94];

    // Check if this instance is valid and slot is not -1 (invalid)
    if (this != nullptr && slotIndex != -1) {
        // Global pre-update routine (e.g., frame sync, timer update)
        sub_586970();
        // Retrieve entity data into the local buffer; passes 'this' and buffer pointer
        return sub_579450(this, localBuffer);
    }
    // Failure: original assembly returns (EAX & 0xFFFFFF00) but we return 0 for clarity
    return 0;
}