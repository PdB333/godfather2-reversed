// FUNC_NAME: DynamicArray::pushBack
int __fastcall DynamicArray::pushBack(int *this)
{
  longlong newCapacity;
  uint uVar2;
  int iVar3;
  
  if ((uint)this[1] <= this[2] + 1U) {
    uVar2 = this[1] + 10;
    this[1] = uVar2;
    newCapacity = (ulonglong)uVar2 * 4;
    iVar3 = FUN_009c8e80(-(uint)((int)((ulonglong)newCapacity >> 0x20) != 0) | (uint)newCapacity);
    if (*this != 0) {
      uVar2 = 0;
      if (this[2] != 0) {
        do {
          *(undefined4 *)(iVar3 + uVar2 * 4) = *(undefined4 *)(*this + uVar2 * 4);
          uVar2 = uVar2 + 1;
        } while (uVar2 < (uint)this[2]);
      }
      FUN_009c8f10(*this);
    }
    *this = iVar3;
  }
  iVar3 = this[2];
  this[2] = iVar3 + 1;
  return *this + iVar3 * 4;
}