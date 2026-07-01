// FUNC_NAME: Vector4::subtract
void Vector4::subtract(const float* a, const float* b, float* out)
{
    float a1 = a[1]; // +0x04
    float a2 = a[2]; // +0x08
    float a3 = a[3]; // +0x0C
    float b1 = b[1]; // +0x04
    float b2 = b[2]; // +0x08
    float b3 = b[3]; // +0x0C

    out[0] = a[0] - b[0]; // +0x00
    out[1] = a1 - b1;      // +0x04
    out[2] = a2 - b2;      // +0x08
    out[3] = a3 - b3;      // +0x0C
}