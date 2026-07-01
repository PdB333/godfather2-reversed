// FUNC_NAME: SomeClass::extractAnimationIds
void __thiscall extractAnimationIds(int this, undefined4 param_2, uint *outputBuffer, uint maxCount)
{
    uint id;
    uint index;
    uint count;
    
    count = 0;
    index = 0;
    while( true ) {
        id = *(uint *)(index + *(int *)(this + 0x14)); // +0x14: pointer to animation ID array (each entry 0xC bytes)
        if (3 < id) { // Animation IDs > 3 are invalid/terminator
            return;
        }
        *outputBuffer = id;
        count = count + 4;
        outputBuffer = outputBuffer + 1;
        if (maxCount < count) break;
        index = index + 0xc; // Each animation entry is 12 bytes (0xC)
        if (299 < index) { // Max 25 entries (300/12 = 25)
            *outputBuffer = 0xabba; // Sentinel value indicating end of valid data
            return;
        }
    }
    return;
}