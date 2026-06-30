// FUNC_NAME: Matrix44::scaleRows
void __thiscall Matrix44::scaleRows(float *this, float *scaleVec)
{
  float sx = scaleVec[0]; // scale X
  float sy = scaleVec[1]; // scale Y
  float sz = scaleVec[2]; // scale Z

  // Row 0: scale by sx
  float r0c0 = this[0];
  float r0c1 = this[1];
  float r0c2 = this[2];
  float r0c3 = this[3];
  this[0] = sx * r0c0;
  this[1] = sx * r0c1;
  this[2] = sx * r0c2;
  this[3] = sx * r0c3;

  // Row 1: scale by sy
  float r1c0 = this[4];
  float r1c1 = this[5];
  float r1c2 = this[6];
  float r1c3 = this[7];
  this[4] = sy * r1c0;
  this[5] = sy * r1c1;
  this[6] = sy * r1c2;
  this[7] = sy * r1c3;

  // Row 2: scale by sz
  float r2c0 = this[8];
  float r2c1 = this[9];
  float r2c2 = this[10];
  float r2c3 = this[11];
  this[8] = sz * r2c0;
  this[9] = sz * r2c1;
  this[10] = sz * r2c2;
  this[11] = sz * r2c3;
}