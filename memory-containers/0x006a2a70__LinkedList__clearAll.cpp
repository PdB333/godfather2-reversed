// FUNC_NAME: LinkedList::clearAll
void __fastcall LinkedList::clearAll(undefined4 *listHead)
{
  undefined4 *nextNode;
  undefined4 *currentNode;
  
  currentNode = (undefined4 *)*listHead;
  while (currentNode != listHead) {
    nextNode = (undefined4 *)*currentNode;
    FUN_009c8f10(currentNode);  // node destructor / free
    currentNode = nextNode;
  }
  // Reset the list to empty (head points to itself)
  listHead[1] = listHead;   // +0x04: tail = head
  *listHead = listHead;     // +0x00: head = head
  return;
}