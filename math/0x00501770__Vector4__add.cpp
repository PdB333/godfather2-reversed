// FUNC_NAME: Vector4::add
void __thiscall Vector4::add(float *thisVec, float *otherVec, float *resultVec)
{
    float x1 = thisVec[0]; // +0x00
    float y1 = thisVec[1]; // +0x04
    float z1 = thisVec[2]; // +0x08
    float w1 = thisVec[3]; // +0x0C

    float x2 = otherVec[0]; // +0x00
    float y2 = otherVec[1]; // +0x04
    float z2 = otherVec[2]; // +0x08
    float w2 = otherVec[3]; // +0x0C

    resultVec[0] = x1 + x2;
    resultVec[1] = y1 + y2;
    resultVec[2] = z1 + z2;
    resultVec[3] = w1 + w2;
}