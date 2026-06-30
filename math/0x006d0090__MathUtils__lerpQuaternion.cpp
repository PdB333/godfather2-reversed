// FUNC_NAME: MathUtils::lerpQuaternion
void __thiscall MathUtils::lerpQuaternion(float *quatA, float t, float *quatB, float *result)
{
  float qAx, qAy, qAz, qAw;
  float qBx, qBy, qBz, qBw;

  // Extract quaternion A components
  qAx = quatA[0]; // +0x00
  qAy = quatA[1]; // +0x04
  qAz = quatA[2]; // +0x08
  qAw = quatA[3]; // +0x0C

  // Extract quaternion B components
  qBx = quatB[0]; // +0x00
  qBy = quatB[1]; // +0x04
  qBz = quatB[2]; // +0x08
  qBw = quatB[3]; // +0x0C

  // Perform spherical linear interpolation (lerp) between two quaternions
  result[0] = t * qAx + qBx; // +0x00
  result[1] = t * qAy + qBy; // +0x04
  result[2] = t * qAz + qBz; // +0x08
  result[3] = t * qAw + qBw; // +0x0C
}