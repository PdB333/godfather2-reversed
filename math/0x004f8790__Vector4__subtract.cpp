// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(float *this, float *other, float *result)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;

  x1 = this[1]; // +0x04
  y1 = this[2]; // +0x08
  z1 = this[3]; // +0x0C
  x2 = other[1]; // +0x04
  y2 = other[2]; // +0x08
  z2 = other[3]; // +0x0C

  result[0] = this[0] - other[0]; // x component
  result[1] = x1 - x2;            // y component
  result[2] = y1 - y2;            // z component
  result[3] = z1 - z2;            // w component
}