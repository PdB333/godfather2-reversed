// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(float *this, float t, float *result)
{
  float vx = this[0];
  float vy = this[1];
  float vz = this[2];
  float vw = this[3];
  float ux = param_1[0]; // +0x00
  float uy = param_1[1]; // +0x04
  float uz = param_1[2]; // +0x08
  float uw = param_1[3]; // +0x0C

  result[0] = t * vx + ux;
  result[1] = t * vy + uy;
  result[2] = t * vz + uz;
  result[3] = t * vw + uw;
}