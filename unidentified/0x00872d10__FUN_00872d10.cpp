// FUNC_NAME: UnknownClass::isSomethingActive
uint __fastcall UnknownClass::isSomethingActive(int thisPtr)
{
  uint result;
  int iVar1;
  uint in_EAX;
  
  result = in_EAX & 0xffffff00;
  if ((*(int *)(thisPtr + 100) != 0) && (*(int *)(thisPtr + 100) != 0x48)) {
    iVar1 = *(int *)(thisPtr + 100);
    if (iVar1 != 0) {
      // Check flags at offset 0xD4 of the sub-object
      return CONCAT31((int3)((uint)(iVar1 + -0x48) >> 8),(*(uint *)(iVar1 + 0xd4) & 0x71) != 0);
    }
    result = (uint)((uRam0000011c & 0x71) != 0);
  }
  return result;
}