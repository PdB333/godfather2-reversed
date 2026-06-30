// FUNC_NAME: createNetObject
uint* createNetObject(void)
{
    char isClient;
    uint* newObj;
    int clientSize;
    int stackVar1;
    undefined8* stackPtr;
    int stackVar2;
    int stackBuffer[2];
    undefined8* tempPtr;
    undefined8 stackBuf1;
    undefined8 stackBuf2;
    undefined4 local_24;
    undefined4 local_20;
    undefined8* local_1c;
    undefined8 local_18;
    undefined8 local_10;

    local_1c = &local_18;
    local_24 = 0;
    local_20 = 0;
    local_18 = 0;
    local_10 = 0;

    isClient = FUN_005a3c40(); // Check if running on client
    if (isClient == '\0') {
        // Server path: allocate object of fixed size 0x24
        newObj = (uint*)(*DAT_0119caf0)(0x24, 0); // globalAlloc
        if (newObj == (uint*)0x0) {
            newObj = (uint*)0x0;
        } else {
            *newObj = *newObj & 0xffff8001 | 1; // Set flags: bit0=1, clear bits 15-31
            *(undefined2 *)((int)newObj + 2) = 0; // Clear short at +2
            *newObj = *newObj | 0x8000; // Set bit15
            FUN_005a0a80(); // initObject (no extra size)
            newObj[8] = 0xbeefceec; // Magic signature at +0x20
        }
        FUN_005abf00(newObj); // registerObject (server)
    } else {
        // Client path: allocate with size from getClientObjectSize()
        newObj = (uint*)(*DAT_0119caf0)(); // globalAlloc with no explicit size? Actually call with no args
        if (newObj == (uint*)0x0) {
            newObj = (uint*)0x0;
        } else {
            clientSize = FUN_005a3a40(); // getClientObjectSize
            *newObj = *newObj & 0xffff8001 | 1;
            *(undefined2 *)((int)newObj + 2) = 0;
            *newObj = *newObj | 0x8000;
            FUN_005a0a00(clientSize + 4); // initObjectWithSize (extra 4 bytes)
            newObj[8] = 0xbeefceec;
        }
    }

    isClient = FUN_005a3c40(); // Check again
    if (isClient == '\0') {
        // Server path: build a name/string using stack buffer
        tempPtr = &stackBuf1;
        stackBuffer[0] = 0;
        stackBuffer[1] = 0;
        stackBuf1 = 0;
        stackBuf2 = 0;
        FUN_005a92b0(stackBuffer); // initStackBuffer
        stackVar2 = newObj[3] + newObj[1]; // Calculate some offset
        stackVar1 = stackBuffer[0] + (int)tempPtr; // Pointer arithmetic
        stackPtr = tempPtr;
        FUN_005aba20(&stackPtr, &stackVar1); // concatStrings
        newObj[8] = 0xbeefceec; // Re-set magic? (redundant)
        if ((tempPtr != &stackBuf1) && (tempPtr != (undefined8*)0x0)) {
            (*DAT_0119caf4)(tempPtr); // globalFree
        }
    } else {
        // Client path: just register
        FUN_005a3a40(); // getClientObjectSize (ignored)
        FUN_005abeb0(); // registerClientObject
    }

    if ((local_1c != &local_18) && (local_1c != (undefined8*)0x0)) {
        (*DAT_0119caf4)(local_1c); // Free local buffer if allocated
    }
    return newObj;
}