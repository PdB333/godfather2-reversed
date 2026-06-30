// FUNC_NAME: EARS::VectorAllocator::reserve
void EARS::VectorAllocator::reserve(uint newCapacity)
{
  int iVar1;
  uint uVar2;
  undefined4 *newBuffer;
  int iVar4;
  int iVar5;
  undefined4 *this;
  int unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  uint local_4;
  
  if (newCapacity < 0x6666667) {
    if (this[2] == 0) { // +0x08: mSize (element count)
      uVar2 = 0;
    }
    else {
      uVar2 = (int)(this[4] - this[2]) / 0x28; // +0x10: mEnd, +0x08: mBegin -> capacity = (end - begin) / elementSize
    }
    if (uVar2 < newCapacity) {
      newBuffer = (undefined4 *)this[1]; // +0x04: mBuffer (current allocation)
      if (newBuffer == (undefined4 *)0x0) {
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        newBuffer = &local_c;
      }
      iVar4 = (*(code *)**(undefined4 **)*this)(newCapacity * 0x28, newBuffer); // vtable[0] = allocator function
      if ((uint)this[3] < (uint)this[2]) { // +0x0C: mAllocatedEnd, +0x08: mBegin
        FUN_00b97aea(); // assertion failure
      }
      local_4 = this[2];
      if ((uint)this[3] < local_4) {
        FUN_00b97aea(); // assertion failure
      }
      uVar2 = local_4;
      local_4 = local_4 & 0xffffff00;
      FUN_005dab00(uVar2, local_4, local_4); // memcpy/memmove
      iVar1 = this[2];
      if (iVar1 == 0) {
        iVar5 = 0;
        unaff_EDI = newCapacity * 0x28;
      }
      else {
        iVar5 = (this[3] - iVar1) / 0x28; // +0x0C: mAllocatedEnd - mBegin
        (**(code **)(*(int *)*this + 4))(iVar1, ((this[4] - iVar1) / 0x28) * 0x28); // vtable[1] = deallocator
      }
      this[4] = unaff_EDI + iVar4; // +0x10: mEnd = newBuffer + newCapacity * elementSize
      this[3] = iVar4 + iVar5 * 0x28; // +0x0C: mAllocatedEnd = newBuffer + oldAllocatedSize
      this[2] = iVar4; // +0x08: mBegin = newBuffer
    }
    return;
  }
  FUN_005d9ed0(); // overflow error handler
  return;
}