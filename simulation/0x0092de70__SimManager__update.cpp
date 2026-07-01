// FUNC_NAME: SimManager::update
void __fastcall SimManager::update(int this) {
    uint *flagsPtr;
    int *objectPtr;
    uint index;
    code *funcPtr;
    float deltaMove;

    // Possibly set some timer or frame rate (10 = priority?)
    setSomePriority(10);

    // Call virtual function at vtable+0x2c on global manager
    (**(code **)(*g_pGlobalManager + 0x2c))();

    // Reset some object fields
    *(int *)(this + 0xec) = 0;          // +0xec: some timer/flag
    *(int *)(this + 0x118) = -1;        // +0x118: some handle/index

    // Clear global flag
    g_someGlobalFlag = 0;

    // Clear 12 entries (each 0x18 bytes) of an array
    index = 0;
    do {
        (&g_someArray)[index] = 0;      // clears 0x18 bytes per step
        objectPtr = g_pSomeObject;      // reload global pointer
        index += 24;                    // 0x18 byte stride
    } while (index < 288);              // 0x120 bytes total (12 entries)

    if (g_pSomeObject != 0) {
        deltaMove = 0.0f;
        // Clamp difference between this->field_0x168 and a global threshold
        if ((0.0f < *(float *)(this + 0x168)) &&
            (deltaMove = *(float *)(this + 0x168) - g_someThreshold, deltaMove < 0.0f)) {
            deltaMove = 0.0f;
        }
        flagsPtr = (uint *)(g_pSomeObject + 0xdf); // +0xdf: flags byte?
        g_pSomeObject[0xf5] = (int)deltaMove;      // +0x3d4: store as int

        // Check condition: bit 4 of flags, object[3] != 0, and object[0xed] != -1
        if ((((*flagsPtr >> 4) & 1) != 0) &&
            (objectPtr[3] != 0) &&
            (objectPtr[0xed] != -1)) {
            // Select virtual function based on object[2] (offset 8)
            if (objectPtr[2] == 0) {
                funcPtr = *(code **)(*objectPtr + 0x98); // vtable+0x98
            } else {
                funcPtr = *(code **)(*objectPtr + 0x80); // vtable+0x80
            }
            (*funcPtr)();
        }
        updateSubsystem(0); // FUN_008a4ae0(0) - unknown
    }
    releaseGlobalResource(&g_someGlobal); // FUN_004086d0
}