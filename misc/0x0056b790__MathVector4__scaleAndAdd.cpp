// FUNC_NAME: MathVector4::scaleAndAdd
void __thiscall MathVector4::scaleAndAdd(const float* otherVec, float scale, float* outVec) const
{
    // this is the source vector (4 floats)
    // Computes: outVec = scale * this + otherVec
    float srcX = this->x;   // +0x00
    float srcY = this->y;   // +0x04
    float srcZ = this->z;   // +0x08
    float srcW = this->w;   // +0x0C

    float othX = otherVec[0];
    float othY = otherVec[1];
    float othZ = otherVec[2];
    float othW = otherVec[3];

    outVec[0] = scale * srcX + othX;
    outVec[1] = scale * srcY + othY;
    outVec[2] = scale * srcZ + othZ;
    outVec[3] = scale * srcW + othW;
}