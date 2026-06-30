// FUNC_NAME: MathUtils::lerpVector4
void __thiscall MathUtils::lerpVector4(float *this, float *target, float t, float *result)
{
  float srcX = this[0];  // +0x00
  float srcY = this[1];  // +0x04
  float srcZ = this[2];  // +0x08
  float srcW = this[3];  // +0x0C
  
  float dstX = target[0];  // +0x00
  float dstY = target[1];  // +0x04
  float dstZ = target[2];  // +0x08
  float dstW = target[3];  // +0x0C
  
  // Linear interpolation: result = src + (dst - src) * t
  result[0] = (dstX - srcX) * t + srcX;
  result[1] = (dstY - srcY) * t + srcY;
  result[2] = (dstZ - srcZ) * t + srcZ;
  result[3] = (dstW - srcW) * t + srcW;
}