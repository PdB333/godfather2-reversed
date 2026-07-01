// FUNC_NAME: Entity::getTransformMatrix
void __thiscall Entity::getTransformMatrix(int this, float *outMatrix)
{
  // Copy 4x4 transform matrix from entity data
  // +0x20 to +0x2C: first 4 floats (row 0 of 4x4 matrix)
  outMatrix[0] = *(float *)(this + 0x20);
  outMatrix[1] = *(float *)(this + 0x24);
  outMatrix[2] = *(float *)(this + 0x28);
  outMatrix[3] = *(float *)(this + 0x2C);
  // +0x8C: 5th float (likely row 1, column 0 or translation component)
  outMatrix[4] = *(float *)(this + 0x8C);
  return;
}