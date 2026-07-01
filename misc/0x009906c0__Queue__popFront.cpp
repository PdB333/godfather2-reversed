// FUNC_NAME: Queue::popFront
undefined4 * __fastcall Queue::popFront(int this)
{
  undefined4 *node;
  undefined4 nextNode;
  
  if ((*(int *)(this + 0x34) == 0) &&
     ((*(int *)(this + 0x30) == 0 || ((*(byte *)(this + 0x24) & 1) == 0)))) {
    // Queue is empty or not initialized, call error handler
    FUN_004de190();
  }
  
  node = *(undefined4 **)(this + 0x34);  // +0x34 = head pointer
  if (node != (undefined4 *)0x0) {
    nextNode = *node;  // First field of node is next pointer
    *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;  // +0x10 = popCount (increment)
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + -1;    // +0x0C = size (decrement)
    *(undefined4 *)(this + 0x34) = nextNode;  // Update head to next node
    return node;
  }
  
  return (undefined4 *)0x0;
}