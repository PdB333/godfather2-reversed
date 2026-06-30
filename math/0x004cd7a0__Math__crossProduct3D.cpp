// FUNC_NAME: Math::crossProduct3D
void __thiscall crossProduct3D(float *thisVec, float *otherVec, float *outVec)
{
    float x1 = thisVec[0];  // +0x00
    float y1 = thisVec[1];  // +0x04
    float z1 = thisVec[2];  // +0x08
    float w1 = thisVec[3];  // +0x0C (unused, w is set to 0)

    float x2 = otherVec[0]; // +0x00
    float y2 = otherVec[1]; // +0x04
    float z2 = otherVec[2]; // +0x08
    float w2 = otherVec[3]; // +0x0C (unused)

    // Cross product: result = this × other
    outVec[0] = y1 * z2 - z1 * y2; // x component
    outVec[1] = z1 * x2 - x1 * z2; // y component
    outVec[2] = x1 * y2 - y1 * x2; // z component
    outVec[3] = 0.0f;               // w component (always 0 for 3D cross product)
}