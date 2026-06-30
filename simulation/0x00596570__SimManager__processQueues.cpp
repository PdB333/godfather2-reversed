// FUNC_NAME: SimManager::processQueues
void __fastcall SimManager::processQueues(int thisPtr)
{
    int i;
    int j;
    int count1;
    int count2;
    int count3;
    int* indexArray1;
    int* indexArray2;
    int* indexArray3;
    void** objArray1;
    void** objArray2;
    void** objArray3;

    // Check active flag at +0x04
    if (*(char*)(thisPtr + 4) != '\0') {
        // First queue (high priority?, uses vtable offset 0x58)
        i = 0;
        *(int*)(thisPtr + 0x1c) = 0;           // reset index counter1
        count1 = *(int*)(thisPtr + 8);
        objArray1 = *(void***)(thisPtr + 0x14);
        indexArray1 = *(int**)(thisPtr + 0x18);
        if (0 < count1) {
            do {
                // Call virtual function at vtable+0x58 (likely 'tick' or 'update')
                (*(void(__thiscall**)(void*))(
                    *(int*)(*(int*)objArray1[i] + 0x58)  // i is iVar2
                ))();
                i++;
                indexArray1[j] = i;             // store current index (iVar1)
                j = i;
            } while (i < count1);
        }
        indexArray1[i - 1] = -1;                // terminator

        // Second queue (uses vtable offset 8)
        i = 0;
        *(int*)(thisPtr + 0x28) = 0;           // reset index counter2
        count2 = *(int*)(thisPtr + 0xc);
        objArray2 = *(void***)(thisPtr + 0x20);
        indexArray2 = *(int**)(thisPtr + 0x24);
        if (0 < count2) {
            do {
                // Call virtual function at vtable+0x08 (typically 'update' or 'simulate')
                (*(void(__thiscall**)(void*))(
                    *(int*)(*(int*)objArray2[i] + 8)
                ))();
                i++;
                indexArray2[j] = i;
                j = i;
            } while (i < count2);
        }
        indexArray2[i - 1] = -1;

        // Third queue (same vtable offset 8)
        i = 0;
        *(int*)(thisPtr + 0x34) = 0;           // reset index counter3
        count3 = *(int*)(thisPtr + 0x10);
        objArray3 = *(void***)(thisPtr + 0x2c);
        indexArray3 = *(int**)(thisPtr + 0x30);
        if (0 < count3) {
            do {
                (*(void(__thiscall**)(void*))(
                    *(int*)(*(int*)objArray3[i] + 8)
                ))();
                i++;
                indexArray3[j] = i;
                j = i;
            } while (i < count3);
        }
        indexArray3[i - 1] = -1;
        return;
    }
    // If not active, fallback to some unknown indirect call (likely assertion or error)
    (*(void(__thiscall**)(void*))(*(int*)0x01205590 + 4))();
}