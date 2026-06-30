// FUNC_NAME: HandleTable::findEntry
uint __thiscall HandleTable::findEntry(uint handle, int *outPtr, uint *outExtraData)
{
    // Offset 0x0C: entryCount (uint)
    // Offset 0x10: entries array (each entry: 3 uint32s: key, relativeOffset, extraData)
    uint entryCount = *(uint *)(this + 0x0C);
    uint *entryPtr = (uint *)(this + 0x10);

    // Default return: high 24 bits of the handle passed in EAX (previous handle or similar)
    // When table empty, caller expects this value.
    uint result = in_EAX & 0xFFFFFF00;

    *outPtr = 0;
    *outExtraData = 0;

    if (entryCount != 0)
    {
        for (uint i = 0; i < entryCount; i++)
        {
            if (*entryPtr == handle)
            {
                // Found: entry structure: [key, relativeOffset, extraData]
                uint relativeOffset = entryPtr[1];
                *outPtr = relativeOffset + this;
                *outExtraData = entryPtr[2];

                // Build handle: (absolute pointer) & 0xFFFFFF00 | 1
                // The low bit 1 indicates a valid resolved handle.
                result = ((relativeOffset + this) & 0xFFFFFF00) | 1;
                break;
            }
            entryPtr += 3;
        }
    }

    // If not found, return handle's high 24 bits (as in param_2 & 0xFFFFFF00)
    // Note: When table is empty, result is from in_EAX; otherwise return with error code.
    return result;
}