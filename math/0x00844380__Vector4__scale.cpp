// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *out, float scalar) {
    // Members: +0x0 x, +0x4 y, +0x8 z, +0xC w (4 floats)
    float x = this[0];
    float y = this[1];
    float z = this[2];
    float w = this[3];

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}