// FUNC_NAME: RBTree::findNodeOrParent
void RBTree::findNodeOrParent(uint *key)
{
  int *result;
  undefined4 *currentNode;
  undefined4 *childNode;
  undefined4 *parentNode;
  int treeRoot;
  
  treeRoot = *(int *)(this + 0x1c); // +0x1c: root node pointer
  currentNode = *(undefined4 **)(treeRoot + 0x1c); // +0x1c: tree root's left child?
  
  // If the current node is not a leaf (leaf nodes have byte at +0x15 == 0)
  if (*(char *)((int)currentNode[1] + 0x15) == '\0') {
    parentNode = (undefined4 *)currentNode[1];
    do {
      // Compare key with current node's key (at offset +0x0c from node)
      if ((uint)parentNode[3] < *key) {
        childNode = (undefined4 *)parentNode[2]; // right child
      }
      else {
        childNode = (undefined4 *)*parentNode; // left child
        currentNode = parentNode;
      }
      parentNode = childNode;
    } while (*(char *)((int)childNode + 0x15) == '\0'); // continue while not leaf
  }
  
  // Now currentNode points to the last non-leaf node visited
  parentNode = *(undefined4 **)(treeRoot + 0x1c);
  
  // If we found a node that is not the root and its key <= search key
  if ((currentNode != parentNode) && ((uint)currentNode[3] <= *key)) {
    *result = this;
    result[1] = (int)currentNode;
    return;
  }
  
  // Otherwise return the root as the result
  *result = this;
  result[1] = (int)parentNode;
  return;
}