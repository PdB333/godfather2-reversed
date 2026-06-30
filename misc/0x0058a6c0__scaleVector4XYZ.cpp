// FUNC_NAME: scaleVector4XYZ
void __fastcall scaleVector4XYZ(float* dest, const float* src, float scale)
{
    float savedW = dest[3];
    dest[0] = src[0] * scale;
    dest[1] = src[1] * scale;
    dest[2] = src[2] * scale;
    dest[3] = savedW;
}