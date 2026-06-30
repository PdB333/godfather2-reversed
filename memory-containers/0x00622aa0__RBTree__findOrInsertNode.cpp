// FUNC_NAME: RBTree::findOrInsertNode
int* RBTree::findOrInsertNode(int thisPtr, int* outResult, uint* key)
{
  int iVar1;
  undefined4 *currentNode;
  int *piVar3;
  bool isLeftChild;
  int stackThis;
  undefined4 *stackCurrent;
  
  stackCurrent = *(undefined4 **)(thisPtr + 0x1c); // +0x1c: root node pointer
  isLeftChild = true;
  if (*(char *)((int)stackCurrent[1] + 0x25) == '\0') { // +0x25: node color flag (0 = red, 1 = black)
    currentNode = (undefined4 *)stackCurrent[1];
    do {
      stackCurrent = currentNode;
      isLeftChild = *key < (uint)currentNode[3]; // +0x0C: key value
      if (isLeftChild) {
        currentNode = (undefined4 *)*currentNode; // left child
      }
      else {
        currentNode = (undefined4 *)currentNode[2]; // right child
      }
    } while (*(char *)((int)currentNode + 0x25) == '\0');
  }
  stackThis = thisPtr;
  if (isLeftChild) {
    if (stackCurrent == (undefined4 *)**(int **)(thisPtr + 0x1c)) {
      piVar3 = (int *)FUN_00622c80(thisPtr, &stackThis, 1, key); // insert new node
      iVar1 = *piVar3;
      outResult[1] = piVar3[1];
      *outResult = iVar1;
      *(undefined1 *)(outResult + 2) = 1; // flag: inserted
      return outResult;
    }
    FUN_006242f0(); // error handler or rebalance
  }
  if ((uint)stackCurrent[3] < *key) {
    piVar3 = (int *)FUN_00622c80(thisPtr, &stackThis, isLeftChild, key); // insert new node
    iVar1 = piVar3[1];
    *outResult = *piVar3;
    outResult[1] = iVar1;
    *(undefined1 *)(outResult + 2) = 1; // flag: inserted
    return outResult;
  }
  outResult[1] = (int)stackCurrent; // existing node found
  *outResult = stackThis;
  *(undefined1 *)(outResult + 2) = 0; // flag: found existing
  return outResult;
}