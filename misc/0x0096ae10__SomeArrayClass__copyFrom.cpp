// FUNC_NAME: SomeArrayClass::copyFrom
int * __thiscall SomeArrayClass::copyFrom(int *this, int *other)
{
  int elementCount;
  int i;
  int offset;
  uint local_4;
  
  elementCount = other[2];
  this[2] = elementCount;
  i = 0;
  this[1] = other[1];
  if (elementCount == 0) {
    this[0] = 0;
  }
  else {
    // Allocate memory for the array elements (each element is 0x1c bytes)
    this[0] = FUN_009c8e80(other[2] * 0x1c);
    local_4 = 0;
    if (this[1] != 0) {
      do {
        // Copy each element from source to destination
        offset = this[0] + i;
        if (offset != 0) {
          // Call copy constructor or assignment for the element at source + i
          FUN_004d3b50(other[0] + i);
          // Copy fields at offsets +0x10, +0x14, +0x18
          *(undefined4 *)(offset + 0x10) = *(undefined4 *)(other[0] + i + 0x10);
          *(undefined1 *)(offset + 0x14) = *(undefined1 *)(other[0] + i + 0x14);
          *(undefined4 *)(offset + 0x18) = *(undefined4 *)(other[0] + i + 0x18);
        }
        local_4 = local_4 + 1;
        i = i + 0x1c;
      } while (local_4 < (uint)this[1]);
      return this;
    }
  }
  return this;
}