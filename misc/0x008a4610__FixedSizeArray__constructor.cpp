// FUNC_NAME: FixedSizeArray::constructor
void __thiscall FixedSizeArray::constructor(int *this, uint maxSize, int elementSize)
{
  longlong lVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  this[3] = elementSize;           // +0x0C: elementSize
  this[1] = 0;                     // +0x04: count (initialized to 0)
  this[2] = maxSize;               // +0x08: maxSize
  this[4] = 0;                     // +0x10: flags (initialized to 0)
  iVar2 = FUN_009c8e50(0xc);       // allocate memory for the array header (12 bytes)
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    lVar1 = (ulonglong)(maxSize + 1) * 4;  // size of data buffer: (maxSize+1)*4 bytes
    uVar3 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // allocate data buffer
    *(undefined4 *)(iVar2 + 8) = uVar3;    // store data pointer at offset +8 in header
  }
  *this = iVar2;                   // +0x00: pointer to array header
  uVar4 = 0;
  do {
    *(undefined4 *)(*(int *)(*this + 8) + uVar4 * 4) = 0;  // zero-initialize data buffer
    uVar4 = uVar4 + 1;
  } while (uVar4 <= maxSize);
  lVar1 = (ulonglong)(maxSize + 1) * 4;
  iVar2 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // allocate another buffer
  this[5] = iVar2;                 // +0x14: secondary buffer pointer (e.g., for flags or indices)
  return;
}