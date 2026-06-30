// FUNC_NAME: Quaternion::slerp
void __thiscall Quaternion::slerp(int this, int targetQuat, float t, int outQuat)
{
  float *sourceQuat;
  float *targetQuatData;
  float *outQuatData;
  float qx1, qy1, qz1, qw1;
  float qx2, qy2, qz2, qw2;

  // Get source quaternion components from this object (+0x08 offset for quaternion data)
  sourceQuat = *(float **)(this + 8);
  qx1 = sourceQuat[1]; // +0x0C
  qy1 = sourceQuat[2]; // +0x10
  qz1 = sourceQuat[3]; // +0x14
  qw1 = sourceQuat[0]; // +0x08

  // Get target quaternion components
  targetQuatData = *(float **)(targetQuat + 8);
  qx2 = targetQuatData[1]; // +0x0C
  qy2 = targetQuatData[2]; // +0x10
  qz2 = targetQuatData[3]; // +0x14
  qw2 = targetQuatData[0]; // +0x08

  // Perform spherical linear interpolation (slerp)
  outQuatData = *(float **)(outQuat + 8);
  *outQuatData = (qw2 - qw1) * t + qw1;           // Interpolate w
  outQuatData[1] = (qx2 - qx1) * t + qx1;         // Interpolate x
  outQuatData[2] = (qy2 - qy1) * t + qy1;         // Interpolate y
  outQuatData[3] = (qz2 - qz1) * t + qz1;         // Interpolate z
}