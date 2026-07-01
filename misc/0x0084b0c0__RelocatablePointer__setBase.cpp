// FUNC_NAME: RelocatablePointer::setBase
void __thiscall RelocatablePointer::setBase(int *this, int baseAddress)
{
  int iVar1;
  
  *this = baseAddress;
  if (*(int *)(baseAddress + 0x20) != 0) {
    *(int *)(baseAddress + 0x20) = *(int *)(baseAddress + 0x20) + baseAddress;
  }
  iVar1 = *(int *)(*this + 0x24);
  if (iVar1 != 0) {
    *(int *)(*this + 0x24) = iVar1 + baseAddress;
  }
  iVar1 = *(int *)(*this + 0x28);
  if (iVar1 != 0) {
    *(int *)(*this + 0x28) = iVar1 + baseAddress;
  }
  iVar1 = *(int *)(*this + 0x2c);
  if (iVar1 != 0) {
    *(int *)(*this + 0x2c) = iVar1 + baseAddress;
  }
  iVar1 = *(int *)(*this + 0x30);
  if (iVar1 != 0) {
    *(int *)(*this + 0x30) = iVar1 + baseAddress;
  }
  return;
}