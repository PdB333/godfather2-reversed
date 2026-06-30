// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(const float* target, float t, float* out) const
{
    // This function performs component-wise linear interpolation between the current vector (this)
    // and the target vector (target) using factor t (0.0 to 1.0), storing the result in out.

    float srcX = this->x; // +0x00
    float srcY = this->y; // +0x04
    float srcZ = this->z; // +0x08
    float srcW = this->w; // +0x0C

    float dstX = target[0];
    float dstY = target[1];
    float dstZ = target[2];
    float dstW = target[3];

    out[0] = (dstX - srcX) * t + srcX;
    out[1] = (dstY - srcY) * t + srcY;
    out[2] = (dstZ - srcZ) * t + srcZ;
    out[3] = (dstW - srcW) * t + srcW;
}