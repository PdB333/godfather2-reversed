// FUNC_NAME: Vector4::scaleXYZKeepW
void __fastcall Vector4::scaleXYZKeepW(float *this, float *vec, float scale)
{
    float y = vec[1];
    float z = vec[2];
    float w = vec[3];
    float originalW = this[3]; // +0x0C

    this[0] = scale * vec[0]; // +0x00
    this[1] = scale * y;      // +0x04
    this[2] = scale * z;      // +0x08
    this[3] = scale * w;      // +0x0C
    this[3] = originalW;      // restore original W component
}