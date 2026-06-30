// FUNC_NAME: Vector4::componentMultiply
void __thiscall Vector4::componentMultiply(float *this, float *other, float *result)
{
  // Perform component-wise multiplication of two 4D vectors
  // this[0..3] * other[0..3] -> result[0..3]
  float x = this[0];   // +0x00
  float y = this[1];   // +0x04
  float z = this[2];   // +0x08
  float w = this[3];   // +0x0C

  float otherX = other[0]; // +0x00
  float otherY = other[1]; // +0x04
  float otherZ = other[2]; // +0x08
  float otherW = other[3]; // +0x0C

  result[0] = x * otherX;
  result[1] = y * otherY;
  result[2] = z * otherZ;
  result[3] = w * otherW;
  return;
}