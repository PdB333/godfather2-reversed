// FUNC_NAME: Vector4::scaledAdd
// Address: 0x006d4040
// Role: Multiplies this vector by a scalar and adds another vector, storing result in output (result = this * scale + other).
void __thiscall Vector4::scaledAdd(const float* other, float scale, float* out) const
{
    // this: implicit first parameter (in_EAX)
    // other: second vector (param_1)
    // scale: scalar multiplier (param_2)
    // out: output vector (param_3)

    float thisX = this[0];   // +0x00
    float thisY = this[1];   // +0x04
    float thisZ = this[2];   // +0x08
    float thisW = this[3];   // +0x0C

    float otherX = other[0]; // +0x00
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C

    out[0] = scale * thisX + otherX;
    out[1] = scale * thisY + otherY;
    out[2] = scale * thisZ + otherZ;
    out[3] = scale * thisW + otherW;
}