// FUNC_NAME: Matrix4x4::getTranslationAndRotation
void __thiscall Matrix4x4::getTranslationAndRotation(Vector3 *outTranslation, Vector3 *outRotation)
{
    // Copy translation from matrix columns (columns 0-3, rows 0-3)
    // Matrix is stored column-major: +0x10 = column 0, +0x14 = column 1, +0x18 = column 2, +0x1c = column 3
    // Translation is in column 3 (columns 0-2 are rotation/scale)
    outTranslation->x = *(float *)(this + 0x10);  // +0x10: matrix[0][0] (column 0, row 0)
    outTranslation->y = *(float *)(this + 0x14);  // +0x14: matrix[1][0] (column 0, row 1)
    outTranslation->z = *(float *)(this + 0x18);  // +0x18: matrix[2][0] (column 0, row 2)
    outTranslation->w = *(float *)(this + 0x1c);  // +0x1c: matrix[3][0] (column 0, row 3)

    // Copy rotation (Euler angles) from matrix columns 1-3
    // Rotation is stored in columns 1-3 (columns 1,2,3 = rotation axes)
    outRotation->x = *(float *)(this + 0x20);  // +0x20: matrix[0][1] (column 1, row 0)
    outRotation->y = *(float *)(this + 0x24);  // +0x24: matrix[1][1] (column 1, row 1)
    outRotation->z = *(float *)(this + 0x28);  // +0x28: matrix[2][1] (column 1, row 2)
    outRotation->w = *(float *)(this + 0x2c);  // +0x2c: matrix[3][1] (column 1, row 3)
}