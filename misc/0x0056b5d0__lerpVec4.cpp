// FUNC_NAME: lerpVec4
// address 0x0056b5d0: 4-component linear interpolation: out = weight1 * vec1 + weight2 * vec2
// weights and vectors are floats; typically used for quaternion or 4D vector blending.
void lerpVec4(float weight1, float* vec1, float weight2, float* vec2, float* outVec)
{
    // read vec2 components (index 1..3) first, then vec1 components (index 1..3)
    float v2y = vec2[1];
    float v2z = vec2[2];
    float v2w = vec2[3];

    float v1y = vec1[1];
    float v1z = vec1[2];
    float v1w = vec1[3];

    // compute linear blend for all four components
    outVec[0] = weight2 * vec2[0] + weight1 * vec1[0];
    outVec[1] = weight2 * v2y + weight1 * v1y;
    outVec[2] = weight2 * v2z + weight1 * v1z;
    outVec[3] = weight2 * v2w + weight1 * v1w;
}