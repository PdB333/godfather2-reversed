// FUNC_NAME: interpolateVector3PreserveW
// 0x004f1ce0: Linear interpolation between two 4-component vectors, preserving the W (fourth) component of the destination.
void interpolateVector3PreserveW(const float* from, const float* to, float t, float* out)
{
    float fromY = from[1];
    float fromZ = from[2];
    float fromW = from[3]; // unused
    float toY = to[1];
    float toZ = to[2];
    float toW = to[3]; // unused
    float originalOutW = out[3];

    out[0] = (to[0] - from[0]) * t + from[0];
    out[1] = (toY - fromY) * t + fromY;
    out[2] = (toZ - fromZ) * t + fromZ;
    out[3] = originalOutW; // W component preserved
}