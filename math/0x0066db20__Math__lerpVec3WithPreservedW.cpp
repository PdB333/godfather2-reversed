// FUNC_NAME: Math::lerpVec3WithPreservedW
// Address: 0x0066db20
// Performs a linear interpolation of the first three components of two 4-element vectors,
// keeping the fourth component (w) unchanged. Result is written to the output vector.
// Parameters:
//   result  - output float[4]
//   a       - input float[4] (source A)
//   b       - input float[4] (source B)
//   t       - interpolation factor (0.0 = a, 1.0 = b)
void __fastcall lerpVec3WithPreservedW(float *result, float *a, float *b, float t)
{
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // not used in calculation, kept from original
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // not used, result[3] is overwritten later

    // Interpolate first three components: result = t*a + b
    result[0] = t * ax + bx;
    result[1] = t * ay + by;
    result[2] = t * az + bz;
    result[3] = t * aw + bw; // computed but then discarded

    // Preserve original w component (before interpolation)
    result[3] = aw;
}