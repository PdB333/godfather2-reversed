// FUNC_NAME: Vector4::scaleToOutput
void __thiscall Vector4::scaleToOutput(float *out, float scalar)
{
    // Scale the 4-component vector (x, y, z, w) by scalar and store to out
    float x = this->x;  // +0x00
    float y = this->y;  // +0x04
    float z = this->z;  // +0x08
    float w = this->w;  // +0x0C

    *out = x * scalar;
    out[1] = y * scalar;
    out[2] = z * scalar;
    out[3] = w * scalar;
}