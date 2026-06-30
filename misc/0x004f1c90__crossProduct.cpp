// FUNC_NAME: crossProduct
void crossProduct(const float* a, const float* b, float* out)
{
    // Compute cross product of 3D vectors stored in first three components of 4D vectors.
    // The fourth component of 'out' is preserved (not modified).
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // unused in cross, but loaded

    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // unused

    float originalOutW = out[3]; // preserve original w component

    out[0] = ay * bz - az * by;
    out[1] = az * bx - ax * bz;
    out[2] = ax * by - ay * bx;
    out[3] = originalOutW; // restore original w
}