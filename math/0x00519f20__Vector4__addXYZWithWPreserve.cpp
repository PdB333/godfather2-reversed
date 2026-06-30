// FUNC_NAME: Vector4::addXYZWithWPreserve
void __fastcall Vector4::addXYZWithWPreserve(float *thisOut, float *a, float *b)
{
  float ax = a[1];
  float ay = a[2];
  float az = a[3];
  float bx = b[1];
  float by = b[2];
  float bz = b[3];
  float w = thisOut[3]; // preserve original W component

  thisOut[0] = a[0] + b[0];
  thisOut[1] = ax + bx;
  thisOut[2] = ay + by;
  thisOut[3] = az + bz;
  thisOut[3] = w; // restore original W
}