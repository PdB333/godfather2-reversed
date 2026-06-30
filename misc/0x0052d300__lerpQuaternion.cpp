// FUNC_NAME: lerpQuaternion
void __thiscall lerpQuaternion(float *from, float t, float *to, float *result)
{
  float fromX = from[1]; // +0x04
  float fromY = from[2]; // +0x08
  float fromZ = from[3]; // +0x0C
  float toX = to[1];     // +0x04
  float toY = to[2];     // +0x08
  float toZ = to[3];     // +0x0C

  // Linear interpolation of quaternion components (w, x, y, z)
  result[0] = (to[0] - from[0]) * t + from[0]; // w component
  result[1] = (toX - fromX) * t + fromX;       // x component
  result[2] = (toY - fromY) * t + fromY;       // y component
  result[3] = (toZ - fromZ) * t + fromZ;       // z component
}