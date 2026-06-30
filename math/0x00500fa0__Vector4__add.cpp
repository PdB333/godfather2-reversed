// FUNC_NAME: Vector4::add
// Address: 0x00500fa0
// Role: Adds two 4-component vectors (this + other = out)
// Fields: in_EAX[0-3] correspond to x, y, z, w of the vector

void __thiscall Vector4::add(const Vector4& other, Vector4& out) const
{
    // Load this vector components
    float fVar1 = this->y;   // in_EAX[1]
    float fVar2 = this->z;   // in_EAX[2]
    float fVar3 = this->w;   // in_EAX[3]
    // Load other vector components
    float fVar4 = other.y;  // param_1[1]
    float fVar5 = other.z;  // param_1[2]
    float fVar6 = other.w;  // param_1[3]

    // Compute sum
    out.x = this->x + other.x;  // *in_EAX + *param_1
    out.y = fVar1 + fVar4;
    out.z = fVar2 + fVar5;
    out.w = fVar3 + fVar6;
    return;
}