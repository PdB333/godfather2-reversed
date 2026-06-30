// FUNC_NAME: GrowableArray::reserve
void GrowableArray::reserve(uint newCapacity)
{
  int iVar1;
  undefined4 *newData;
  uint uVar3;
  undefined4 *puVar4;
  int *this; // unaff_ESI
  
  if ((uint)this[2] < newCapacity) {
    newData = (undefined4 *)FUN_009c8e80(newCapacity * 8);
    if (*this != 0) {
      uVar3 = 0;
      puVar4 = newData;
      if (this[1] != 0) {
        do {
          if (puVar4 != (undefined4 *)0x0) {
            iVar1 = *this;
            *puVar4 = *(undefined4 *)(iVar1 + uVar3 * 8);
            puVar4[1] = *(undefined4 *)(iVar1 + 4 + uVar3 * 8);
          }
          uVar3 = uVar3 + 1;
          puVar4 = puVar4 + 2;
        } while (uVar3 < (uint)this[1]);
      }
      FUN_009c8f10(*this);
    }
    *this = (int)newData;
    this[2] = newCapacity;
  }
  return;
}