// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint local_8;
  
  if ((uint)this[2] < newCapacity) {
    iVar1 = FUN_009c8e80(newCapacity << 4); // allocate(newCapacity * sizeof(Element))
    iVar3 = 0;
    if (*this != 0) {
      local_8 = 0;
      iVar2 = iVar1;
      if (this[1] != 0) {
        do {
          piVar4 = (int *)(*this + iVar3);
          if (iVar2 != 0) {
            FUN_008f6e60(piVar4); // copy construct element at iVar2 from piVar4
            *(int *)(iVar2 + 0xc) = piVar4[3]; // copy field at +0x0C
          }
          if (*piVar4 != 0) {
            FUN_009c8f10(*piVar4); // free element's internal data
          }
          local_8 = local_8 + 1;
          iVar3 = iVar3 + 0x10;
          iVar2 = iVar2 + 0x10;
        } while (local_8 < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old buffer
    }
    *this = iVar1;
    this[2] = newCapacity;
  }
  return;
}