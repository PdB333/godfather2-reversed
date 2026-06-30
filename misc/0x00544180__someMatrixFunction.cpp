// FUNC_NAME: someMatrixFunction
void someMatrixFunction(void *thisPtr, float *outMatrix)
{
  float local_50[12]; // 3x4 matrix stored as 12 floats
  undefined local_4c; // unused padding
  undefined local_48;
  undefined local_40;
  undefined local_3c;
  undefined local_38;
  undefined local_30;
  undefined local_2c;
  undefined local_28;
  undefined local_20;
  undefined local_1c;
  undefined local_18;

  FUN_00aa1a10(local_50); // likely builds a 3x4 transformation matrix from 'this'
  
  // Copy the 12 floats of the 3x4 matrix to output
  // Note: param_2[3] and param_2[7] are skipped (indices 3 and 7),
  // suggesting this is a 4x4 matrix with last row [0,0,0,1] or similar
  outMatrix[0] = local_50[0];
  outMatrix[1] = local_50[1];
  outMatrix[2] = local_50[2];
  outMatrix[4] = local_50[4];
  outMatrix[5] = local_50[5];
  outMatrix[6] = local_50[6];
  outMatrix[8] = local_50[8];
  outMatrix[9] = local_50[9];
  outMatrix[10] = local_50[10];
  outMatrix[12] = local_50[12]; // note: local_50[12] may be out of bounds? enum uses local_20 offset
  outMatrix[13] = local_50[13];
  outMatrix[14] = local_50[14];
}