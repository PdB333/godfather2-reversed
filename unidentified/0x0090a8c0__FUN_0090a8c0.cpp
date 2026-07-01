// FUNC_NAME: SomeClass::getSomeFlagOrStatus
uint __fastcall getSomeFlagOrStatus(int this)
{
  uint uVar1;
  
  uVar1 = *(uint *)(this + 8); // +0x8: some pointer or handle
  if ((uVar1 != 0) && (uVar1 = uVar1 - 0x48, uVar1 != 0)) {
    if (*(int *)(this + 8) != 0) { // +0x8: re-read pointer
      return *(uint *)(*(int *)(this + 8) + 0x14) >> 0x1d & 0xffffff01; // +0x14: flag field, extract top 3 bits, mask
    }
    return uRam0000005c >> 0x1d & 0xffffff01; // likely a global or constant
  }
  return uVar1 & 0xffffff00; // return lower bits masked
}