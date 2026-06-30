// FUNC_NAME: EA::Math::scaleVectorByFactor
void EA::Math::scaleVectorByFactor(float *vector)
{
  float scale = DAT_00e2b1a4 / vector[8]; // +0x20: some constant factor? Possibly field of view or aspect ratio?
  // Scale first 6 components (e.g., position + orientation)
  vector[0] = scale * vector[0];
  vector[1] = scale * vector[1];
  vector[2] = scale * vector[2];
  vector[3] = scale * vector[3];
  vector[4] = scale * vector[4];
  vector[5] = scale * vector[5];
  // Note: vector might be a 6-element homogeneous transform (position + direction) scaled by some global factor
}