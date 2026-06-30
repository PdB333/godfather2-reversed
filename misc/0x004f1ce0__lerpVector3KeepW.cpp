// FUNC_NAME: lerpVector3KeepW
void lerpVector3KeepW(const float* from, const float* to, float t, float* out)
{
    // Cache source vector components (y,z,w) to avoid repeated reads
    float fromY = from[1];
    float fromZ = from[2];
    float fromW = from[3];
    float toY = to[1];
    float toZ = to[2];
    float toW = to[3];

    // Preserve the original w component of the output vector
    float originalOutW = out[3];

    // Linear interpolation of x,y,z components: out[i] = (to[i] - from[i])*t + from[i]
    out[0] = (to[0] - from[0]) * t + from[0];  // x
    out[1] = (toY - fromY) * t + fromY;        // y
    out[2] = (toZ - fromZ) * t + fromZ;        // z
    out[3] = (toW - fromW) * t + fromW;        // w (temporary)

    // Restore the original w component (kept unchanged)
    out[3] = originalOutW;
}