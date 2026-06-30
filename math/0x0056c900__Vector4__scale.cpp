// FUNC_NAME: Vector4::scale
void __thiscall Vector4::scale(float *out, float scalar)
{
  float v0 = this[0]; // X
  float v1 = this[1]; // Y
  float v2 = this[2]; // Z
  float v3 = this[3]; // W

  out[0] = scalar * v0;
  out[1] = scalar * v1;
  out[2] = scalar * v2;
  out[3] = scalar * v3;
}