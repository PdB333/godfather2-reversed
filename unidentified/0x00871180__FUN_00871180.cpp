// FUNC_NAME: SomeClass::handleMessage
// Reconstructed from 0x00871180 - Message handler for game object state/events

int __thiscall SomeClass::handleMessage(void *thisPtr, int arg2, int arg3, int arg4, int messageId, int arg6)
{
    int *vtablePtr;    // pointer to vtable stored at this+0x5c
    char someFlag;     // boolean from FUN_00875840
    int retVal;        // return value
    int contextPtr;    // from FUN_00471610
    // local struct used for virtual call (8 bytes)
    struct {
        uint32_t high;  // from this+0x64
        uint32_t low;   // from context+0x30 (low 32 bits of 64-bit value)
    } localStruct;
    uint32_t someData; // from context+0x38 (4 bytes)
    uint32_t zeroVec[3]; // 12-byte struct for FUN_005466c0

    if (messageId == 10) {
        // Set bit 2 at offset 0x6c (probably enable flag)
        *(uint32_t *)((char *)thisPtr + 0x6c) |= 4;
        return 1;
    }

    if (messageId != 11) {
        if (messageId != 12) {
            // Default: delegate to base class handler
            retVal = FUN_004ac700(arg2, arg3, arg4, messageId, arg6);
            return retVal;
        }

        // Message 12: Prepare a structure and call virtual function at vtable+0x1c
        vtablePtr = *(int **)((char *)thisPtr + 0x5c);
        someFlag = FUN_00875840();

        if (someFlag == 0) {
            contextPtr = FUN_00471610();
            someData = *(uint32_t *)(contextPtr + 0x38);
            // Build 8-byte struct: high from this+0x64, low from context+0x30 (cast to int)
            localStruct.high = *(uint32_t *)((char *)thisPtr + 0x64);
            localStruct.low = (int)*(uint64_t *)(contextPtr + 0x30);
            // Call virtual function at offset 0x1c (e.g., SomeClass::someVirtualMethod)
            (*(void (__thiscall **)(void *))(*vtablePtr + 0x1c))(&localStruct);

            // Additional check: if FUN_00544b70 returns 0, zero out a 12-byte struct and call FUN_005466c0
            if (FUN_00544b70() == 0) {
                zeroVec[0] = 0;
                zeroVec[1] = 0;
                zeroVec[2] = 0;
                FUN_005466c0(zeroVec);
            }
        }

        // Common cleanup for message 12
        FUN_0086b830(0);
        FUN_0086b7b0(0);
        if ((*(uint8_t *)((char *)thisPtr + 0x6c) & 0x10) != 0) {
            // If bit 4 is set, call with float 1.0f (0x3f800000)
            FUN_0086b7d0(1.0f);
        }
        return 1;
    }

    // Message 11: simple call with arg3
    FUN_00870fc0(arg3);
    return 1;
}