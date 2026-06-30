// FUNC_NAME: HandleManager::releaseHandle
// Address: 0x005e7b60
// Releases a handle from a fixed-size slot allocator. The handle is provided via a pointer (ESI).
// The global structure at DAT_01223504 manages up to 256 slots, with metadata at offsets +0x1c (max free count) and +0x1d (current free count).
// Slots are stored as bytes starting at offset +0x18.
// The handle is XORed with 0xAD103100 to produce an index (low byte) into the slot array.
// If the slot is non-zero, it is cleared, the count is decremented, and the handle pointer is zeroed.

#include <cstdint>

// Forward declaration of the global handle manager structure
struct HandleManager {
    // Unknown header bytes (0x00–0x17)
    uint8_t header[0x18];                   // +0x00
    // Slot array: each byte indicates whether the slot is in use (non-zero) or free (0)
    uint8_t slots[256];                     // +0x18
    // Max number of simultaneously active handles (derived from slots[4])
    // uint8_t maxCount;                    // +0x1c (alias for slots[4])
    // Current count of active handles (slots[5])
    // uint8_t currentCount;                // +0x1d (alias for slots[5])
};

static HandleManager* gHandleMgr = reinterpret_cast<HandleManager*>(0x01223504);

// ESI is assumed to be a pointer to a uint32_t that holds the handle to be released.
uint8_t HandleManager::releaseHandle(uint32_t* handlePtr) {
    uint8_t result = 0;                     // default return: not released

    if (handlePtr == nullptr)
        return result;

    uint32_t hash = *handlePtr ^ 0xAD103100;
    uint32_t maxCount = gHandleMgr->slots[4]; // from offset +0x1c

    // Check if hash is within the valid range (below maxCount)
    if (hash < maxCount) {
        uint8_t slotIndex = hash & 0xFF;   // low byte of hash
        uint8_t* slot = &gHandleMgr->slots[slotIndex]; // +0x18 + slotIndex

        // Proceed only if the slot is currently occupied (non-zero)
        if (*slot != 0) {
            // Decrement the global current count (offset +0x1d)
            gHandleMgr->slots[5]--;
            // Clear the slot
            *slot = 0;
            // Zero out the handle to indicate it's been released
            *handlePtr = 0;
            result = 1;                     // success
        }
    }
    return result;
}