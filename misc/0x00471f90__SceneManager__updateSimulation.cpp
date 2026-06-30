// FUNC_NAME: SceneManager::updateSimulation
bool __fastcall SceneManager::updateSimulation(int* thisPtr)
{
    // thisPtr is a pointer to a SceneManager object
    // Offsets used:
    // +0x40: double timeValue (simulation time)
    // +0x108: int unknownInt (iVar1)
    // +0x15E: short maybePausedFlag
    // +0x4c: vtable function (likely getTimeScale or similar)

    double currentTime;
    float timeHigh;
    float fVar2;
    int unknownInt;
    float tempFloat;
    int resultFlag;

    // Read the 64-bit double at +0x40 and extract high 32 bits as float
    timeHigh = (float)((unsigned long long)(*(uint64_t*)(thisPtr + 0x40)) >> 32);
    fVar2 = timeHigh + DAT_00e35654; // Add a constant time delta (maybe frame time)

    unknownInt = thisPtr[0x42]; // Offset 0x108

    // Recombine low 32 bits of original double with modified high part
    currentTime = (double)( (uint64_t)( (uint32_t)(fVar2) ) << 32 | (*(uint64_t*)(thisPtr + 0x40) & 0xFFFFFFFF) );

    // Check a short flag at +0x15E
    if ( (*(short*)((int)thisPtr + 0x15E) >= 0) )
    {
        // Virtual call through vtable offset 0x4c (returns a double-like structure via pointer)
        // This function likely returns a double value or a struct in local_dc (edx:eax)
        double someDouble;
        (*(void (__fastcall**)(int*, double*))(*(int*)thisPtr + 0x4c))(thisPtr, &someDouble);

        // If the high 32 bits of that double are negative, apply additional delta
        if ( *(int*)((char*)&someDouble + 4) < 0 )
        {
            fVar2 = DAT_012067e8 * someDouble + fVar2;
            currentTime = (double)( (uint64_t)( (uint32_t)(fVar2) ) << 32 | (*(uint64_t*)(thisPtr + 0x40) & 0xFFFFFFFF) );
        }
    }

    // Prepare parameters for a function call (likely a message/event processing)
    double paramDouble; // This will be set to currentTime
    paramDouble = currentTime;

    // Build a local struct that will be passed to FUN_009e5ed0
    // This struct seems to contain multiple fields: type, flags, time, coordinates, etc.
    int localBuffer[14]; // approximate size, not exact
    int* pBuffer = localBuffer;

    localBuffer[0] = 0x3E0; // Some type or size (1008)
    localBuffer[1] = 2;    // Subtype or mode
    localBuffer[2] = 0x80000000; // Flag
    localBuffer[3] = 0;    // Maybe padding
    localBuffer[4] = 0;    // Maybe padding

    // The next fields relate to the time and unknownInt
    *(double*)(&localBuffer[5]) = currentTime; // Actually at offset 0x14 from buffer, but careful with alignment
    *(int*)(&localBuffer[5] + 8) = unknownInt; // Store at offset 0x1C? Might need adjustment

    // Another time/delta field
    *(float*)((char*)localBuffer + 0x20) = fVar2 - DAT_00e2b050; // Some derived value
    *(int*)((char*)localBuffer + 0x24) = unknownInt;
    *(int*)((char*)localBuffer + 0x28) = unknownInt; // iStack_b8 = iVar1

    // Set up a pointer to a function table (vtable for the struct?)
    void* vtablePtr = &PTR_FUN_00e32a8c; // external reference

    // Call the function to process the buffer
    FUN_009e5ed0(&localBuffer[5], &vtablePtr); // Pass pointers to buffer and vtable

    // Return whether a flag was set (resultFlag)
    return resultFlag != 0;
}