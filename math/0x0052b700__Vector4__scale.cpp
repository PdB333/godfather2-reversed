// FUNC_NAME: Vector4::scale
// Address: 0x0052b700
// Role: Scales a 4-component vector by a scalar and stores result in output.
// Fields (this): +0x00 float x, +0x04 float y, +0x08 float z, +0x0C float w

void __thiscall Vector4::scale(float *out, float scalar) const
{
    // Read source components from this pointer
    float x = this->x;       // *(float*)(this+0x00)
    float y = this->y;       // *(float*)(this+0x04)
    float z = this->z;       // *(float*)(this+0x08)
    float w = this->w;       // *(float*)(this+0x0C)

    // Scale and write to output
    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}