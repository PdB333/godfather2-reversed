// FUNC_NAME: BinarySearchTree::findNode
undefined4 * __thiscall BinarySearchTree::findNode(int this, undefined4 key)
{
  char cVar1;
  undefined4 *currentNode;
  int compareResult;
  undefined4 *nextNode;
  undefined4 *parentNode;
  
  parentNode = (undefined4 *)(*(undefined4 **)(this + 4))[1];  // +0x04: root node pointer
  cVar1 = *(char *)((int)parentNode + 0x29);  // +0x29: node flag (0 = valid/not found)
  currentNode = *(undefined4 **)(this + 4);
  while (cVar1 == '\0') {
    compareResult = FUN_004d4b20(key);  // compare function for ordering
    if (compareResult < 0) {
      nextNode = (undefined4 *)parentNode[2];  // +0x08: left child pointer
      parentNode = currentNode;
    }
    else {
      nextNode = (undefined4 *)*parentNode;  // +0x00: right child pointer
    }
    currentNode = parentNode;
    parentNode = nextNode;
    cVar1 = *(char *)((int)nextNode + 0x29);
  }
  return currentNode;
}