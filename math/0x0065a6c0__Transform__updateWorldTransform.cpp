// FUNC_NAME: Transform::updateWorldTransform
void Transform::updateWorldTransform(int deltaX, int deltaY, int deltaZ)
{
  // Update position from base + delta
  // +0x0C: world position x, +0x1C: base position x
  *(int *)(this + 0x0C) = *(int *)(this + 0x1C) + deltaX;
  // +0x14: world position z, +0x24: base position z
  *(int *)(this + 0x14) = *(int *)(this + 0x24) + deltaZ;
  // +0x10: world position y, +0x20: base position y
  *(int *)(this + 0x10) = *(int *)(this + 0x20) + deltaY;

  // Copy local transform matrix from +0x6C (0x81 dwords = 0x204 bytes)
  // This is likely a 4x4 matrix of floats (16 floats = 64 bytes) but the size is larger,
  // possibly including extra data like scale/shear or a 3x4 matrix with padding.
  undefined4 localMatrix[0x81];
  for (int i = 0; i < 0x81; i++) {
    localMatrix[i] = *(undefined4 *)(this + 0x6C + i * 4);
  }

  // +0x18: some transform component (e.g., scale or rotation), set from +0x28
  *(undefined4 *)(this + 0x18) = *(undefined4 *)(this + 0x28);

  // Combine world position (+0x0C) with another transform (+0x5C) and the copied matrix
  // +0x5C likely holds parent or additional transform data (e.g., rotation quaternion)
  FUN_00661210(this + 0x0C, this + 0x5C, localMatrix);

  // Clear dirty flag at +0x270
  *(int *)(this + 0x270) = 0;
}