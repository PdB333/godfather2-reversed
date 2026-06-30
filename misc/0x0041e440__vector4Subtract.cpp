// FUNC_NAME: vector4Subtract
// Function: 0041e440 - Subtracts two 4-component vectors (float[4]).
// The function computes: dst = src1 - src2 component-wise.
void vector4Subtract(const float *src1, const float *src2, float *dst)
{
    float y1 = src1[1]; // second component
    float z1 = src1[2]; // third component
    float w1 = src1[3]; // fourth component
    float y2 = src2[1];
    float z2 = src2[2];
    float w2 = src2[3];

    dst[0] = src1[0] - src2[0]; // x component
    dst[1] = y1 - y2;
    dst[2] = z1 - z2;
    dst[3] = w1 - w2;
}