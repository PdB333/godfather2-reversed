// FUNC_NAME: SomeClass::getScaledOffsetPosition
// Address: 0x00774730
// This function computes a world-space position from a rotation+translation offset, 
// scaled by a global scale factor (DAT_00e51cb0). 
// The object has a pointer at +0x7c to a bone/transform data structure, 
// a mode flag at +0x88, and the transform data is read from offsets relative to that pointer.

void __thiscall SomeClass::getScaledOffsetPosition(SomeClass* thisPtr, float* outPos)
{
    // Constants (likely game globals)
    const float worldScale = DAT_00e51cb0;  // global scale factor
    const float constant360 = DAT_00e44564; // likely 360.0f (degrees)

    // Get pointer to bone/transform data (offset +0x7c)
    // If null, set boneDataPtr to 0 (will cause access at offset 0?)
    int* boneDataPtr = *(int**)((unsigned char*)thisPtr + 0x7c); // +0x7c
    int boneBase;
    if (boneDataPtr == 0) {
        boneBase = 0;
    } else {
        boneBase = (int)((unsigned char*)boneDataPtr - 0x48); // subtract header size? +0x48
    }

    // Euler rotation components (3 floats)
    float rx, ry, rz;
    if (*(int*)((unsigned char*)thisPtr + 0x88) == 0) {
        // Mode 0: use rotation at offsets +0x90, +0x94, +0x98
        // Note: the decompiler reads 8 bytes as a double, but it's actually two floats.
        float* rotPtr = (float*)(boneBase + 0x90);
        rx = rotPtr[0];
        ry = rotPtr[1];
        rz = *(float*)(boneBase + 0x98);
    } else if (*(int*)((unsigned char*)thisPtr + 0x88) == 1) {
        // Mode 1: use rotation at offsets +0x70, +0x74, +0x78
        float* rotPtr = (float*)(boneBase + 0x70);
        rx = rotPtr[0];
        ry = rotPtr[1];
        rz = *(float*)(boneBase + 0x78);
    } else {
        // Default: negated version of mode 1 (subtract from constant360)
        float* rotPtr = (float*)(boneBase + 0x70);
        rx = constant360 - rotPtr[0];
        ry = constant360 - rotPtr[1];
        rz = constant360 - *(float*)(boneBase + 0x78);
    }

    // Recalculate boneBase (same logic as before) – done for clarity
    if (boneDataPtr == 0) {
        boneBase = 0;
    } else {
        boneBase = (int)((unsigned char*)boneDataPtr - 0x48);
    }

    // Read translation vector at offsets +0xb0, +0xb4, +0xb8
    float* transPtr = (float*)(boneBase + 0xb0);
    float transX = transPtr[0];
    float transY = transPtr[1];
    float transZ = transPtr[2];

    // Apply scale and add translation to get world position
    outPos[0] = worldScale * rx + transX;
    outPos[1] = worldScale * ry + transY;
    outPos[2] = worldScale * rz + transZ;
}