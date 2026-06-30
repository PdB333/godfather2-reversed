// FUNC_NAME: Matrix44::transformPoints
void __thiscall Matrix44::transformPoints(float *self, float *src, float *dst, int count)
{
  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;

  // Load matrix elements from (presumably) unaff_ESI register-passed pointer
  // Memory layout: row-major 4x4 matrix
  // this is passed in ESI
  m00 = self[0];  // +0x00
  m01 = self[1];  // +0x04
  m02 = self[2];  // +0x08
  m03 = self[3];  // +0x0C
  m10 = self[4];  // +0x10
  m11 = self[5];  // +0x14
  m12 = self[6];  // +0x18
  m13 = self[7];  // +0x1C
  m20 = self[8];  // +0x20
  m21 = self[9];  // +0x24
  m22 = self[10]; // +0x28
  m23 = self[11]; // +0x2C
  m30 = self[12]; // +0x30
  m31 = self[13]; // +0x34
  m32 = self[14]; // +0x38
  m33 = self[15]; // +0x3C

  // Transform each point as a 4-component vector (position or direction)
  // count is passed in EAX, loaded into in_EAX
  while (count > 0) {
    float x = src[0];
    float y = src[1];
    float z = src[2];
    float w = src[3];  // typical homogeneous coordinate

    // Standard 4x4 matrix-vector multiplication
    dst[0] = x * m00 + y * m10 + z * m20 + w * m30;  // output x
    dst[1] = x * m01 + y * m11 + z * m21 + w * m31;  // output y
    dst[2] = x * m02 + y * m12 + z * m22 + w * m32;  // output z
    dst[3] = x * m03 + y * m13 + z * m23 + w * m33;  // output w

    src += 4;  // advance to next source point (4 floats per point)
    dst += 4;  // advance to next destination slot
    count--;
  }
}