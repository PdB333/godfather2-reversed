// FUNC_NAME: LinearMath::Vector4ScaleMultiply
void __thiscall Vector4ScaleMultiply(float *thisVec, float *scaleVec, float *outputVec)
{
  float x1, y1, z1, w1;
  float x2, y2, z2, w2;

  // Store input values to avoid overwriting issues if output overwrites input
  x1 = thisVec[0]; // +0x00: x component
  y1 = thisVec[1]; // +0x04: y component
  z1 = thisVec[2]; // +0x08: z component
  w1 = thisVec[3]; // +0x0C: w component

  x2 = scaleVec[0]; // +0x00: x scale
  y2 = scaleVec[1]; // +0x04: y scale
  z2 = scaleVec[2]; // +0x08: z scale
  w2 = scaleVec[3]; // +0x0C: w scale

  // Perform element-wise (Hadamard) multiplication
  outputVec[0] = x1 * x2; // output x = this.x * scale.x
  outputVec[1] = y1 * y2; // output y = this.y * scale.y
  outputVec[2] = z1 * z2; // output z = this.z * scale.z
  outputVec[3] = w1 * w2; // output w = this.w * scale.w

  return;
}