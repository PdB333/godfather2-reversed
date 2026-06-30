// FUNC_NAME: SlotContainer::isSlotValidAndType34
bool __fastcall SlotContainer::isSlotValidAndType34(void* thisPtr, int index) {
    int* slotPtr;

    if (index < 1) {
        // Handle index 0 specially; get pointer from helper (likely returns first slot)
        slotPtr = (int*)FUN_00625430();
    } else {
        // Compute pointer to element at given index.
        // The container stores a pointer to the element at index 1 in [this+0xC].
        // For index i (>=1), the element address is (*(int**)(this+0xC) - 8) + i * 8
        slotPtr = (int*)((*(int*)((uint8_t*)thisPtr + 0xC)) - 8 + index * 8);
        // Check if the computed pointer is beyond the end pointer stored at [this+0x8]
        int* endPtr = *(int**)((uint8_t*)thisPtr + 8);
        if (endPtr <= slotPtr) {
            return false;  // Out of bounds
        }
    }

    // If slotPtr is valid and its type (first int) is 3 or 4, return true.
    if (slotPtr != nullptr && (*slotPtr == 3 || *slotPtr == 4)) {
        return true;
    }
    return false;
}