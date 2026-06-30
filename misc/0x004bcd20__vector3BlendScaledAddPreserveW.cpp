// FUNC_NAME: vector3BlendScaledAddPreserveW
void __fastcall vector3BlendScaledAddPreserveW(float* dst, const float* from, const float* to, float t)
{
    // Blend the first three components: dst = t * from + to, but preserve the original dst[3] (w/scale component)
    // This is used for interpolating a 3D vector with a weight, while keeping the fourth component unchanged.
    // Parameters:
    //   dst  - Output vector (4 floats). The fourth component is left untouched.
    //   from - Source vector A (first three components used)
    //   to   - Source vector B (first three components used)
    //   t    - Blend factor
    float savedW = dst[3]; // +0x0C: preserve the w component

    dst[0] = t * from[0] + to[0];
    dst[1] = t * from[1] + to[1];
    dst[2] = t * from[2] + to[2];
    dst[3] = t * from[3] + to[3]; // computed but will be overwritten immediately

    dst[3] = savedW; // restore original w
}