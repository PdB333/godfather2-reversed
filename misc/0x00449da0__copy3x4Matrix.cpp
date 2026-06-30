// FUNC_NAME: copy3x4Matrix
void copy3x4Matrix(float *dest, float *src)
{
    // Copy the first 3 columns of each row from a row-major 4x4 matrix
    // Equivalent to copying the 3x4 affine transformation part (rotation + translation)
    // Indices: rows 0-3, columns 0-2 (skipping column 3 which is typically [0,0,0,1])
    dest[0] = src[0];   // row0, col0
    dest[1] = src[1];   // row0, col1
    dest[2] = src[2];   // row0, col2
    dest[3] = src[4];   // row1, col0
    dest[4] = src[5];   // row1, col1
    dest[5] = src[6];   // row1, col2
    dest[6] = src[8];   // row2, col0
    dest[7] = src[9];   // row2, col1
    dest[8] = src[10];  // row2, col2
    dest[9] = src[12];  // row3, col0  (translation X)
    dest[10] = src[13]; // row3, col1  (translation Y)
    dest[11] = src[14]; // row3, col2  (translation Z)
}