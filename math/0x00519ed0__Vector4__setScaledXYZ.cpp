// FUNC_NAME: Vector4::setScaledXYZ
void __fastcall Vector4::setScaledXYZ(float *src, float scalar)
{
    float srcY = src[1];  // +0x04
    float srcZ = src[2];  // +0x08
    float srcW = src[3];  // +0x0C (unused, as w is preserved)
    float origW = this->w; // save original w (this + 0x0C)

    this->x = scalar * src[0]; // +0x00
    this->y = scalar * srcY;   // +0x04
    this->z = scalar * srcZ;   // +0x08
    this->w = scalar * srcW;   // temporary scaled w (overwritten next)
    this->w = origW;           // restore original w (only xyz changed)
}