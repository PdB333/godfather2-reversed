// FUNC_NAME: Vector4::scaleXYZ
void __fastcall Vector4::scaleXYZ(float *thisOut, float *vecIn, float scalar)
{
    float y = vecIn[1];
    float z = vecIn[2];
    float w = vecIn[3];
    float origW = thisOut[3]; // +0x0C

    thisOut[0] = scalar * vecIn[0]; // +0x00
    thisOut[1] = scalar * y;        // +0x04
    thisOut[2] = scalar * z;        // +0x08
    thisOut[3] = scalar * w;        // +0x0C
    thisOut[3] = origW;             // restore original W component
}