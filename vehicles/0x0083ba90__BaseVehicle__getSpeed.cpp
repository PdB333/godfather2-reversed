// FUNC_NAME: BaseVehicle::getSpeed
float __thiscall BaseVehicle::getSpeed(int this, float *outVelocity)
{
  float *pDefaultVel;
  float x, y, z;
  float speed;

  pDefaultVel = (float *)FUN_00424fb0(&x, 0); // get default velocity vector (maybe from animation?)
  outVelocity[0] = pDefaultVel[0];
  outVelocity[1] = pDefaultVel[1];
  outVelocity[2] = pDefaultVel[2];
  speed = 0.0f;
  // Check if bit 0x13 (19) of flags at +0xa8 is set, or global debug flag is active
  if (((*(uint *)(this + 0xa8) >> 0x13 & 1) != 0) || (DAT_0112dc40 != '\0')) {
    FUN_0083b990(&x); // update velocity from physics simulation
    speed = SQRT(z * z + x * x + y * y) * _DAT_00e53f34; // magnitude scaled by global factor
  }
  return speed;
}