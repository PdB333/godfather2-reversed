// FUNC_NAME: Quaternion::lerp
void __thiscall Quaternion::lerp(const float* target, float t, float* result) const
{
    float srcX = this[0];
    float srcY = this[1];
    float srcZ = this[2];
    float srcW = this[3];

    float dstX = target[0];
    float dstY = target[1];
    float dstZ = target[2];
    float dstW = target[3];

    result[0] = (dstX - srcX) * t + srcX;
    result[1] = (dstY - srcY) * t + srcY;
    result[2] = (dstZ - srcZ) * t + srcZ;
    result[3] = (dstW - srcW) * t + srcW;
}