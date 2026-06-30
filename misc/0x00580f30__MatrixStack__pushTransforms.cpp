// FUNC_NAME: MatrixStack::pushTransforms
void MatrixStack::pushTransforms(Matrix4x4 *outMatrices, int count)
{
  int i;
  Matrix4x4 identityMatrix;
  
  FUN_00581080(); // likely clearMatrixStack or reset
  i = 0;
  if (0 < *(int *)(count + 0x1c)) { // +0x1c: some count field
    do {
      // Initialize identity matrix with DAT_00e2b1a4 (likely 0x3f800000 = 1.0f)
      identityMatrix.m[0][0] = 0;
      identityMatrix.m[0][1] = 0;
      identityMatrix.m[0][2] = 0;
      identityMatrix.m[0][3] = DAT_00e2b1a4; // 1.0f
      identityMatrix.m[1][0] = 0;
      identityMatrix.m[1][1] = 0;
      identityMatrix.m[1][2] = 0;
      identityMatrix.m[1][3] = DAT_00e2b1a4; // 1.0f
      
      FUN_00581220(&identityMatrix); // likely multiply or transform
      
      outMatrices[0] = identityMatrix;
      outMatrices[1] = identityMatrix; // copy to all slots? Actually this is wrong - need to check
      
      i = i + 1;
      outMatrices = outMatrices + 8; // advance by 8 floats = 2 matrices? Actually Matrix4x4 is 16 floats
    } while (i < *(int *)(count + 0x1c));
  }
  return;
}