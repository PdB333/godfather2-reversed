// FUNC_NAME: ObjectTableManager::setObjectParam
// Address: 0x005e7b20
// Role: Sets a parameter (at +0x6c) on an object identified by a scrambled ID.
// The ID is XORed with 0xad103100 to obtain an index into a global hash table (256 slots max).
// If the slot has a valid pointer, the value is written to offset 0x6c of that object.

#include <cstdint>

// Global pointer to the object table header (DAT_01223504)
// Structure: [byte count at +0x1c] [array of 4-byte pointers at +4]
static uint8_t* g_pObjectTableHeader = reinterpret_cast<uint8_t*>(0x01223504);

// Hash constant used to unscramble the ID
static const uint32_t HASH_XOR = 0xad103100;

// Offset of the parameter field within the target object
static const uint32_t FIELD_OFFSET = 0x6c;

// Inner struct representing the table header (for clarity)
struct ObjectTableHeader {
    uint8_t _pad0[0x1c];          // +0x00 padding to +0x1c
    uint8_t slotCount;            // +0x1c number of slots (must be <= 256)
    uint32_t slots[1];            // +0x20 (actually at +0x04 from base) array of pointers
};

bool ObjectTableManager::setObjectParam(uint32_t scrambledId, int32_t value) {
    // Unscramble the ID to get the actual slot index
    uint32_t index = scrambledId ^ HASH_XOR;

    // Check if the index is within the slot count
    ObjectTableHeader* header = reinterpret_cast<ObjectTableHeader*>(g_pObjectTableHeader);
    if (index >= header->slotCount) {
        return false;
    }

    // Get the pointer from the slot array (index is masked to low byte as per Ghidra)
    uint32_t* slotArray = reinterpret_cast<uint32_t*>(g_pObjectTableHeader + 4); // array of pointers
    uint32_t slotIndex = index & 0xFF; // ensure 8-bit index (though already < slotCount <= 256)
    uint32_t objectPtr = slotArray[slotIndex];

    if (objectPtr == 0) {
        return false;
    }

    // Write the value to the object's field at +0x6c
    *reinterpret_cast<int32_t*>(objectPtr + FIELD_OFFSET) = value;
    return true;
}