// FUNC_NAME: FreeListAllocator::pushNode
void __fastcall FreeListAllocator::pushNode(int this, int allocator, undefined4 data)
{
  undefined4 *node;
  
  node = *(undefined4 **)(this + 0x10);
  if (node != (undefined4 *)0x0) {
    if (*(undefined4 **)(this + 0x14) == node) {
      *(undefined4 *)(this + 0x14) = 0;
    }
    *(undefined4 *)(this + 0x10) = *node;
  }
  node[1] = data;
  *node = 0;
  if (*(undefined4 **)(allocator + 0x114) != (undefined4 *)0x0) {
    **(undefined4 **)(allocator + 0x114) = node;
    *(undefined4 **)(allocator + 0x114) = node;
    return;
  }
  *(undefined4 **)(allocator + 0x110) = node;
  *(undefined4 **)(allocator + 0x114) = node;
  return;
}