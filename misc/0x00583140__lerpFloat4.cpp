// FUNC_NAME: lerpFloat4
void __thiscall lerpFloat4(float *thisVec, float *otherVec, float *outVec, float t)
{
    // Linear interpolation of 4-element float vectors: out = lerp(this, other, t)
    float a0 = thisVec[0];
    float a1 = thisVec[1];
    float a2 = thisVec[2];
    float a3 = thisVec[3];

    float b0 = otherVec[0];
    float b1 = otherVec[1];
    float b2 = otherVec[2];
    float b3 = otherVec[3];

    outVec[0] = (b0 - a0) * t + a0;
    outVec[1] = (b1 - a1) * t + a1;
    outVec[2] = (b2 - a2) * t + a2;
    outVec[3] = (b3 - a3) * t + a3;
}