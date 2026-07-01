// FUNC_NAME: SomeClass::isAnimationSlotAvailable
uint __fastcall SomeClass::isAnimationSlotAvailable(int thisPtr)
{
  int iVar1;
  uint in_EAX;
  uint uVar2;

  uVar2 = in_EAX & 0xffffff00;
  if ((*(int *)(thisPtr + 4) != 0) && (*(int *)(thisPtr + 4) != 0x48)) {
    uVar2 = (*(byte *)(thisPtr + 0x12) - 1) % 0xc;
    if (*(int *)(thisPtr + 4) != 0) {
      iVar1 = *(int *)(thisPtr + 4) + -0x48;
      return CONCAT31((int3)((uint)iVar1 >> 8),*(char *)(uVar2 + 0x1e20 + iVar1) == '\0');
    }
    uVar2 = (uint)(*(char *)(uVar2 + 0x1e20) == '\0');
  }
  return uVar2;
}