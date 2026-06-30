// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *this, float *outResult, float scalar)
{
    float x = this[0]; // +0x00
    float y = this[1]; // +0x04
    float z = this[2]; // +0x08
    float w = this[3]; // +0x0C

    outResult[0] = scalar * x;
    outResult[1] = scalar * y;
    outResult[2] = scalar * z;
    outResult[3] = scalar * w;
}