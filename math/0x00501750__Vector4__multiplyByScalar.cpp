// FUNC_NAME: Vector4::multiplyByScalar
void __thiscall Vector4::multiplyByScalar(Vector4* outResult, float scalar) const
{
    // Read components from this (the source vector, passed in EAX)
    float vx = x;   // +0x00
    float vy = y;   // +0x04
    float vz = z;   // +0x08
    float vw = w;   // +0x0C

    // Scale and store in output
    outResult->x = scalar * vx;
    outResult->y = scalar * vy;
    outResult->z = scalar * vz;
    outResult->w = scalar * vw;
}