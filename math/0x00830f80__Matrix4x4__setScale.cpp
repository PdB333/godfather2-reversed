// FUNC_NAME: Matrix4x4::setScale
void __thiscall Matrix4x4::setScale(int this, float *scaleVec)
{
  float w;
  float y;
  float z;
  float w2;
  float originalW;

  w = scaleVec[3]; // +0x0C (w component of scale vector)
  y = scaleVec[1]; // +0x04
  z = scaleVec[2]; // +0x08
  w2 = scaleVec[3]; // +0x0C
  originalW = *(float *)(this + 0x3c); // Save original W component of matrix row 3

  // Set scale for each row (x, y, z, w) using the w component of the scale vector
  *(float *)(this + 0x30) = w * *scaleVec;   // +0x30: row 3, col 0
  *(float *)(this + 0x34) = w * y;            // +0x34: row 3, col 1
  *(float *)(this + 0x38) = w * z;            // +0x38: row 3, col 2
  *(float *)(this + 0x3c) = w * w2;           // +0x3c: row 3, col 3

  // Restore original W component (preserve translation/homogeneous coordinate)
  *(float *)(this + 0x3c) = originalW;
  return;
}