// FUNC_NAME: RBTree::findOrInsert
void __thiscall RBTree::findOrInsert(int this, int *outNode, uint *key)
{
  int iVar1;
  undefined4 *currentNode;
  int *nodePtr;
  undefined4 *parentNode;
  bool isLeftChild;
  int stackNode;
  undefined4 *stackParent;
  
  parentNode = *(undefined4 **)(this + 4);
  isLeftChild = true;
  if (*(char *)((int)parentNode[1] + 0x25) == '\0') {
    currentNode = (undefined4 *)parentNode[1];
    do {
      parentNode = currentNode;
      isLeftChild = *key < (uint)currentNode[3];
      if (isLeftChild) {
        currentNode = (undefined4 *)*currentNode;
      }
      else {
        currentNode = (undefined4 *)currentNode[2];
      }
    } while (*(char *)((int)currentNode + 0x25) == '\0');
  }
  stackNode = this;
  stackParent = parentNode;
  if (isLeftChild) {
    if (parentNode == (undefined4 *)**(int **)(this + 4)) {
      isLeftChild = true;
      goto LAB_008ee3bc;
    }
    FUN_008ea580();
  }
  if (*key <= (uint)stackParent[3]) {
    *outNode = stackNode;
    outNode[1] = (int)stackParent;
    *(undefined1 *)(outNode + 2) = 0;
    return;
  }
LAB_008ee3bc:
  nodePtr = (int *)FUN_008ed110(&stackNode,isLeftChild,parentNode,key);
  iVar1 = nodePtr[1];
  *outNode = *nodePtr;
  outNode[1] = iVar1;
  *(undefined1 *)(outNode + 2) = 1;
  return;
}