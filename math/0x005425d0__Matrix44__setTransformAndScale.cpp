// FUNC_NAME: Matrix44::setTransformAndScale
void __thiscall Matrix44::setTransformAndScale(undefined4 *thisMatrix, undefined4 *rotationMatrix, undefined4 *scaleMatrix, undefined4 transX, undefined4 transY, undefined4 transZ, undefined4 transW)
{
  *(undefined1 *)(thisMatrix + 8) = 0; // +0x20: set identity flag to false
  thisMatrix[9] = 0; // +0x24: clear scale flag
  thisMatrix[0xd] = transX; // +0x34: translation X
  thisMatrix[0xe] = transY; // +0x38: translation Y
  thisMatrix[0xf] = transZ; // +0x3c: translation Z
  thisMatrix[0x10] = transW; // +0x40: translation W
  thisMatrix[0xc] = 0x3e0; // +0x30: set some flag (0x3e0 = 992)
  *thisMatrix = *rotationMatrix; // +0x00: copy rotation row0
  thisMatrix[1] = rotationMatrix[1]; // +0x04: copy rotation row1
  thisMatrix[2] = rotationMatrix[2]; // +0x08: copy rotation row2
  thisMatrix[3] = rotationMatrix[3]; // +0x0c: copy rotation row3
  thisMatrix[4] = *scaleMatrix; // +0x10: copy scale row0
  thisMatrix[5] = scaleMatrix[1]; // +0x14: copy scale row1
  thisMatrix[6] = scaleMatrix[2]; // +0x18: copy scale row2
  thisMatrix[7] = scaleMatrix[3]; // +0x1c: copy scale row3
  *(undefined1 *)(thisMatrix + 8) = 1; // +0x20: set identity flag to true
  thisMatrix[9] = (uint)(thisMatrix + 0xc) >> 2 | 0x40000000; // +0x24: store packed flag
  return;
}