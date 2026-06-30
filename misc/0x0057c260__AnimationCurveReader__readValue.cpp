// FUNC_NAME: AnimationCurveReader::readValue

void __thiscall AnimationCurveReader::readValue(int index, int mode, int extraParam, float *output)
// Uses ESI as output pointer; registers: EAX = data buffer base, XMM0 = result from called helpers
{
    float fVar1;
    float fVar2;
    float *outputPtr; // unaff_ESI
    int dataBasePtr;  // in_EAX - pointer to raw data

    switch(mode) {
    case 1:
        FUN_0057c110(extraParam);
        *outputPtr = *((float*)0); // in_XMM0_Da - result from helper
        break;
    case 2:
        FUN_0057c160();
        *outputPtr = *((float*)0); // in_XMM0_Da
        break;
    case 3:
        FUN_0057c1d0();
        *outputPtr = *((float*)0); // in_XMM0_Da
        break;
    case 4:
    {
        // Read 4 bytes as little-endian integer, then convert to float
        unsigned int raw = (unsigned char)(*(byte*)(dataBasePtr + 5 + index * 4)) << 24 |
                          (unsigned char)(*(byte*)(dataBasePtr + 4 + index * 4)) << 16 |
                          (unsigned char)(*(byte*)(dataBasePtr + 3 + index * 4)) << 8 |
                          (unsigned char)(*(byte*)(dataBasePtr + 2 + index * 4));
        *outputPtr = (float)raw;
        break;
    }
    case 6:
    case 7:
    {
        // Read two 24-bit fixed-point numbers (shifted left by 8 to become 32-bit)
        fVar1 = (float)((unsigned int)(*(uint3*)(dataBasePtr + 2)) << 8);
        fVar2 = (float)((unsigned int)(*(uint3*)(dataBasePtr + 5)) << 8);
        if (mode == 6) {
            // Linear interpolation with one table lookup
            *outputPtr = g_interpolationTable[(unsigned char)(*(byte*)(dataBasePtr + 8 + index))] * fVar2 + fVar1;
        } else { // mode == 7
            // Bilinear interpolation with two table lookups and global scale
            *outputPtr = (g_interpolationTable[(unsigned char)(*(byte*)(dataBasePtr + 9 + index * 2))] * g_scaleFactor +
                         g_interpolationTable[(unsigned char)(*(byte*)(dataBasePtr + 8 + index * 2))]) * fVar2 + fVar1;
        }
        break;
    }
    default:
        break;
    }
}