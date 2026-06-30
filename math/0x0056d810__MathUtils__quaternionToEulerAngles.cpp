// FUNC_NAME: MathUtils::quaternionToEulerAngles
void MathUtils::quaternionToEulerAngles(float *inQuat, float *outRoll, float *outPitch, float *outYaw)
{
  float qx, qy, qz, qw;
  float sinp, cosp;
  double dVar6;
  float fVar7;

  qx = inQuat[2]; // +0x08
  qy = *inQuat;   // +0x00
  qz = inQuat[1]; // +0x04
  qw = inQuat[3]; // +0x0C

  dVar6 = (double)((qw * qz + qx * qy) * DAT_00e2b04c); // 2.0f
  FUN_00b9a9fa(); // sinf
  fVar7 = DAT_00e2eff4; // -1.0f
  *outRoll = (float)dVar6;

  sinp = (qz * qx - qw * qy) * DAT_00e2b04c; // 2.0f
  if ((sinp <= fVar7) || (fVar7 = DAT_00e2b1a4, DAT_00e2b1a4 <= sinp)) { // clamp to [-1, 1]
    sinp = fVar7;
  }
  dVar6 = (double)sinp;
  FUN_00b9c766(); // asinf
  fVar7 = DAT_00e2b04c; // 2.0f
  *outPitch = DAT_00e44564 - (float)dVar6; // PI/2 - asin(sinp)

  dVar6 = (double)((qw * qx + qz * qy) * fVar7);
  FUN_00b9a9fa(); // sinf
  *outYaw = (float)dVar6;

  return;
}