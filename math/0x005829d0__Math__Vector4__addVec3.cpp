// FUNC_NAME: Math::Vector4::addVec3
void __thiscall Vector4::addVec3(const float* aVec3, const float* bVec3)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;

    fVar2 = aVec3[1];      // aVec3.y
    fVar3 = aVec3[2];      // aVec3.z
    fVar4 = aVec3[3];      // aVec3.w (unused in addition but read)
    fVar5 = bVec3[1];      // bVec3.y
    fVar6 = bVec3[2];      // bVec3.z
    fVar7 = bVec3[3];      // bVec3.w (unused in addition but read)

    fVar1 = this->data[3]; // preserve w component of destination

    this->data[0] = aVec3[0] + bVec3[0]; // x += x
    this->data[1] = fVar2 + fVar5;       // y += y
    this->data[2] = fVar3 + fVar6;       // z += z
    this->data[3] = fVar1;               // w unchanged

    return;
}