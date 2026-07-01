// FUNC_NAME: LinkedList::clearAndDestroy
void __fastcall LinkedList::clearAndDestroy(undefined4 *listHead)
{
  undefined4 *current;
  undefined4 *next;
  
  current = (undefined4 *)*listHead;
  while (current != listHead) {
    next = (undefined4 *)*current;
    if (current[2] != 0) {
      // Destroy the data at offset +0x08 (likely a pointer to a heap-allocated object)
      FUN_004daf90(current + 2);
    }
    // Remove and free the node itself
    FUN_009c8f10(current);
    current = next;
  }
  return;
}