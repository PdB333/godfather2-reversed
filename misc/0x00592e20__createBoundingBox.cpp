// FUNC_NAME: createBoundingBox
int createBoundingBox(uint param1, uint param2, uint param3, uint in_EAX) {
    // Local 8-float structure, likely representing an axis-aligned bounding box (AABB) or similar.
    // Initially zero, except for two sentinel values (DAT_00e2b1a4 - likely infinite/FLT_MAX constant)
    float localBox[8];
    localBox[0] = 0.0f;
    localBox[1] = 0.0f;
    localBox[2] = 0.0f;
    localBox[3] = DAT_00e2b1a4;  // +0x0c: sentinel/infinity
    localBox[4] = 0.0f;
    localBox[5] = 0.0f;
    localBox[6] = 0.0f;
    localBox[7] = DAT_00e2b1a4;  // +0x1c: sentinel/infinity

    // Compute bounding data from inputs (presumably points or other geometry)
    int result = FUN_00592ec0(localBox, param1, in_EAX, param2, param3);
    if (result == 0) {
        return 0;
    }

    // Allocate a new object (likely a wrapper for the bounding box)
    int obj = FUN_005931a0();  // Allocation (size unknown, but at least 0x30 bytes)
    if (obj == 0) {
        return 0;
    }

    // Copy computed bounding data into the object at offset +0x10
    // The object likely has a header (vtable, count, etc.) before the bounding data
    *(float*)(obj + 0x10) = localBox[0];
    *(float*)(obj + 0x14) = localBox[1];
    *(float*)(obj + 0x18) = localBox[2];
    *(float*)(obj + 0x1c) = localBox[3];
    *(float*)(obj + 0x20) = localBox[4];
    *(float*)(obj + 0x24) = localBox[5];
    *(float*)(obj + 0x28) = localBox[6];
    *(float*)(obj + 0x2c) = localBox[7];
    return obj;
}