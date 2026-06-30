// FUNC_NAME: blendVector3WithPreservedW
void __fastcall blendVector3WithPreservedW(float* out, float* src1, float* src2, float t)
{
    // Save original fourth component of output
    float savedW = out[3];

    // Linear interpolation of first three components: out = t * src1 + src2
    out[0] = t * src1[0] + src2[0];
    out[1] = t * src1[1] + src2[1];
    out[2] = t * src1[2] + src2[2];

    // Restore the fourth component unchanged
    out[3] = savedW;
}