// FUNC_NAME: multiplyVec3ComponentwisePreserveW
void __fastcall multiplyVec3ComponentwisePreserveW(float *out, float *a, float *b)
{
    // Performs component-wise multiplication of a and b for elements 0-2,
    // then overwrites element 3 with its original value from out.
    float a_y = a[1];
    float a_z = a[2];
    float a_w = a[3];
    float b_y = b[1];
    float b_z = b[2];
    float b_w = b[3];
    float out_w = out[3]; // preserve the destination's w component

    out[0] = a[0] * b[0]; // x = a.x * b.x
    out[1] = a_y * b_y;   // y = a.y * b.y
    out[2] = a_z * b_z;   // z = a.z * b.z
    out[3] = a_w * b_w;   // temporary write w product
    out[3] = out_w;       // restore original w
}