// FUNC_NAME: MathUtils::lerpVector4
void __thiscall lerpVector4(float *a, float t, float *b, float *out)
{
  float a1 = a[1]; // a->y, +0x04
  float a2 = a[2]; // a->z, +0x08
  float a3 = a[3]; // a->w, +0x0C
  float b0 = b[0]; // b->x, +0x00
  float b1 = b[1]; // b->y, +0x04
  float b2 = b[2]; // b->z, +0x08
  float b3 = b[3]; // b->w, +0x0C

  out[0] = t * a[0] + b0; // Linear interpolation: out = t * a + b (note: using b as base, not (1-t)*b + t*a)
  out[1] = t * a1 + b1;
  out[2] = t * a2 + b2;
  out[3] = t * a3 + b3;
}