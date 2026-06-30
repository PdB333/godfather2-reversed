// FUNC_ADDR: 0x0044c560 - Utility: Vector4 scalar multiplication
// Multiplies each component of a 4-element float vector by a scalar.
void scaleVector4(float scale, const float* src, float* dst) {
    float x = src[0];
    float y = src[1];
    float z = src[2];
    float w = src[3];

    dst[0] = scale * x;
    dst[1] = scale * y;
    dst[2] = scale * z;
    dst[3] = scale * w;
}