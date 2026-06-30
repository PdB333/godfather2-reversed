// FUNC_NAME: BitArray::init
void __thiscall BitArray::init(int *this, uint numBits, int initialValue)
{
  longlong lVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  this[3] = initialValue;
  this[1] = 0;
  this[2] = numBits;
  this[4] = 0;
  iVar2 = FUN_009c8e50(0xc); // allocate 12 bytes for BitArray internal
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    lVar1 = (ulonglong)(numBits + 1) * 4;
    uVar3 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // allocate bit storage
    *(undefined4 *)(iVar2 + 8) = uVar3;
  }
  *this = iVar2; // store internal pointer
  uVar4 = 0;
  do {
    *(undefined4 *)(*(int *)(*this + 8) + uVar4 * 4) = 0; // clear all bits
    uVar4 = uVar4 + 1;
  } while (uVar4 <= numBits);
  lVar1 = (ulonglong)(numBits + 1) * 4;
  iVar2 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // allocate another array
  this[5] = iVar2; // store second array pointer
  return;
}