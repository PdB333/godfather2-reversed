// FUNC_NAME: Matrix4x4::scaleByFactor
void Matrix4x4::scaleByFactor(void)
{
  float *matrix = in_EAX; // this pointer to 4x4 matrix (16 floats)
  float scaleFactor = DAT_00e2b1a4 / matrix[0x18]; // global scale / matrix[24] (element [6][0] or scale factor)
  
  // Scale all 8 elements of the matrix (first two rows of 4x4)
  matrix[0] = scaleFactor * matrix[0];  // +0x00
  matrix[1] = scaleFactor * matrix[1];  // +0x04
  matrix[2] = scaleFactor * matrix[2];  // +0x08
  matrix[3] = scaleFactor * matrix[3];  // +0x0C
  matrix[4] = scaleFactor * matrix[4];  // +0x10
  matrix[5] = scaleFactor * matrix[5];  // +0x14
  matrix[6] = scaleFactor * matrix[6];  // +0x18
  matrix[7] = scaleFactor * matrix[7];  // +0x1C
  return;
}