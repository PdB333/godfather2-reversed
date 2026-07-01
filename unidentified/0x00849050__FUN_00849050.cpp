// FUNC_NAME: SomeClass::getSomeRectOrBounds
void __thiscall getSomeRectOrBounds(int thisPtr, undefined4 *outRect)
{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(thisPtr + 0xb4);
  *outRect = *(undefined4 *)(thisPtr + 0xb0);
  outRect[2] = uVar1;
  uVar1 = _DAT_00d5780c; // global constant, likely screen height or some max value
  outRect[1] = 0;
  outRect[3] = uVar1;
  return;
}