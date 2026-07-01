// FUNC_NAME: MessageHandler::processMessage
void __thiscall MessageHandler::processMessage(int thisPtr, int *msgData)
{
    int msgId = *msgData;
    
    // Handle message based on ID comparisons with stored IDs and constants
    if (msgId == DAT_0112fddc) { // likely "connect" or "establish"
        // Clear some state
        *(int *)(thisPtr + 0x90) = 0;
        *(int *)(thisPtr + 0x8c) = 0;
        *(int *)(thisPtr + 0x88) = 0;
        *(int *)(thisPtr + 0x84) = 0;
        *(int *)(thisPtr + 0x54) = *(int *)(thisPtr + 0x54) - 1;
        
        int extra = msgData[1]; // secondary data
        // Check flag at offset 0x6c bit 3
        if ((*(uint *)(thisPtr + 0x6c) & 8) == 0) {
            uint counter = *(uint *)(thisPtr + 0x5c);
            int *vtablePtr = (int *)(thisPtr - 0x3c); // object with vtable
            uint limit = getTimeOrCounter(); // FUN_0083c160
            if (limit <= counter) {
                goto clearAndFreeMem; // jump to common cleanup
            }
            // Local variables for vector/data
            float localData[3]; // local_14, local_10, local_18 (actually local_18, local_14, local_10)
            float *localPtr = localData;
            localData[0] = 0;
            localData[1] = 0;
            localData[2] = 0;
            void *vecA = nullptr;
            void *vecB = nullptr;
            
            // Decide based on another flag at 0x70 bit 3
            if ((*(uint *)(thisPtr + 0x70) & 8) == 0) {
                // Call virtual function at vtable+0x2c to get some data
                char result = (**(code **)(*vtablePtr + 0x2c))(&localVec, &vecB, &vecA, &localPtr);
                if (result == '\0') goto clearAndFreeMem;
            } else {
                // Alternative: use stored data at offsets 0xf0,0xf4,0xf8 and allocate
                localVec = *(undefined4 *)(thisPtr + 0xf0);
                localVec2 = *(undefined4 *)(thisPtr + 0xf4);
                localVec3 = *(undefined4 *)(thisPtr + 0xf8);
                vecA = nullptr;
                localPtr = nullptr;
                callAllocateVectors(&vecA, &localPtr); // FUN_005f5cb0
                vecB = vecA;
                vecA = localPtr;
                localPtr = *(void **)(thisPtr + 0x108);
            }
            // Call pre-processing with extra
            preProcess(extra); // FUN_0083eae0
            
            // Iterate over some array at thisPtr+0xc4, count at thisPtr+0xec
            int *arrayBase = (int *)(thisPtr + 0xc4);
            int count = *(int *)(thisPtr + 0xec);
            int *current = arrayBase;
            int *end = arrayBase + count * 2; // each element 8 bytes (2 ints)
            while (current < end) {
                // each element is a structure with virtual function at +0 (vtable) and data at +4
                int *element = current;
                // Call virtual function at offset 4 (index 1) with extra, thisPtr+0xbc, and vtablePtr
                (**(code **)(*element + 4))(extra, *(int *)(thisPtr + 0xbc), vtablePtr);
                current += 2;
            }
            
            // Depending on vecA and vecB being set, call another virtual
            if (vecA == nullptr || vecB == nullptr) {
                (**(code **)(*vtablePtr + 0x3c))(extra, &localVec, localPtr, 0, 0);
            } else {
                callCopyComponents(vecA, vecB); // FUN_005f5c20
                (**(code **)(*vtablePtr + 0x3c))(extra, &localVec, localPtr, 0, localResult);
                if (localResult[0] != 0) {
                    callFreeResult(localResult); // FUN_004daf90
                }
            }
            // If flag bit 0 at 0x6c is clear, get current time and store
            if ((*(byte *)(thisPtr + 0x6c) & 1) == 0) {
                float currentTime = (float)getFrameTime(); // FUN_0083b4f0
                *(float *)(thisPtr + 0x64) = currentTime;
            }
        } else {
clearAndFreeMem:
            callFreeMemory(extra + 0x3c); // FUN_004088c0
        }
        
        // Recalculate limit condition
        int counter2 = *(int *)(thisPtr + 0x5c);
        uint limit2 = getTimeOrCounter();
        bool condition = (uint)(*(int *)(thisPtr + 0x54) + counter2) < limit2;
        goto finalCheck;

    } else if (msgId == DAT_0112fde8) { // disconnect or stop
        // Clear data
        *(int *)(thisPtr + 0x90) = 0;
        *(int *)(thisPtr + 0x8c) = 0;
        *(int *)(thisPtr + 0x88) = 0;
        *(int *)(thisPtr + 0x84) = 0;
        *(int *)(thisPtr + 0x54) = *(int *)(thisPtr + 0x54) - 1;
        
        int counter = *(int *)(thisPtr + 0x5c);
        uint limit = getTimeOrCounter();
        bool condition = (uint)(*(int *)(thisPtr + 0x54) + counter) < limit;
        goto finalCheck;

    } else if (msgId == *(int *)(thisPtr + 0xa0)) { // some ID stored at +0xa0
        *(uint *)(thisPtr + 0x6c) |= 8;
        return;

    } else if (msgId == *(int *)(thisPtr + 0xa8)) {
        *(uint *)(thisPtr + 0x6c) &= 0xfffffff7;
        if ((*(uint *)(thisPtr + 0x6c) >> 0xb & 1) == 0) {
            return;
        }
        int status = getTimeOrCounter();
        if (status != 1 && status - 1 >= 0) {
            setSomeFlag(1); // FUN_0083e1b0
        }
        *(int *)(thisPtr + 0x64) = 0;
        return;

    } else if (msgId == *(int *)(thisPtr + 0xb0)) {
        handleSimpleEvent(0, 1); // FUN_0083e4b0
        return;

    } else if (msgId == DAT_0112dc4c) {
        *(uint *)(thisPtr + 0x70) |= 2;
        return;

    } else if (msgId == DAT_0112dc44) {
        *(uint *)(thisPtr + 0x70) &= 0xfffffffd;
        return;

    } else if (msgId == DAT_0112dc60) {
        handleSimpleEvent(0, 1); // FUN_0083e4b0
        return;

    } else if (msgId == DAT_012069f4) {
        callCleanupRoutine(); // FUN_0083ebb0
        callUnregisterObject(&DAT_012069f4); // FUN_004086d0
        return;

    } else if (msgId == DAT_0112fdf8) {
        int extra = msgData[1];
        // Iterate over array at +0xc4, calling virtual at offset 8
        int *arrayBase = (int *)(thisPtr + 0xc4);
        int count = *(int *)(thisPtr + 0xec);
        int *current = arrayBase;
        int *end = arrayBase + count * 2;
        while (current < end) {
            int *element = current;
            (**(code **)(*element + 8))(extra, *(int *)(thisPtr + 0xbc), thisPtr - 0x3c);
            current += 2;
        }
        // Prepare memory for call
        int memSize = (extra == 0) ? 0 : extra + 0x3c;
        callMemoryOperation(&DAT_0112dc68, memSize, 0); // FUN_00408b80
        return;

    } else {
        return;
    }

finalCheck:
    if (condition) {
        return;
    }
    float fVal = *(float *)(thisPtr + 0x34);
    // Check flags at 0x6c bits 0x18000 (0x11 and 0x10) and another condition
    if (((*(uint *)(thisPtr + 0x6c) & 0x18000) != 0) &&
        (fVal < *(float *)(thisPtr + 0x38)) &&
        ((*(uint *)(thisPtr + 0x6c) >> 0x10 & 1) != 0)) {
        // Adjust fVal: (value+source)-source (likely rounding)
        fVal = (*(float *)(thisPtr + 0x38) + fVal) - fVal;
    }
    *(float *)(thisPtr + 0x64) = fVal;
}