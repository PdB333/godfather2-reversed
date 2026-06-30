// FUNC_NAME: extractMatrixScales
void __fastcall extractMatrixScales(void *outputStruct, const float *matrix4x4)
{
    // Output struct has scale properties at known offsets
    // +0x134: scaleX (float), +0x138: scaleY (float), +0x13c: scaleZ (float)
    // Matrix is row-major 4x4 (16 floats), we read the top-left 3x3 rotation part.
    // Indices 0-2: row0 (x,y,z), 4-6: row1, 8-10: row2.
    // Compute length of each row to get scale factor along that axis.

    float *scaleField = (float *)outputStruct;

    // Scale X (length of first row)
    scaleField[0x134 / 4] = SQRT(matrix4x4[0]*matrix4x4[0] + matrix4x4[1]*matrix4x4[1] + matrix4x4[2]*matrix4x4[2]);

    // Scale Y (length of second row)
    scaleField[0x138 / 4] = SQRT(matrix4x4[4]*matrix4x4[4] + matrix4x4[5]*matrix4x4[5] + matrix4x4[6]*matrix4x4[6]);

    // Scale Z (length of third row)
    scaleField[0x13c / 4] = SQRT(matrix4x4[8]*matrix4x4[8] + matrix4x4[9]*matrix4x4[9] + matrix4x4[10]*matrix4x4[10]);
}