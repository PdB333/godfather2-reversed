// FUNC_NAME: rotateVector3
void rotateVector3(float *outVec, float *inVec, float *matrix44)
{
  float vx = inVec[0];
  float vy = inVec[1];
  float vz = inVec[2];

  // matrix44 is a 4x4 column-major? Actually indices as used: [0,1,2] = row0; [4,5,6] = row1; [8,9,10] = row2.
  outVec[0] = vy * matrix44[4] + vx * matrix44[0] + vz * matrix44[8];
  outVec[1] = vy * matrix44[5] + vx * matrix44[1] + vz * matrix44[9];
  outVec[2] = vy * matrix44[6] + vx * matrix44[2] + vz * matrix44[10];
}