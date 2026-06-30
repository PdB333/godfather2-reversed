// FUNC_NAME: EARSCommandManager::initializeInstance

void __fastcall EARSCommandManager::initializeInstance(EARSCommandManager* thisPtr) {
    int bufferSize;
    byte* tableEntry;
    byte* arrayPtr;
    uint32_t flags;
    bool isFirstInstance;
    uint32_t currentCount;
    uint32_t local8;

    // Initialize global singleton handles if needed
    if (gSystemHandle1 == 0) {
        gSystemHandle1 = getSystemHandle();
    }
    if (gSystemHandle2 == 0) {
        gSystemHandle2 = getSystemHandle();
    }

    // Store first handle in instance at +0x10
    *(int*)(thisPtr + 0x10) = gSystemHandle1;

    // Allocate main buffer if not already done
    if (gMainBuffer == 0) {
        flags = 0x14;
        if (gSomeFlag == 0) {
            flags = 3;
        }
        gMainBuffer = allocateBufferWithFlags(flags, 0x210098, gWidth, gHeight, 1, 0xffffffff);
        gBackupBuffer = gMainBuffer;
        if ((gExistingPointer != 0) && (*(int*)(gExistingPointer + 0xa0) != 0)) {
            flushCache();
        }
    }

    // Use a global size value and access a table entry
    bufferSize = gSomeSize;
    if (gMainBuffer < 0x1000) {
        tableEntry = (byte*)(&gResourceTable + gMainBuffer * 0x38);
    } else {
        tableEntry = nullptr;
    }
    if ((int)((uint16_t)(tableEntry[4]) * (uint16_t)(tableEntry[2])) < gSomeSize * gSomeSize) {
        currentCount = 0xffffffff;
    } else {
        if ((0xfff < gMainBuffer) || (gMainBuffer * 0x38 == -0x11a0f28)) {
            gSomeHandle = 0xffffffff;
            goto LAB_0049090f;
        }
        currentCount = allocateResource();
        if ((0xfff < currentCount) || (&gResourceTable + currentCount * 0x38 == nullptr)) {
            gSomeHandle = 0xffffffff;
            goto LAB_0049090f;
        }
        if (1 < (byte)(&gResourceTable)[currentCount * 0x38]) {
            gSomeHandle = 0xffffffff;
            goto LAB_0049090f;
        }
    }
    gSomeHandle = allocateBufferWithFlags(flags, 0x210098, bufferSize, bufferSize, 1, currentCount);

LAB_0049090f:
    // Call another initialization function
    initializePointers();

    // Copy data from +0x50 to +0x1bc
    *(uint32_t*)(thisPtr + 0x1bc) = *(uint32_t*)(thisPtr + 0x50);

    // Increment global instance counter, check if first instance
    int temp = gInstanceCounter + 1;
    isFirstInstance = (gInstanceCounter == 0);
    gInstanceCounter = temp;
    if (isFirstInstance) {
        // Register command handlers on first instance
        currentCount = 0;
        local8 = (local8 & 0xFFFFFF00) | 0x80; // Set low byte to 0x80
        if (gCommandCount != 0) {
            arrayPtr = &gCommandArray;
            do {
                if (0x80 < *arrayPtr) {
                    handleError();
                    return;
                }
                currentCount = currentCount + 1;
                arrayPtr = arrayPtr + 0xc;
            } while (currentCount < gCommandCount);
        }
        if (gCommandCount < 0x20) {
            int offset = gCommandCount * 0xc;
            *(uint64_t*)(&gCommandArrayData + gCommandCount * 3) = 0x4906e000490670; // two function pointers
            *(uint32_t*)(&gCommandArray + offset) = local8; // parameter byte
            gCommandCount = gCommandCount + 1;
        }
    }
    return;
}