// FUNC_NAME: Vector4::scaleAndPreserveW
void __fastcall Vector4::scaleAndPreserveW(float *this, float *source, float scale)
{
    float w;
    w = source[3];           // +0x0C (W component)
    this[0] = scale * source[0]; // +0x00 (X)
    this[1] = scale * source[1]; // +0x04 (Y)
    this[2] = scale * source[2]; // +0x08 (Z)
    this[3] = w;                // +0x0C (W preserved, not scaled)
}