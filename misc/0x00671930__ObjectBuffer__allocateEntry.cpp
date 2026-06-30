// FUNC_NAME: ObjectBuffer::allocateEntry
void ObjectBuffer::allocateEntry(int param_1, int *param_2)
{
  ushort count;
  int newBuffer;
  ushort *bufferHeader; // unaff_ESI - likely "this" pointing to buffer header block
  
  count = *bufferHeader; // Current number of entries (+0x00)
  *param_2 = 0;
  if (count == 0) {
    newBuffer = FUN_00673070(); // Allocate new buffer pool
  }
  else {
    newBuffer = FUN_006730f0(*(int *)(bufferHeader + 2), (count + 1) * 0xc + -0xc); // Resize existing buffer
  }
  *(int *)(bufferHeader + 2) = newBuffer; // Store buffer pointer (+0x04)
  // Entry layout: 12 bytes per entry (+0x00 = previous, +0x04 = item, +0x08 = next)
  *(int *)(*(int *)(bufferHeader + 2) + 4 + (uint)*bufferHeader * 0xc) = param_1;
  *(int *)(*(int *)(bufferHeader + 2) + 8 + (uint)*bufferHeader * 0xc) = 0;
  *bufferHeader = *bufferHeader + 1;
  
  int index = FUN_006721d0(); // Get new entry index
  *param_2 = index;
  return;
}