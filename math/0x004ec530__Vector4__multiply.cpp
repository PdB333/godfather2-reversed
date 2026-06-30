// FUNC_NAME: Vector4::multiply
void __thiscall Vector4::multiply(float *this, float *other, float *out)
{
  // Component-wise multiplication of two 4-element vectors (float3? no, 4 components)
  // this->x * other->x, this->y * other->y, etc.
  // Struct offsets: +0x00=x, +0x04=y, +0x08=z, +0x0C=w
  float tx = this[0];
  float ty = this[1];
  float tz = this[2];
  float tw = this[3];
  float ox = other[0];
  float oy = other[1];
  float oz = other[2];
  float ow = other[3];
  out[0] = tx * ox;
  out[1] = ty * oy;
  out[2] = tz * oz;
  out[3] = tw * ow;
}