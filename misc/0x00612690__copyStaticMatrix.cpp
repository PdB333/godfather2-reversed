// FUNC_NAME: copyStaticMatrix
void copyStaticMatrix(float* outMatrix)
{
    // Copy a static 4x4 matrix from global memory at 0x011f6720 (16 floats)
    // Assumes outMatrix points to at least 16 floats
    float row0_0 = *(float*)0x011f6720;
    float row0_1 = *(float*)0x011f6724;
    float row0_2 = *(float*)0x011f6728;
    float row0_3 = *(float*)0x011f672c;
    float row1_0 = *(float*)0x011f6730;
    float row1_1 = *(float*)0x011f6734;
    float row1_2 = *(float*)0x011f6738;
    float row1_3 = *(float*)0x011f673c;
    float row2_0 = *(float*)0x011f6740;
    float row2_1 = *(float*)0x011f6744;
    float row2_2 = *(float*)0x011f6748;
    float row2_3 = *(float*)0x011f674c;
    float row3_0 = *(float*)0x011f6750;
    float row3_1 = *(float*)0x011f6754;
    float row3_2 = *(float*)0x011f6758;
    float row3_3 = *(float*)0x011f675c;

    outMatrix[0]  = row0_0;
    outMatrix[1]  = row0_1;
    outMatrix[2]  = row0_2;
    outMatrix[3]  = row0_3;
    outMatrix[4]  = row1_0;
    outMatrix[5]  = row1_1;
    outMatrix[6]  = row1_2;
    outMatrix[7]  = row1_3;
    outMatrix[8]  = row2_0;
    outMatrix[9]  = row2_1;
    outMatrix[10] = row2_2;
    outMatrix[11] = row2_3;
    outMatrix[12] = row3_0;
    outMatrix[13] = row3_1;
    outMatrix[14] = row3_2;
    outMatrix[15] = row3_3;
}