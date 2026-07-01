// FUNC_NAME: RBTree::findOrInsertNode
undefined4 * __thiscall RBTree::findOrInsertNode(int this, uint *key)
{
  undefined4 *currentNode;
  undefined4 *childNode;
  int *insertResult;
  undefined4 *rootNode;
  uint localKey[2];
  undefined1 localBuffer[8];
  
  rootNode = *(undefined4 **)(this + 4);
  if (*(char *)((int)rootNode[1] + 0x15) == '\0') {
    currentNode = (undefined4 *)rootNode[1];
    do {
      if ((uint)currentNode[3] < *key) {
        childNode = (undefined4 *)currentNode[2];
      }
      else {
        childNode = (undefined4 *)*currentNode;
        rootNode = currentNode;
      }
      currentNode = childNode;
    } while (*(char *)((int)childNode + 0x15) == '\0');
  }
  if ((rootNode == *(undefined4 **)(this + 4)) || (*key < (uint)rootNode[3])) {
    localKey[0] = *key;
    localKey[1] = 0;
    insertResult = (int *)FUN_008eef50(localBuffer, this, rootNode, localKey);
    this = *insertResult;
    rootNode = (undefined4 *)insertResult[1];
  }
  if (this == 0) {
    FUN_00b97aea(); // likely assertion failure
  }
  if (rootNode == *(undefined4 **)(this + 4)) {
    FUN_00b97aea(); // likely assertion failure
  }
  return rootNode + 4;
}