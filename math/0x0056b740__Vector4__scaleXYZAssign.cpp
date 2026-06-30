// FUNC_NAME: Vector4::scaleXYZAssign

void __thiscall Vector4::scaleXYZAssign(float *this, const float *src, float scale)
{
    float srcY = src[1];
    float srcZ = src[2];
    float srcW = src[3];
    float dstW = this[3];  // Preserve the original W component

    this[0] = scale * src[0];
    this[1] = scale * srcY;
    this[2] = scale * srcZ;
    this[3] = dstW;         // Restore W, leaving it unchanged
}