// FUNC_NAME: EARSQueue::getNextWriteSlot
int __fastcall EARSQueue::getNextWriteSlot(int *queue)
{
  if (queue[0] == 0) {
    FUN_00b97aea(); // likely assertion or error handler
  }
  if (queue[1] == *(int *)(queue[0] + 4)) {
    FUN_00b97aea(); // likely assertion or error handler
  }
  return queue[1] + 0xc; // +0x0: buffer pointer, +0x4: capacity, +0x8: read index, +0xC: write index
}