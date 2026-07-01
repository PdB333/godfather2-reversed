// FUNC_NAME: RBTree::findNodeLessOrEqual
void __thiscall RBTree::findNodeLessOrEqual(int this, int *outNode, uint *key)
{
  int *currentNode;
  int *nextNode;
  int *nodePtr;
  int candidateNode;
  int *candidatePtr;
  
  // Start from the root node stored at this+4
  currentNode = *(int **)(this + 4);
  
  // If the current node is not a leaf (leaf marker at offset +0x19)
  if (*(char *)((int)currentNode[1] + 0x19) == '\0') {
    // Traverse the tree to find the rightmost node with key < *key
    do {
      if ((uint)currentNode[3] < *key) {
        // Go right (key is greater than current node's key)
        nextNode = (int *)currentNode[2];
      }
      else {
        // Go left (key is less or equal)
        nextNode = (int *)*currentNode;
        currentNode = nextNode;
      }
      currentNode = nextNode;
    } while (*(char *)((int)nextNode + 0x19) == '\0');
  }
  
  // candidateNode holds the last node that went left (the potential result)
  candidateNode = this;
  
  // If we never went left (currentNode is still root) or the found node's key is > *key
  if ((currentNode == *(int **)(this + 4)) || (*key < (uint)currentNode[3])) {
    // No valid node found, return the root (sentinel)
    candidateNode = this;
    candidatePtr = *(int **)(this + 4);
    nodePtr = &candidateNode;
  }
  else {
    // Return the node we found (the last left turn)
    nodePtr = &candidateNode;
  }
  
  // Output the node pointer and its key
  *outNode = *nodePtr;
  outNode[1] = nodePtr[1];
  return;
}