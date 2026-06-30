// FUNC_NAME: __thiscall vectorSubtract(float*, float*)
void __thiscall vectorSubtract(float *this, float *other, float *result)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;
  
  x1 = this[0];
  y1 = this[1];
  z1 = this[2];
  w1 = this[3];
  
  x2 = other[0];
  y2 = other[1];
  z2 = other[2];
  w2 = other[3];
  
  result[0] = x1 - x2;
  result[1] = y1 - y2;
  result[2] = z1 - z2;
  result[3] = w1 - w2;
}