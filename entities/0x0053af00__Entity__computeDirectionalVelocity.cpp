//FUNC_NAME: Entity::computeDirectionalVelocity
undefined4 __thiscall Entity::computeDirectionalVelocity(int this, float *outVelocity, float angle, float *scaleFactors)
{
  float speedScale = *(float *)(this + 0x34); // +0x34: speed multiplier (e.g., m_speed)
  float radAngle = angle * DAT_00e2a848; // DAT_00e2a848: degrees-to-radians conversion factor
  double dAngle = (double)radAngle;

  // Compute cosine of angle (likely FUN_00b99fcb is cos)
  double cosAngle = FUN_00b99fcb(dAngle);
  outVelocity[0] = (float)(cosAngle * scaleFactors[0] * speedScale);
  outVelocity[1] = 0.0f; // Y component is zero (planar movement)

  // Compute sine of angle (likely FUN_00b99e20 is sin)
  double sinAngle = FUN_00b99e20(dAngle);
  outVelocity[2] = (float)(sinAngle * scaleFactors[2] * speedScale);

  FUN_00414aa0(); // Debug/logging call (likely unused in release)
  return 1;
}