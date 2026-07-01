// FUNC_NAME: Matrix44::transformPoints
void __thiscall Matrix44::transformPoints(float *this, float *outPoints)
{
  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;
  int count;
  float *inPoints;
  float x, y, z, w;
  float tx, ty, tz, tw;

  // Load matrix columns from this pointer (ESI)
  m00 = this[0];   // +0x00
  m01 = this[1];   // +0x04
  m02 = this[2];   // +0x08
  m03 = this[3];   // +0x0C
  m10 = this[4];   // +0x10
  m11 = this[5];   // +0x14
  m12 = this[6];   // +0x18
  m13 = this[7];   // +0x1C
  m20 = this[8];   // +0x20
  m21 = this[9];   // +0x24
  m22 = this[10];  // +0x28
  m23 = this[11];  // +0x2C
  m30 = this[12];  // +0x30
  m31 = this[13];  // +0x34
  m32 = this[14];  // +0x38
  m33 = this[15];  // +0x3C

  // in_EAX holds the number of points to transform
  count = in_EAX;
  inPoints = param_1; // param_1 is the input point array

  if (count > 0) {
    do {
      // Load input point (4 floats: x, y, z, w)
      x = inPoints[0];
      y = inPoints[1];
      z = inPoints[2];
      w = inPoints[3];

      // Transform by matrix multiplication (row-major: out = M * in)
      outPoints[0] = x * m00 + y * m10 + z * m20 + w * m30;
      outPoints[1] = x * m01 + y * m11 + z * m21 + w * m31;
      outPoints[2] = x * m02 + y * m12 + z * m22 + w * m32;
      outPoints[3] = x * m03 + y * m13 + z * m23 + w * m33;

      count--;
      inPoints += 4;
      outPoints += 4;
    } while (count > 0);
  }
}