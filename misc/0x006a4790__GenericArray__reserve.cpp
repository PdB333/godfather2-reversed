// FUNC_NAME: GenericArray::reserve
void __thiscall GenericArray::reserve(int *this, uint newCapacity)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_8;
  
  if ((uint)this[2] < newCapacity) {
    iVar2 = FUN_009c8e80(newCapacity * 0x30); // operator new[] (size = elementSize * count)
    iVar4 = 0;
    if (*this != 0) {
      local_8 = 0;
      iVar3 = iVar2;
      if (this[1] != 0) {
        do {
          iVar1 = *this; // old array pointer
          if (iVar3 != 0) {
            FUN_006a46f0(iVar1 + iVar4); // copy constructor / placement new for element at index
          }
          local_8 = local_8 + 1;
          *(undefined ***)(iVar1 + iVar4 + 0x24) = &PTR_LAB_00e2f0c0; // set vtable pointer at +0x24
          iVar4 = iVar4 + 0x30; // advance by element size (0x30 = 48 bytes)
          iVar3 = iVar3 + 0x30;
        } while (local_8 < (uint)this[1]); // copy all existing elements
      }
      FUN_009c8f10(*this); // operator delete[] (old array)
    }
    *this = iVar2; // new array pointer
    this[2] = newCapacity; // update capacity
  }
  return;
}