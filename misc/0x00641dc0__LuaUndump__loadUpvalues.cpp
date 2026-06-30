// FUNC_NAME: LuaUndump::loadUpvalues
void __thiscall LuaUndump::loadUpvalues(uint nupvalues, int* readerState) {
    bool nupIsZero = (nupvalues == 0);

    // Validate nupvalues is non-negative
    if ((int)nupvalues < 0) {
        error(readerState[0], "bad integer in %s", (const char*)readerState[4]);
    }

    // Read the expected nupvalues count from the bytecode stream into this+0x44
    readByte();

    // Validate consistency: if nupvalues > 0, it must match the expected count
    if (!nupIsZero && (nupvalues != *(unsigned char*)(this + 0x44))) {
        error(readerState[0], "bad nupvalues in %s: read %d; expected %d",
              (const char*)readerState[4], nupvalues, *(unsigned char*)(this + 0x44));
    }

    int allocatorState = readerState[0];
    uint allocSize = nupvalues * 4;

    int* upvalueArray;
    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) {
            error(allocatorState, "memory allocation error: block too big");
        }

        // Allocate memory for upvalue pointer array (each entry 4 bytes)
        upvalueArray = (int*)allocateMemory(0, allocSize); // DAT_012059dc
        if (upvalueArray != 0) {
            if (allocatorState != 0) {
                // Track allocated memory (offset +0x24 from allocator state)
                int* allocCounter = (int*)(*(int*)(allocatorState + 0x10) + 0x24);
                *allocCounter += allocSize;
            }
        }
        else {
            if (allocatorState != 0) {
                handleAllocError(); // FUN_00635a80
                return;
            }
        }
    }
    else {
        upvalueArray = 0;
    }

    // Store array pointer and count in the proto structure
    *(int**)(this + 0x1c) = upvalueArray;   // +0x1c: upvalue pointer array
    *(uint*)(this + 0x24) = nupvalues;      // +0x24: number of upvalues

    // Read each upvalue from the bytecode stream and store in the array
    for (int i = 0; i < (int)nupvalues; ++i) {
        int value = readTValue(readerState); // FUN_00641a50
        upvalueArray[i] = value;
    }
}