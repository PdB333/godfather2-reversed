// FUNC_NAME: vectorLerp4
// Address: 0x004af2c0
// Role: Linear interpolation between two 4-component float vectors (e.g., quaternions or 4D points).
// Parameters:
//   from - source vector (4 floats)
//   to   - target vector (4 floats)
//   t    - interpolation factor (0.0 = from, 1.0 = to)
//   out  - output vector (4 floats)
void vectorLerp4(const float* from, const float* to, float t, float* out)
{
    float f1 = from[1];
    float f2 = from[2];
    float f3 = from[3];
    float t1 = to[1];
    float t2 = to[2];
    float t3 = to[3];

    out[0] = (to[0] - from[0]) * t + from[0];
    out[1] = (t1 - f1) * t + f1;
    out[2] = (t2 - f2) * t + f2;
    out[3] = (t3 - f3) * t + f3;
}