// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *thisOut, float scalar)
{
  float x;
  float y;
  float z;
  float w;
  
  x = thisOut[1];  // +0x04
  y = thisOut[2];  // +0x08
  z = thisOut[3];  // +0x0C
  w = thisOut[0];  // +0x00
  *thisOut = scalar * w;
  thisOut[1] = scalar * x;
  thisOut[2] = scalar * y;
  thisOut[3] = scalar * z;
  return;
}