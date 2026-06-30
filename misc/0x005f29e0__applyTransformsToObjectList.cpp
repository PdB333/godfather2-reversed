// FUNC_NAME: applyTransformsToObjectList
uint __cdecl applyTransformsToObjectList(uint source, uint listContainer)
{
    // listContainer+0x6f: number of objects (byte)
    // listContainer+0xc: array of 4-byte pointers to objects
    // Each object: +0x1c: type byte, +0xc: set to source+4 (some handle)
    // source: +0x3c float, +0x4c float (position/rotation)
    // listContainer+0x50: float (parameter)
    // listContainer+0x5c: int (some ID)

    byte count = *(byte *)(listContainer + 0x6f);
    uint result = 0; // placeholder for in_EAX initial mask

    if (listContainer != 0 && source != 0) {
        int **ptrArray = (int **)(listContainer + 0xc);
        for (int i = 0; i < (int)count; i++) {
            int *obj = ptrArray[i];
            if (obj != 0) {
                byte typeByte = *(byte *)(obj + 0x1c); // +0x1c: behavior/type
                FUN_005f2680(); // unknown setup
                FUN_005dbc10(
                    *(int *)(listContainer + 0x5c), // +0x5c: some ID
                    (double)*(float *)(source + 0x3c), // +0x3c: parent X or Y
                    (double)*(float *)(listContainer + 0x50), // +0x50: list param
                    (double)*(float *)(source + 0x4c), // +0x4c: parent Z or W
                    typeByte
                );
                *(int *)(obj + 0xc) = *(int *)(source + 4); // +0xc: set object's reference
                uint uVar5 = FUN_005f37b0(); // returns an object
                FUN_005f1400(uVar5); // do something with that object
            }
        }
        // Construct return value from loop counter offset (debug/status)
        result = ((uint)ptrArray >> 8) & 0xFFFFFF00 | 1;
    } else {
        result = 0; // default zero from low byte of in_EAX
    }
    return result;
}