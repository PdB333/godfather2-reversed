// FUNC_NAME: LinkedList::destroyAllNodes
void __fastcall LinkedList::destroyAllNodes(undefined4 *listHead)
{
  undefined4 *currentNode;
  undefined4 *nextNode;
  
  currentNode = (undefined4 *)*listHead;
  while (currentNode != listHead) {
    nextNode = (undefined4 *)*currentNode;
    if (currentNode[2] != 0) {          // +0x08: node data pointer
      FUN_004daf90(currentNode + 2);    // freeNodeData
    }
    FUN_009c8f10(currentNode);          // freeNode
    currentNode = nextNode;
  }
  return;
}