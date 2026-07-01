// FUNC_NAME: ObjectPool::destroyAll
void __fastcall ObjectPool::destroyAll(int *this)
{
  int iVar1;
  int index;
  int offset;
  
  index = this[1] + -1;
  if (-1 < index) {
    offset = index * 0x14;
    do {
      iVar1 = *(int *)(*this + offset);  // +0x00: object pointer array
      if (iVar1 != 0) {
        // Call destructor at offset +0x0C in the slot entry
        (**(code **)(*this + offset + 0xc))(iVar1);
      }
      index = index + -1;
      offset = offset + -0x14;  // Each slot is 0x14 bytes
    } while (-1 < index);
  }
  this[1] = 0;  // +0x04: count
  FUN_009c8f10(*this);  // Free the allocated memory
  *this = 0;  // +0x00: pointer to slot array
  this[2] = 0;  // +0x08: capacity
  return;
}