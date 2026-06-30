// FUNC_NAME: Vector4f::scale
// Function address: 0x004f5890
// Multiplies a 4-component vector (this) by a scalar and stores result in outVec
void __thiscall Vector4f::scale(float *outVec, float scalar)
{
    float x = this[0]; // +0x00: x component
    float y = this[1]; // +0x04: y component
    float z = this[2]; // +0x08: z component
    float w = this[3]; // +0x0C: w component

    outVec[0] = scalar * x;
    outVec[1] = scalar * y;
    outVec[2] = scalar * z;
    outVec[3] = scalar * w;
}