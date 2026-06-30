// FUNC_NAME: Vector3::subtract

void __fastcall Vector3::subtract(float* dest, const float* srcA, const float* srcB)
{
    // dest[0..2] = srcA[0..2] - srcB[0..2]; preserve dest[3] (w component)
    float savedW = dest[3];
    dest[0] = srcA[0] - srcB[0];
    dest[1] = srcA[1] - srcB[1];
    dest[2] = srcA[2] - srcB[2];
    dest[3] = savedW;
}