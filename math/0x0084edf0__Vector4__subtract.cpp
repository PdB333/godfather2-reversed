// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(float *this, float *other, float *result)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;

  x1 = this[0]; // +0x00
  y1 = this[1]; // +0x04
  z1 = this[2]; // +0x08
  w1 = this[3]; // +0x0C

  x2 = other[0]; // +0x00
  y2 = other[1]; // +0x04
  z2 = other[2]; // +0x08
  w2 = other[3]; // +0x0C

  result[0] = x1 - x2; // +0x00
  result[1] = y1 - y2; // +0x04
  result[2] = z1 - z2; // +0x08
  result[3] = w1 - w2; // +0x0C
}