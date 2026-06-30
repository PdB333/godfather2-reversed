// FUNC_NAME: Matrix4::assignWithChangeCheck
// Address: 0x00612f10
// Role: Copy a 4x4 matrix from source to destination, return true if any element changed.

bool Matrix4::assignWithChangeCheck(float* dest, const float* src)
{
    // Save old values for comparison
    float old0 = dest[0], old1 = dest[1], old2 = dest[2], old3 = dest[3];
    float old4 = dest[4], old5 = dest[5], old6 = dest[6], old7 = dest[7];
    float old8 = dest[8], old9 = dest[9], old10 = dest[10], old11 = dest[11];
    float old12 = dest[12], old13 = dest[13], old14 = dest[14], old15 = dest[15];

    // Copy new matrix
    dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; dest[3] = src[3];
    dest[4] = src[4]; dest[5] = src[5]; dest[6] = src[6]; dest[7] = src[7];
    dest[8] = src[8]; dest[9] = src[9]; dest[10] = src[10]; dest[11] = src[11];
    dest[12] = src[12]; dest[13] = src[13]; dest[14] = src[14]; dest[15] = src[15];

    // Check for any change
    if (old0 != dest[0] || old1 != dest[1] || old2 != dest[2] || old3 != dest[3] ||
        old4 != dest[4] || old5 != dest[5] || old6 != dest[6] || old7 != dest[7] ||
        old8 != dest[8] || old9 != dest[9] || old10 != dest[10] || old11 != dest[11] ||
        old12 != dest[12] || old13 != dest[13] || old14 != dest[14] || old15 != dest[15])
    {
        return true;
    }
    return false;
}