// FUNC_NAME: Vector4::scaleTo
void __thiscall Vector4::scaleTo(float *out, float scalar) {
    // this points to a Vector4 with 4 floats at offsets 0x00, 0x04, 0x08, 0x0C
    float x = *(float *)this;         // +0x00
    float y = *((float *)this + 1);   // +0x04
    float z = *((float *)this + 2);   // +0x08
    float w = *((float *)this + 3);   // +0x0C

    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}