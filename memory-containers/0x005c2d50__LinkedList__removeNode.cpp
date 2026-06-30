// FUNC_NAME: LinkedList::removeNode
void __fastcall LinkedList::removeNode(int *listHead, int node)
{
  if (node != 0) {
    // If node is the tail, update tail to previous node
    if (listHead[1] == node) {
      listHead[1] = *(int *)(node + 0x10); // +0x10: prev pointer
    }
    // If node is the head, update head to next node
    if (*listHead == node) {
      *listHead = *(int *)(*listHead + 0x10); // +0x10: prev pointer (actually next? or prev?)
    }
    // Unlink the node from the list (likely updates next/prev pointers of neighbors)
    FUN_005c2e30(); // unlinkNode(node)
  }
}