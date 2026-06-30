// FUNC_NAME: SlotArray::getSlotData
// Address: 0x00625ae0
// Role: Retrieves a pointer from a slot array using an index; if index < 1, uses a default slot from another function.
// The array stores 8-byte entries: first 4 bytes = type (4 = valid), second 4 bytes = data pointer.
// Returns data pointer + 0xc if type is 4 or additional validation passes.

struct SlotArray {
    int* beginPtr;    // +0x08: end (or start?) – used for bounds check against slotPtr
    int* endPtr;      // +0x0c: base of the slot array (each slot is 8 bytes)
};

int* getDefaultSlot(); // FUN_00625430 – returns a slot pointer when index is < 1
int validateSlot();     // FUN_00633990 – returns non-zero if slot is valid

__thiscall void* SlotArray::getSlotData(int index) {
    int* slotPtr;
    int* dataPtr;

    // If index < 1, retrieve a default slot from another function
    if (index < 1) {
        slotPtr = getDefaultSlot();
    }
    else {
        // Calculate slot address: base + (index * 8) - 8? Actually -8 + index*8 = (index-1)*8, so index is 1-based?
        slotPtr = this->endPtr + (-8 + index * 8);
        // Bounds check: slotPtr must be >= beginPtr (assuming beginPtr is start, endPtr is end?)
        if (slotPtr <= this->beginPtr) {
            return 0;
        }
    }

    if (slotPtr != 0) {
        // Check slot type field (first int)
        if (*slotPtr == 4) {
            // Return data at offset 0xc from the object pointed by second int
            dataPtr = (int*)(*(slotPtr + 1));
            return (void*)(*(dataPtr + 3)); // *(dataPtr + 0xc / 4)
        }
        // If type is not 4, run additional validation
        if (validateSlot() != 0) {
            dataPtr = (int*)(*(slotPtr + 1));
            return (void*)(*(dataPtr + 3));
        }
    }
    return 0;
}