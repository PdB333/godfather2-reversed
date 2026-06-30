// FUNC_NAME: FixedSizeAllocator::pushNode
undefined1 __fastcall FixedSizeAllocator::pushNode(undefined4 *allocator, undefined4 *node)
{
  undefined1 result;
  
  result = 0;
  if ((allocator != (undefined4 *)0x0) && (*(ushort *)((int)allocator + 10) < *(ushort *)(allocator + 2)))
  {
    if (*(ushort *)((int)allocator + 10) == 0) {
      allocator[1] = node;  // +0x04: firstNode
    }
    else {
      if ((undefined4 *)*allocator == (undefined4 *)0x0) {  // +0x00: head
        return 0;
      }
      *(undefined4 *)*allocator = node;  // head->next = node
    }
    node[1] = *allocator;  // +0x04: node->prev = head
    *node = 0;             // +0x00: node->next = null
    *(short *)((int)allocator + 10) = *(short *)((int)allocator + 10) + 1;  // +0x0A: count++
    result = 1;
    *allocator = node;  // head = node
  }
  return result;
}