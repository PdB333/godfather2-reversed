// FUNC_NAME: SomeArrayClass::copyFrom
int * __thiscall SomeArrayClass::copyFrom(int *this, int *other)
{
  int elementSize;
  int i;
  undefined4 *destElement;
  uint count;
  
  elementSize = other[2]; // +0x08: element size (0x34)
  this[2] = elementSize; // +0x08: store element size
  this[1] = other[1]; // +0x04: store count
  if (elementSize == 0) {
    this[0] = 0; // +0x00: null pointer
  }
  else {
    this[0] = FUN_009c8e80(other[2] * 0x34); // allocate memory for elements (0x34 bytes each)
    count = 0;
    if (this[1] != 0) {
      do {
        destElement = (undefined4 *)(this[0] + i); // +0x00: base pointer
        if (destElement != (undefined4 *)0x0) {
          iVar1 = other[0] + i; // source element base
          *destElement = *(undefined4 *)(other[0] + i); // copy first 4 bytes
          destElement[1] = *(undefined4 *)(iVar1 + 4); // copy next 4 bytes
          destElement[2] = *(undefined4 *)(iVar1 + 8); // copy next 4 bytes
          FUN_00498500(iVar1 + 0xc); // copy 12 bytes at offset 0x0C
          FUN_00498500(iVar1 + 0x18); // copy 12 bytes at offset 0x18
          FUN_00498500(iVar1 + 0x24); // copy 12 bytes at offset 0x24
          destElement[0xc] = *(undefined4 *)(iVar1 + 0x30); // copy last 4 bytes at offset 0x30
        }
        count = count + 1;
        i = i + 0x34; // each element is 0x34 bytes
      } while (count < (uint)this[1]);
      return this;
    }
  }
  return this;
}