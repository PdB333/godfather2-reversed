// FUNC_NAME: MathUtils::lerpVec3WithW
void __fastcall MathUtils::lerpVec3WithW(float* dest, float* src1, float weight1, float* src2, float weight2)
{
    // Blend src1 and src2 by weights weight2 and weight1 respectively, storing into dest.
    // Only the first three components (x,y,z) are blended; the fourth (w) is preserved from dest.
    float src1_y = src1[1];
    float src1_z = src1[2];
    float src1_w = src1[3];
    float src2_y = src2[1];
    float src2_z = src2[2];
    float src2_w = src2[3];
    float dest_w = dest[3];

    dest[0] = weight2 * src1[0] + weight1 * src2[0];
    dest[1] = weight2 * src1_y + weight1 * src2_y;
    dest[2] = weight2 * src1_z + weight1 * src2_z;
    dest[3] = dest_w;
}