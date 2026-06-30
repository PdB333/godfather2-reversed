// FUNC_NAME: AudioDataManager::applyConfiguration
void __fastcall AudioDataManager::applyConfiguration(int thisPtr)
{
    // Global singleton storage
    AudioDataManager* pThis = (AudioDataManager*)thisPtr;
    *(int*)0x012058e8 = thisPtr;

    // Release previous banks/streams if any
    releaseResource(*(int*)(thisPtr + 0x10));   // +0x10: bank manager
    releaseResource(*(int*)(thisPtr + 0x14));   // +0x14: stream manager

    uint bankSetIndex = *(byte*)(thisPtr + 0xb0);   // +0xb0: current bank set index
    uint streamSetIndex = *(byte*)(thisPtr + 0xb1); // +0xb1: current stream set index

    // --- Bank set configurations (arrays of 0x30 byte structs) ---
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x23c); // +0x23c: array of bank set entries (each 0x30)
        if (field)
            setResourceData(*(int*)(thisPtr + 0x10), field, thisPtr + 0xd0); // +0xd0: buffer for bank data 1
    }
    {
        int* field = *(int**)(thisPtr + (bankSetIndex + 0xc) * 0x30); // array at base (offset 0), index bankSetIndex+12
        if (field)
            setResourceBuffer(*(int*)(thisPtr + 0x10), field, thisPtr + 0xe0); // +0xe0: buffer for bank data 2
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x260); // +0x260: another bank field
        if (field)
            setResourceBuffer(*(int*)(thisPtr + 0x10), field, thisPtr + 0x160); // +0x160: buffer
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x264); // +0x264
        if (field)
            setResourceWithExtra(*(int*)(thisPtr + 0x10), field, thisPtr + 0x160, 3); // +0x160: same buffer, extra param=3
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x258); // +0x258 (600 decimal)
        if (field)
        {
            // 4-component vector (color, direction, etc.)
            Vector4 vec;
            vec.x = *(float*)(thisPtr + 0xc4);
            vec.y = 0.0f;
            vec.z = 0.0f;
            vec.w = 0.0f;
            setResourceData(*(int*)(thisPtr + 0x10), field, &vec);
        }
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x254); // +0x254
        if (field)
            setResourceBuffer(*(int*)(thisPtr + 0x10), field, thisPtr + 0x120); // +0x120
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x268); // +0x268
        if (field)
        {
            void* dataPtr;
            if (*(char*)(thisPtr + 0xc8) == 0) // +0xc8: quality flag? (high if true)
                dataPtr = (void*)0x00e2e770; // low quality data
            else
                dataPtr = (void*)0x011280d0; // high quality data
            setResourceData(*(int*)(thisPtr + 0x10), field, dataPtr);
        }
    }
    {
        int* field = *(int**)(thisPtr + bankSetIndex * 0x30 + 0x25c); // +0x25c
        if (field)
            setResourceData(*(int*)(thisPtr + 0x10), field, thisPtr + 0x1b0); // +0x1b0
    }

    // --- Stream set configurations (arrays of 0x3c byte structs) ---
    {
        int* field = *(int**)(thisPtr + 0x300 + streamSetIndex * 0x3c); // +0x300: array of stream set entries (each 0x3c)
        if (field)
        {
            void* dataPtr;
            if (*(char*)0x01163840 == 0) // global quality flag? (maybe stereo/mono)
                dataPtr = (void*)0x00e2e760;
            else
                dataPtr = (void*)0x01163810;
            setResourceData(*(int*)(thisPtr + 0x14), field, dataPtr); // +0x14: stream manager
        }
    }
    {
        int* field = *(int**)(thisPtr + 0x304 + streamSetIndex * 0x3c); // +0x304
        if (field)
        {
            void* dataPtr;
            if (*(char*)0x01163840 == 0)
                dataPtr = (void*)0x00e2e720;
            else
                dataPtr = (void*)0x011637d0;
            setResourceBuffer(*(int*)(thisPtr + 0x14), field, dataPtr);
        }
    }
    // Several checks for non-zero pointers that do nothing but call debugLog
    if (*(int*)(thisPtr + 0x2cc + streamSetIndex * 0x3c) != 0)   // +0x2cc
        debugLog();
    if (*(int*)(thisPtr + (streamSetIndex + 0xc) * 0x3c) != 0)   // array at base (offset 0), index streamSetIndex+12
        debugLog();
    if (*(int*)(thisPtr + 0x2dc + streamSetIndex * 0x3c) != 0)   // +0x2dc
        debugLog();
    if (*(int*)(thisPtr + 0x2e0 + streamSetIndex * 0x3c) != 0)   // +0x2e0
        debugLog();
    {
        int* field = *(int**)(thisPtr + 0x2ec + streamSetIndex * 0x3c); // +0x2ec
        if (field)
            setResourceData(*(int*)(thisPtr + 0x14), field, thisPtr + 0x1a0); // +0x1a0
    }
    {
        int* field = *(int**)(thisPtr + 0x2f0 + streamSetIndex * 0x3c); // +0x2f0
        if (field)
            setResourceData(*(int*)(thisPtr + 0x14), field, (void*)0x011f6680); // global data
    }
    if (*(int*)(thisPtr + 0x2f4 + streamSetIndex * 0x3c) != 0)   // +0x2f4
        debugLog();
    {
        int* field = *(int**)(thisPtr + 0x2f8 + streamSetIndex * 0x3c); // +0x2f8
        if (field)
            setResourceData(*(int*)(thisPtr + 0x14), field, thisPtr + 0x1c0); // +0x1c0
    }
    {
        int* field = *(int**)(thisPtr + 0x2fc + streamSetIndex * 0x3c); // +0x2fc
        if (field)
            setResourceData(*(int*)(thisPtr + 0x14), field, thisPtr + 0x1d0); // +0x1d0
    }
}