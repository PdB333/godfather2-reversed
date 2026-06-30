// FUNC_NAME: AnimationManager::processCommandList
uint AnimationManager::processCommandList(void)
{
    // +0x00: pointer to some base data (e.g., vtable or class instance)
    int* baseData = *(int**)this;
    // +0x04: pointer to an array of data (could be animation set or state)
    int* dataArray = *(int**)(this + 4); // offset 0x04

    // +0x0C: count of commands to process
    int commandCount = *(int*)(this + 12); // offset 0x0C (third field)

    // +0x08: a float parameter (time/alpha)
    float blendFactor = *(float*)(this + 8); // offset 0x08

    // Determine which action array to use based on a version/type byte
    int* actionArray;
    int stateVersion = (*((uint8*)(dataArray + 1)) & 0xFF); // +0x04 from dataArray
    if (stateVersion < 10) {
        actionArray = *(int**)(dataArray + 0x24); // offset 0x24
    } else {
        actionArray = *(int**)(dataArray + 0x2c); // offset 0x2C
    }

    // Retrieve or allocate a processing buffer
    int* procBuffer = *(int**)(baseData + 0x38); // offset 0x38
    if (procBuffer == NULL) {
        procBuffer = (int*)FUN_0056ef10(commandCount);
        *(int**)(baseData + 0x38) = procBuffer;
    }

    // Starting offset for action slots (each 0x20 bytes)
    uint currentSlotAddr = (uint)procBuffer + 0x10;

    // Pointer to command byte sequence (from baseData+0x34 then +0x14)
    char* cmdBytePtr = *(char**)(baseData + 0x34) + 0x14;

    // Branch based on whether the action array's first element is zero
    if (*actionArray == 0) {
        // If action array's first element is null
        uint returnVal = currentSlotAddr;
        // Check short at actionArray[3] (offset +0x0C)
        if (*(short*)(actionArray + 3) != 0) {
            // Process all commands with "first mode" functions
            FUN_00581080((int)blendFactor);
            for (int i = 0; i < commandCount; i++) {
                if (*cmdBytePtr == '\x02') {
                    FUN_00581220(currentSlotAddr);
                } else if (*cmdBytePtr != '\0') {
                    FUN_00581370();
                }
                currentSlotAddr += 0x20;
                cmdBytePtr++;
            }
            goto returnOne;
        }
        return returnVal & 0xFFFFFF00; // Clear low byte (mask)
    } else {
        // Action array has a non-null first element
        uint actionAddr;
        if (stateVersion < 10) {
            actionAddr = *(uint*)(dataArray + 0x24);
        } else {
            actionAddr = *(uint*)(dataArray + 0x2c);
        }
        // Check short at actionAddr+0x24
        if (*(short*)(actionAddr + 0x24) != 0) {
            FUN_0057f8a0((int)blendFactor);
            for (int i = 0; i < commandCount; i++) {
                if (*cmdBytePtr == '\x02') {
                    FUN_0057f9d0(currentSlotAddr);
                } else if (*cmdBytePtr != '\0') {
                    FUN_005800a0();
                }
                currentSlotAddr += 0x20;
                cmdBytePtr++;
            }
            return 1;
        }
    }

returnOne:
    return 1;
}