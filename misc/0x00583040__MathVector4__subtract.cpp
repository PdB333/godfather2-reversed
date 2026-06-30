// FUNC_NAME: MathVector4::subtract
void __thiscall MathVector4::subtract(float *thisVec, float *otherVec, float *resultVec)
{
    float thisX = thisVec[0];
    float thisY = thisVec[1];
    float thisZ = thisVec[2];
    float thisW = thisVec[3];
    
    float otherX = otherVec[0];
    float otherY = otherVec[1];
    float otherZ = otherVec[2];
    float otherW = otherVec[3];
    
    resultVec[0] = thisX - otherX;
    resultVec[1] = thisY - otherY;
    resultVec[2] = thisZ - otherZ;
    resultVec[3] = thisW - otherW;
}