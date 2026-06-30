// FUNC_NAME: getGlobalMatrix
void getGlobalMatrix(uint32_t matrix[16])
{
    // Copy a 4x4 matrix of uint32 from global memory at 0x011f6720
    matrix[0]  = _DAT_011f6720;
    matrix[1]  = uRam011f6724;
    matrix[2]  = uRam011f6728;
    matrix[3]  = uRam011f672c;
    matrix[4]  = _DAT_011f6730;
    matrix[5]  = uRam011f6734;
    matrix[6]  = uRam011f6738;
    matrix[7]  = uRam011f673c;
    matrix[8]  = _DAT_011f6740;
    matrix[9]  = uRam011f6744;
    matrix[10] = uRam011f6748;
    matrix[11] = uRam011f674c;
    matrix[12] = _DAT_011f6750;
    matrix[13] = uRam011f6754;
    matrix[14] = uRam011f6758;
    matrix[15] = uRam011f675c;
}