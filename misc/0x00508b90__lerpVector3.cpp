// FUNC_NAME: lerpVector3
// Address: 0x00508b90
// Interpolates a 3-component vector (x, y, z) linearly between 'from' and 'to' by factor 't'.
// The fourth component (w) is preserved unchanged.
void lerpVector3(float *out, const float *from, const float *to, float t)
{
    out[0] = from[0] + (to[0] - from[0]) * t;
    out[1] = from[1] + (to[1] - from[1]) * t;
    out[2] = from[2] + (to[2] - from[2]) * t;
    // w (out[3]) is not interpolated; it retains its original value.
}