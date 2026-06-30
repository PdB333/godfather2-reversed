// FUNC_NAME: GhostSet::fetchObjectByIndex
// Function address: 0x0043b0e0
// Role: Retrieves the object pointer and its first field for a given index,
//       checking a bit array to determine if the slot is occupied. If the bit
//       is set (slot used), it clears output fields. Otherwise, it reads the
//       next object pointer from a linear array and advances the array pointer.

void GhostSet::fetchObjectByIndex()
{
    // Structure offsets:
    // +0x00: (unknown)
    // +0x04: byte* mBitArray          - pointer to bitfield marking used slots
    // +0x08: void** mObjectPtrArray   - pointer to an array of object pointers
    // +0x0c: uint32 mIndex            - current slot index to evaluate
    // +0x14: void* mCurrentObject     - output: pointer to the fetched object
    // +0x18: uint16 mStoredIndex      - copy of the index (truncated to 16 bits)
    // +0x1c: uint32 mObjectFirstField - output: first DWORD of the object's data

    uint32 index = *(uint32*)(this + 0x0c);
    *(uint16*)(this + 0x18) = (uint16)index;

    byte* bitArray = *(byte**)(this + 0x04);
    if ((bitArray[index >> 3] & (1 << (index & 7))) != 0)
    {
        // Slot is already in use: clear outputs and return
        *(void**)(this + 0x14) = nullptr;
        *(uint32*)(this + 0x1c) = 0;
        return;
    }

    // Slot is free: read the next object pointer from the array
    void** ptrArray = *(void***)(this + 0x08);
    void* objPtr = *ptrArray;                 // object pointer from array
    uint32 firstField = *(uint32*)objPtr;     // first DWORD of the object

    *(void**)(this + 0x14) = objPtr;
    *(uint32*)(this + 0x1c) = firstField;

    // Advance the array pointer by one pointer (4 bytes)
    *(void***)(this + 0x08) = ptrArray + 1;
}