// FUNC_NAME: CSlotManager::tryAllocateSlot
// Address: 0x006ace40
// Role: Attempts to allocate a slot from a fixed-size pool (max 20) using a resource ID.
// Array at +0x2c: each entry is 0x30 bytes, first byte is a busy flag (LSB=1 means busy).
// If validated index > 19, searches for first free slot and initializes it.

#include <cstdint>

class CSlotManager {
public:
    // Validates resource ID, returns something (maybe an index or status)
    uint32_t validateResourceId(uint32_t resourceId); // FUN_006ac320

    // Initializes a slot for the given resource (probably marks slot as busy)
    static void initializeSlotForResource(uint32_t resourceId); // FUN_006abe80

    // Called after slot is allocated (global or static)
    static void onSlotAllocated(); // FUN_006acd80

    void tryAllocateSlot(uint32_t resourceId);
};

void CSlotManager::tryAllocateSlot(uint32_t resourceId) {
    uint32_t validatedIndex = this->validateResourceId(resourceId);
    if (validatedIndex > 19) { // 0x13 = 19
        int index = 0;
        uint8_t* slotFlagPtr = reinterpret_cast<uint8_t*>(this) + 0x2c; // base of flag array
        while ((~(*slotFlagPtr) & 1) == 0) { // while slot is busy (flag bit0 == 1)
            index++;
            slotFlagPtr += 0x30; // each slot is 48 bytes
            if (index > 19) {
                return; // no free slot found
            }
        }
        // Found free slot at index, initialize it
        CSlotManager::initializeSlotForResource(resourceId);
        CSlotManager::onSlotAllocated();
    }
}