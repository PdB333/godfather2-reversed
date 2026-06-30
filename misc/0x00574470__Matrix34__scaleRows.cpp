// FUNC_NAME: Matrix34::scaleRows
void __thiscall Matrix34::scaleRows(const float* scaleVec)
{
  float s0 = scaleVec[0];
  float s1 = scaleVec[1];
  float s2 = scaleVec[2];

  float r0c0 = m[0];
  float r0c1 = m[1];
  float r0c2 = m[2];
  float r0c3 = m[3];
  m[0] = s0 * r0c0;
  m[1] = s0 * r0c1;
  m[2] = s0 * r0c2;
  m[3] = s0 * r0c3;

  float r1c0 = m[4];
  float r1c1 = m[5];
  float r1c2 = m[6];
  float r1c3 = m[7];
  m[4] = s1 * r1c0;
  m[5] = s1 * r1c1;
  m[6] = s1 * r1c2;
  m[7] = s1 * r1c3;

  float r2c0 = m[8];
  float r2c1 = m[9];
  float r2c2 = m[10];
  float r2c3 = m[11];
  m[8] = s2 * r2c0;
  m[9] = s2 * r2c1;
  m[10] = s2 * r2c2;
  m[11] = s2 * r2c3;
}