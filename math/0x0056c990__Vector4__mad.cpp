// FUNC_NAME: Vector4::mad
// Address: 0x0056c990
// Role: Multiply-add operation: result = scalar * this + vecA (component-wise for 4 floats)
void __thiscall Vector4::mad(const Vector4& vecA, float scalar, Vector4& result) const
{
    // Load components from this (the vector to be scaled)
    float thisX = this->x;   // +0x00
    float thisY = this->y;   // +0x04
    float thisZ = this->z;   // +0x08
    float thisW = this->w;   // +0x0C

    // Load components from vecA (the vector to add)
    float vecAX = vecA.x;    // +0x00
    float vecAY = vecA.y;    // +0x04
    float vecAZ = vecA.z;    // +0x08
    float vecAW = vecA.w;    // +0x0C

    // Compute result = scalar * this + vecA
    result.x = scalar * thisX + vecAX;
    result.y = scalar * thisY + vecAY;
    result.z = scalar * thisZ + vecAZ;
    result.w = scalar * thisW + vecAW;
}