// FUNC_NAME: releaseSlotEntry
void __thiscall releaseSlotEntry(int thisPtr, int slotIndex)
{
    // Get pointer to entry array: each entry is 8 bytes, first 4 bytes are pointer to managed object
    int* entryArray = *(int**)(thisPtr + 0x94); // +0x94: pointer to array of 8-byte entries
    int objectPtr = entryArray[slotIndex * 2];   // entry[slotIndex].pObject

    // Check if the object exists and its sub-object at offset +0x48 is non-null
    if (objectPtr != 0 && (objectPtr - 0x48) != 0)
    {
        int contextId = *(int*)(thisPtr + 0xf4); // +0xf4: context ID (e.g., thread or manager ID)
        if (contextId != -1)
        {
            // Release sub-object at offset +0x48 with context ID
            FUN_0043c5b0(objectPtr - 0x48, contextId);
        }
        // Release sub-object at offset +0x0c (no extra argument)
        FUN_004088c0(objectPtr - 0x0c);
    }

    // Mark the slot as free/removed
    FUN_0083ca20(slotIndex);
}