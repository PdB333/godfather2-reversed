// FUNC_NAME: mathVec3Add
void __fastcall mathVec3Add(float *result, float *a, float *b)
{
    // Adds the first three components of two 4D vectors (a and b)
    // and stores the result in 'result', preserving the original 4th component of result.
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // loaded but not used
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // loaded but not used
    float originalResultW = result[3]; // save the destination's w
    result[0] = ax + bx;
    result[1] = ay + by;
    result[2] = az + bz;
    result[3] = originalResultW; // keep unchanged
}