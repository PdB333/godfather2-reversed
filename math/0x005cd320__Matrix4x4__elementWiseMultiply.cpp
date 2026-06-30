// FUNC_NAME: Matrix4x4::elementWiseMultiply
void __thiscall Matrix4x4::elementWiseMultiply(float *thisMatrix, float *otherMatrix, float *outMatrix)
{
  float m00;
  float m10;
  float m20;
  float m30;
  float n00;
  float n10;
  float n20;
  float n30;

  // Load this matrix elements (in_EAX = this, param_1 = other, param_2 = out)
  // Note: param_1 is actually the second matrix, param_2 is the output
  m00 = thisMatrix[0];
  m10 = thisMatrix[1];  // +0x4
  m20 = thisMatrix[2];  // +0x8
  m30 = thisMatrix[3];  // +0xC

  n00 = otherMatrix[0];
  n10 = otherMatrix[1];  // +0x4
  n20 = otherMatrix[2];  // +0x8
  n30 = otherMatrix[3];  // +0xC

  // Element-wise (Hadamard) multiplication of two 4x4 matrices
  // Only first row is shown; full 16 elements should be multiplied
  outMatrix[0] = m00 * n00;    // +0x0
  outMatrix[1] = m10 * n10;    // +0x4
  outMatrix[2] = m20 * n20;    // +0x8
  outMatrix[3] = m30 * n30;    // +0xC

  return;
}