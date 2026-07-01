// FUNC_NAME: ChaseCamera::setTargetOffset
void __thiscall ChaseCamera::setTargetOffset(int thisPtr, undefined4 *targetOffset)
{
  undefined4 x;
  undefined4 y;
  undefined4 z;
  
  x = targetOffset[1];
  y = targetOffset[2];
  z = targetOffset[3];
  *(undefined4 *)(thisPtr + 0xd0) = *targetOffset;
  *(undefined4 *)(thisPtr + 0xd4) = x;
  *(undefined4 *)(thisPtr + 0xd8) = y;
  *(undefined4 *)(thisPtr + 0xdc) = z;
  return;
}