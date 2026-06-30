// FUNC_NAME: MathUtils::negateVector4
void MathUtils::negateVector4(const float *inVec, float *outVec)
{
  float v[3];
  v[0] = inVec[1]; // +0x04
  v[1] = inVec[2]; // +0x08
  v[2] = inVec[3]; // +0x0C

  outVec[0] = -inVec[0]; // negate x
  outVec[1] = -v[0];     // negate y
  outVec[2] = -v[1];     // negate z
  outVec[3] = -v[2];     // negate w (or unused component)
}