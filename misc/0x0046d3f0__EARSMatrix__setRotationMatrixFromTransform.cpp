// FUNC_NAME: EARSMatrix::setRotationMatrixFromTransform
// Address: 0x0046d3f0
// Copies the rotation/scale part of a 4x4 transform matrix, forcing translation to zero and homogeneous w to 1.
void __thiscall EARSMatrix::setRotationMatrixFromTransform(EARSMatrix* this, const float* sourceMatrix)
{
    // The matrix is stored as 16 consecutive floats starting at offset 0x40
    float* dest = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x40);

    // Copy all 16 elements from source
    for (int i = 0; i < 16; ++i)
    {
        dest[i] = sourceMatrix[i];
    }

    // Zero translation components (indices 3, 7, 11 in row-major order)
    // Offsets: 0x4c = index 3, 0x5c = index 7, 0x6c = index 11
    dest[3]  = 0.0f;   // column 3, row 0 (translation X)
    dest[7]  = 0.0f;   // column 3, row 1 (translation Y)
    dest[11] = 0.0f;   // column 3, row 2 (translation Z)

    // Set homogeneous coordinate to 1.0 (global constant)
    // Offset 0x7c = index 15, usually 1.0f for affine transforms
    dest[15] = *reinterpret_cast<const float*>(&DAT_00e2b1a4); // assumed 1.0f

    // Call engine housekeeping (likely matrix validation or hierarchy propagation)
    FUN_006101b0();
}