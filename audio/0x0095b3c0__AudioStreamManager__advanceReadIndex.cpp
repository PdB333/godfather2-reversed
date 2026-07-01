// FUNC_NAME: AudioStreamManager::advanceReadIndex
void __thiscall AudioStreamManager::advanceReadIndex(
    int *this,                    // +0x00 this pointer
    uint bufferSize,              // param_2 - size of ring buffer
    uint *pIndex,                 // param_3 - pointer to current index
    int offset,                   // param_4 - offset to advance (may be negative)
    uint paramFlags,              // param_5 - flags or secondary data
    undefined4 *pInputData,       // param_6 - input data structure (12 bytes)
    undefined4 *pDefaultData      // param_7 - default data when bufferSize==0
)
{
    undefined4 localStruct[3];    // local_c, local_8, local_4 - 12-byte struct
    undefined4 vtableResult;

    if (bufferSize > 1)
    {
        // Reset index if it was invalid (-1)
        if (*pIndex == 0xFFFFFFFF)
        {
            *pIndex = 0;
        }
        else
        {
            // Handle negative offset: wrap backwards using absolute value modulo size
            if (offset < 0)
            {
                offset = bufferSize - ((offset ^ (offset >> 0x1f)) - (offset >> 0x1f)) % bufferSize;
            }
            // Circular increment
            *pIndex = (offset + *pIndex) % bufferSize;
        }

        // Prepare a temporary struct from input data, then clear the remaining bytes
        localStruct[0] = *pInputData;
        localStruct[1] = 0;
        localStruct[2] = 0;
        // Zero the struct (likely to reset some state)
        memory_Set(&localStruct, 0);        // FUN_00408a00

        // Log the event with debug string (e.g., "stream")
        debugPrint(paramFlags, 0, &DAT_00d8ca78, 0);  // FUN_005a04a0

        // Call vtable method at offset 0x9c to get some object, then pass it to callback
        vtableResult = (**(code **)(*this + 0x9c))();  // likely getCurrentBuffer()
        handleCallback(vtableResult);                   // FUN_0097b8e0
        return;
    }

    if (bufferSize == 0)
    {
        // When buffer size is zero, use default data directly
        localStruct[0] = *pDefaultData;
        localStruct[1] = 0;
        localStruct[2] = 0;
        memory_Set(&localStruct, 0);
    }
    return;
}