// FUNC_NAME: MathUtils::vectorSubtract3
void __fastcall vectorSubtract3(float* dest, const float* src1, const float* src2)
{
    // Preserve the original w component of dest (index 3)
    float w = dest[3];
    // Subtract the first three components (x, y, z)
    dest[0] = src1[0] - src2[0];
    dest[1] = src1[1] - src2[1];
    dest[2] = src1[2] - src2[2];
    // Restore the original w component (unchanged)
    dest[3] = w;
}