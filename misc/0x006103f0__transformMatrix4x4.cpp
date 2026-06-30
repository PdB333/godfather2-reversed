// FUNC_NAME: transformMatrix4x4
void FUN_006103f0(float* result, float* matrix, float* translation)
{
  float temp[12];
  float local_50[8];
  float local_90[8];

  // Copy first 8 floats from matrix (2 rows of 4)
  temp[0] = matrix[0];
  temp[1] = matrix[1];
  temp[2] = matrix[2];
  temp[3] = matrix[3];
  temp[4] = matrix[4];
  temp[5] = matrix[5];
  temp[6] = matrix[6];
  temp[7] = matrix[7];

  // Setup two sets of 4 floats for rotation basis
  local_50[0] = matrix[0];
  local_50[1] = matrix[4];
  local_50[2] = matrix[2];
  local_50[3] = matrix[6];

  // If translation vector is provided, copy it
  if (translation != (float *)0x0) {
    local_50[0] = translation[0];
    local_50[1] = translation[1];
    local_50[2] = translation[2];
    local_50[3] = translation[3];
    local_50[4] = translation[4];
    local_50[5] = translation[5];
    local_50[6] = translation[6];
    local_50[7] = translation[7];

    // Setup second set of 4 for final transform
    local_90[0] = translation[0];
    local_90[1] = translation[4];
    local_90[2] = translation[2];
    local_90[3] = translation[6];

    // Perform final matrix multiplication with translation
    FUN_00610690(temp, &local_50[0], &local_90[0]);
    return;
  }

  // No translation, just perform matrix multiplication
  FUN_00610690(temp, &local_50[0], 0);
  return;
}