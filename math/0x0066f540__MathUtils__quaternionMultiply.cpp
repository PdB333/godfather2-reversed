// FUNC_NAME: MathUtils::quaternionMultiply
void __thiscall MathUtils::quaternionMultiply(float *outResult, float *inQuatA, float *inQuatB)
{
  float wA, xA, yA, zA;
  float wB, xB, yB, zB;

  xA = inQuatA[0]; // +0x00
  yA = inQuatA[1]; // +0x04
  zA = inQuatA[2]; // +0x08
  wA = inQuatA[3]; // +0x0C

  xB = inQuatB[0]; // +0x00
  yB = inQuatB[1]; // +0x04
  zB = inQuatB[2]; // +0x08
  wB = inQuatB[3]; // +0x0C

  // Quaternion multiplication: qA * qB
  outResult[0] = wA * xB + yA * zB - zA * yB;   // x component
  outResult[1] = wA * yB + zA * xB - xA * zB;   // y component
  outResult[2] = wA * zB + xA * yB - yA * xB;   // z component
  outResult[3] = wA * wB - xA * xB - yA * yB - zA * zB; // w component
  return;
}