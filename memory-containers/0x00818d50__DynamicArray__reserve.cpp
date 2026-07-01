// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
  int *oldData;
  uint i;
  int *newData;
  int *src;
  int *dst;

  // Only reallocate if requested capacity is larger than current capacity
  if (this[2] < (int)newCapacity) {
    // Allocate new block: each element is 0xC (12) bytes
    newData = (int *)Memory::alloc(newCapacity * 0xC); // Custom allocator at 0x009c8e80
    if (this[0] != 0) {
      // Copy existing elements (up to current size) to new buffer
      i = 0;
      if (this[1] != 0) {
        dst = newData;
        src = (int *)this[0];
        do {
          // Copy one 12-byte element (three ints)
          *dst = *src;
          dst[1] = src[1];
          // Note: third int (offset 8) is implicitly copied via the subsequent assignment?
          // Actually the decompiled shows copying only two ints? Wait:
          // The code does: *puVar3 = *(undefined8 *)(iVar1 + iVar4); (8 bytes) and
          // *(undefined4 *)(puVar3 + 1) = *(undefined4 *)((undefined8 *)(iVar1 + iVar4) + 1);
          // That copies 12 bytes total: first 8 bytes (as undefined8) and then 4 bytes at offset 8.
          // So effectively three ints: [0]=32bit, [1]=32bit, [2]=32bit? Actually undefined8 spans two ints.
          // So we represent as copying three ints below:
          dst[0] = src[0];
          dst[1] = src[1];
          dst[2] = src[2];
          i++;
          src = src + 3; // advance by 3 ints (12 bytes)
          dst = dst + 3;
        } while (i < (uint)this[1]);
      }
      // Free old buffer
      Memory::free((void *)this[0]); // Free function at 0x009c8f10
    }
    // Update pointer and capacity; size remains unchanged
    this[0] = (int)newData;
    this[2] = newCapacity;
  }
}