// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(float *this, float *other, float *result)
{
  float x1 = this[0];
  float y1 = this[1];
  float z1 = this[2];
  float w1 = this[3]; // +0x0C, typically unused or 1.0f
  float x2 = other[0];
  float y2 = other[1];
  float z2 = other[2];
  float w2 = other[3]; // +0x0C

  result[0] = x1 - x2;
  result[1] = y1 - y2;
  result[2] = z1 - z2;
  result[3] = w1 - w2;
}