// FUNC_NAME: Vector4::lerp
void __thiscall Vector4::lerp(float *this, float t, float *outResult)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;

  x1 = this[0];
  y1 = this[1];
  z1 = this[2];
  w1 = this[3];

  x2 = param_1[0]; // second vector (param_1)
  y2 = param_1[1];
  z2 = param_1[2];
  w2 = param_1[3];

  // Linear interpolation: result = this + t * (param_1 - this)
  // But implementation is: result = this * t + param_1 ? No, actually: out = this + t * param_1 (scaled addition)
  // Wait, recalculating: result = param_2 * this + param_1
  // That's not standard lerp. It's: out = param_1 + t * this
  // This is essentially adding a scaled version of 'this' to param_1.
  // It's likely a vector addition with scaling: out = a + t * b, where a=param_1, b=this.
  // Given the function name "lerp", it's probably dest = src + t * dir (or similar)
  outResult[0] = x2 + t * x1;
  outResult[1] = y2 + t * y1;
  outResult[2] = z2 + t * z1;
  outResult[3] = w2 + t * w1;
}