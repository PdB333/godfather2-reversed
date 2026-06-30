// FUNC_NAME: Matrix4x4::setFromArray
void __thiscall Matrix4x4::setFromArray(int *thisPtr, undefined4 *srcArray)
{
    int *dst = (int *)*thisPtr;  // dereference this (likely a pointer to the matrix data)
    if (dst != 0) {
        // Copy 16 floats (4x4 matrix) starting at offset 0x30 of the destination
        dst[0x30 / 4] = srcArray[0];   // +0x30: m00
        dst[0x34 / 4] = srcArray[1];   // +0x34: m01
        dst[0x38 / 4] = srcArray[2];   // +0x38: m02
        dst[0x3C / 4] = srcArray[3];   // +0x3C: m03
        dst[0x40 / 4] = srcArray[4];   // +0x40: m10
        dst[0x44 / 4] = srcArray[5];   // +0x44: m11
        dst[0x48 / 4] = srcArray[6];   // +0x48: m12
        dst[0x4C / 4] = srcArray[7];   // +0x4C: m13
        dst[0x50 / 4] = srcArray[8];   // +0x50: m20
        dst[0x54 / 4] = srcArray[9];   // +0x54: m21
        dst[0x58 / 4] = srcArray[10];  // +0x58: m22
        dst[0x5C / 4] = srcArray[11];  // +0x5C: m23
        dst[0x60 / 4] = srcArray[12];  // +0x60: m30
        dst[0x64 / 4] = srcArray[13];  // +0x64: m31
        dst[0x68 / 4] = srcArray[14];  // +0x68: m32
        dst[0x6C / 4] = srcArray[15];  // +0x6C: m33
    }
}