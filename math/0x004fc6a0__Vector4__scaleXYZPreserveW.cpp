// FUNC_NAME: Vector4::scaleXYZPreserveW
void __fastcall Vector4::scaleXYZPreserveW(Vector4* this, const float* src, float scalar)
{
    // Vector4 layout: x (+0x00), y (+0x04), z (+0x08), w (+0x0C)
    float origW = this->w;  // +0x0C

    this->x = src[0] * scalar;
    this->y = src[1] * scalar;
    this->z = src[2] * scalar;
    this->w = origW;  // preserve original w component
}