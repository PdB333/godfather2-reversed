// FUNC_NAME: FixedVectorContainer::reserve
void __thiscall FixedVectorContainer::reserve(int *this, uint newCapacity)
{
  uint oldCapacity = this[2];
  if (oldCapacity < newCapacity)
  {
    // Allocate new block: each element is 0xC (12) bytes
    undefined8 *newData = (undefined8 *)FUN_009c8e80(newCapacity * 0xc);
    uint count = 0;
    if (this[1] != 0)
    {
      // Copy existing elements (0xC bytes each) from old to new
      int srcOffset = 0;
      undefined8 *dst = newData;
      do
      {
        int basePtr = this[0];
        if (dst != (undefined8 *)0x0)
        {
          *dst = *(undefined8 *)(basePtr + srcOffset);
          *(undefined4 *)(dst + 1) = *(undefined4 *)((undefined8 *)(basePtr + srcOffset) + 1);
        }
        count++;
        srcOffset += 0xc;
        dst = (undefined8 *)((int)dst + 0xc);
      } while (count < (uint)this[1]);
    }
    // Free old data
    FUN_009c8f10(this[0]); // operator delete[](void*)
    this[0] = (int)newData;
    this[2] = newCapacity;
  }
}