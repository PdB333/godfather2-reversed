// FUNC_NAME: BinarySearchTree::findNodeWithKey
void __thiscall BinarySearchTree::findNodeWithKey(int this, int *outNode, undefined4 key)
{
  undefined4 *currentNode;
  undefined4 *parentNode;
  undefined4 *nextNode;
  int comparisonResult;
  
  currentNode = *(undefined4 **)(this + 0xc);  // +0xC: root node pointer
  parentNode = (undefined4 *)(this + 4);       // +0x4: sentinel/parent pointer (or null node)
  
  while (nextNode = currentNode, nextNode != (undefined4 *)0x0) {
    comparisonResult = FUN_004d4b20(key);  // compare function, returns <0, 0, or >0
    if (comparisonResult < 0) {
      // key is less, go left
      currentNode = (undefined4 *)*currentNode;  // left child pointer
    }
    else {
      // key is greater or equal, go right
      currentNode = (undefined4 *)currentNode[1];  // right child pointer
      parentNode = currentNode;  // track parent for insertion point
    }
  }
  
  *outNode = (int)parentNode;  // output the parent node (or insertion point)
  return;
}