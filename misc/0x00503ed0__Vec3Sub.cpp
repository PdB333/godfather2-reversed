// FUNC_NAME: Vec3Sub
void __fastcall Vec3Sub(float* dest, float* src1, float* src2)
{
    float savedW;
    // Preserve the 4th (homogeneous or w) component of destination
    savedW = dest[3];
    // Subtract first three components
    dest[0] = src1[0] - src2[0];
    dest[1] = src1[1] - src2[1];
    dest[2] = src1[2] - src2[2];
    // Restore the 4th component unchanged
    dest[3] = savedW;
}