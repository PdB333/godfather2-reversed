// FUNC_NAME: SomeClass::setTransformMatrix
void __thiscall SomeClass::setTransformMatrix(int thisPtr, int source)
{
    // Temporary storage for a 4x3 matrix (12 floats) in the layout used by the engine.
    // The matrix is stored as 4 rows, each row split into a 2-float part (8 bytes) and a 1-float part (4 bytes).
    struct Matrix4x3Layout {
        float row0_part0[2]; // +0x00: first two floats of row0
        float row0_part1;    // +0x08: third float of row0
        float row1_part0[2]; // +0x0C: first two floats of row1
        float row1_part1;    // +0x14: third float of row1
        float row2_part0[2]; // +0x18: first two floats of row2
        float row2_part1;    // +0x20: third float of row2
        float row3_part0[2]; // +0x24: first two floats of row3
        float row3_part1;    // +0x2C: third float of row3
    } tempMatrix; // total 48 bytes (0x30)

    // Convert source data into the temporary matrix (likely a quaternion, euler angles, or another matrix)
    FUN_0043a2a0(&tempMatrix, source);

    // Copy the matrix into the object at offset 0x20
    // Offsets: 0x20, 0x28, 0x2C, 0x34, 0x38, 0x40, 0x44, 0x4C
    *(float (*)[2])(thisPtr + 0x20) = tempMatrix.row0_part0; // 8 bytes
    *(float *)(thisPtr + 0x28) = tempMatrix.row0_part1;      // 4 bytes
    *(float (*)[2])(thisPtr + 0x2C) = tempMatrix.row1_part0; // 8 bytes
    *(float *)(thisPtr + 0x34) = tempMatrix.row1_part1;      // 4 bytes
    *(float (*)[2])(thisPtr + 0x38) = tempMatrix.row2_part0; // 8 bytes
    *(float *)(thisPtr + 0x40) = tempMatrix.row2_part1;      // 4 bytes
    *(float (*)[2])(thisPtr + 0x44) = tempMatrix.row3_part0; // 8 bytes
    *(float *)(thisPtr + 0x4C) = tempMatrix.row3_part1;      // 4 bytes
}