// FUNC_NAME: Vec3SubWithW
void Vec3SubWithW(const float* a, const float* b, float* out)
{
    // Save the original w component of the output vector (index 3)
    float savedW = out[3];

    // Subtract the first three components (x, y, z)
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];

    // Temporarily assign w as a[3] - b[3], then restore savedW
    out[3] = a[3] - b[3];
    out[3] = savedW;
}