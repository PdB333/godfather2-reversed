// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(float *this, float t, float *result)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;

  x1 = this[1]; // +0x04
  y1 = this[2]; // +0x08
  z1 = this[3]; // +0x0C
  w1 = this[4]; // +0x10

  x2 = result[1]; // +0x04
  y2 = result[2]; // +0x08
  z2 = result[3]; // +0x0C
  w2 = result[4]; // +0x10

  // Linear interpolation: result = this + t * (target - this)
  // But here it's: result = this + t * target (assuming target is in param_1)
  *result = t * *this + *result; // +0x00
  result[1] = t * x1 + x2;
  result[2] = t * y1 + y2;
  result[3] = t * z1 + z2;
}