// FUNC_NAME: HandleArray::releaseByIndex
// Address: 0x006bb160
// This function releases the object associated with a given index in a handle array.
// The array is stored at offset +0xA0 from this, each entry is 0x18 bytes.
// The first field of an entry is a pointer to the object's internal data minus 0x48.
// After cleanup, bit 26 (0x04000000) is cleared in the object's flags at offset +0x5C.

int __thiscall HandleArray::releaseByIndex(int thisPtr, int slotIndex)
{
    // Pointer to the slot entry in the array (each entry 0x18 bytes)
    int* slotEntryPtr = (int*)(*(int*)(thisPtr + 0xA0) + slotIndex * 0x18);
    int releasedObject;

    if (*slotEntryPtr == 0) {
        releasedObject = 0;
    }
    else {
        // The stored pointer points to an internal structure; the actual object base is at -0x48
        releasedObject = *slotEntryPtr - 0x48;
        // Call cleanup routine for the slot entry (likely decrements refcount or frees resources)
        cleanupSlotEntry(slotEntryPtr);
        // Clear the slot pointer
        *slotEntryPtr = 0;
    }

    // Clear bit 26 (0x04000000) in the object's flags to mark it as released/inactive
    *(unsigned int*)(releasedObject + 0x5C) &= 0xFBFFFFFF;

    return releasedObject;
}