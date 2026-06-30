// FUNC_NAME: lerpVector3PreserveW
void __fastcall lerpVector3PreserveW(float* out, const float* a, const float* b, float t)
{
    // Interpolate first three components (x, y, z) between vectors a and b
    // Preserve the fourth component (w) of the output vector
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // unused in interpolation
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3]; // unused in interpolation

    float savedW = out[3]; // preserve original w of output

    out[0] = (bx - ax) * t + ax;
    out[1] = (by - ay) * t + ay;
    out[2] = (bz - az) * t + az;
    out[3] = savedW; // restore original w
}