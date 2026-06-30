// FUNC_NAME: TransformNode::applyScaleToMatrix
void __fastcall TransformNode::applyScaleToMatrix(int *thisPtr)
{
    float scaleX;
    float scaleY;
    float scaleZ;
    float localMatrix[4][4];
    // +0x24 (byte offset 0x90) – source matrix (may be parent’s transform or identity)
    // +0x34 (byte offset 0xD0) – destination matrix (local transform)
    // +0x4D (byte offset 0x134) – X scale factor (stored as float/int pun)
    // +0x4E (byte offset 0x138) – Y scale factor
    // +0x4F (byte offset 0x13C) – Z scale factor
    // +0x40 (byte offset 0x100) – fourth row (translation) stored here by the function
    // +0x43 (byte offset 0x10C) – bottom‑right element, set to global identity constant

    // Copy source matrix (homogeneous 4x4) into local buffer
    FUN_0043a2a0(&localMatrix, thisPtr + 0x24); // matrix copy/multiply helper

    scaleX = *(float *)(thisPtr + 0x4D);
    scaleY = *(float *)(thisPtr + 0x4E);
    scaleZ = *(float *)(thisPtr + 0x4F);

    // Scale the first three rows (rotation/scale part), keep translation row intact
    for (int row = 0; row < 3; row++) {
        localMatrix[row][0] *= scaleX;
        localMatrix[row][1] *= scaleY;
        localMatrix[row][2] *= scaleZ;
    }

    // Write result to thisPtr + 0x34 (destination matrix)
    float *dest = (float *)(thisPtr + 0x34);
    for (int row = 0; row < 3; row++) {
        dest[row * 4 + 0] = localMatrix[row][0];
        dest[row * 4 + 1] = localMatrix[row][1];
        dest[row * 4 + 2] = localMatrix[row][2];
        dest[row * 4 + 3] = 0.0f;           // set w component to 0
    }
    // Copy fourth row (translation) from source
    dest[12] = localMatrix[3][0];
    dest[13] = localMatrix[3][1];
    dest[14] = localMatrix[3][2];
    dest[15] = *(float *)&DAT_00e2b1a4;    // global identity w (1.0f)

    // Additional update call (likely marks matrix dirty)
    FUN_006101b0();

    // Virtual method at vtable offset 0x68 (e.g., onTransformChanged)
    (**(void (__thiscall **)(int *))(*(int *)thisPtr + 0x68))(thisPtr);
}