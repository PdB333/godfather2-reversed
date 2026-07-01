// FUNC_NAME: SomeContainer::resize
void __thiscall SomeContainer::resize(int *this, uint newCapacity)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint local_8;
  
  if ((uint)this[2] < newCapacity) {
    iVar1 = FUN_009c8e80(newCapacity * 0x4c); // allocate memory for newCapacity elements (each 0x4c bytes)
    iVar3 = 0;
    if (*this != 0) {
      local_8 = 0;
      iVar2 = iVar1;
      if (this[1] != 0) {
        do {
          piVar4 = (int *)(*this + iVar3);
          if (iVar2 != 0) {
            FUN_0098df80(piVar4); // copy/move element at source to destination
          }
          if (piVar4[0xc] != 0) {
            (*(code *)piVar4[0xf])(piVar4[0xc]); // call destructor on element field at +0x30
          }
          if (piVar4[8] != 0) {
            (*(code *)piVar4[0xb])(piVar4[8]); // call destructor on element field at +0x20
          }
          if (piVar4[4] != 0) {
            (*(code *)piVar4[7])(piVar4[4]); // call destructor on element field at +0x10
          }
          if (*piVar4 != 0) {
            (*(code *)piVar4[3])(*piVar4); // call destructor on element field at +0x00
          }
          local_8 = local_8 + 1;
          iVar3 = iVar3 + 0x4c;
          iVar2 = iVar2 + 0x4c;
        } while (local_8 < (uint)this[1]);
      }
      FUN_009c8f10(*this); // free old memory
    }
    *this = iVar1;
    this[2] = newCapacity;
  }
  return;
}