// FUNC_NAME: RBTree::findNodeLessThanOrEqual
void __thiscall RBTree::findNodeLessThanOrEqual(int this, int *outNode, uint *key)
{
  int *currentNode;
  int *childNode;
  int *parentNode;
  int stackNode;
  int *stackChild;
  int stackParent;
  int *stackParent2;
  
  // Start at the root node (stored at this+4)
  currentNode = *(int **)(this + 4);
  
  // Traverse the tree while the current node's "red" flag (byte at +0x15) is 0
  // This flag being 0 means the node is not a leaf/sentinel
  if (*(char *)((int)currentNode[1] + 0x15) == '\0') {
    childNode = (int *)currentNode[1];
    do {
      // If the current node's key (at +0xC) is less than the search key, go right
      if ((uint)childNode[3] < *key) {
        parentNode = (int *)childNode[2];
      }
      // Otherwise go left and update the "last less-than-or-equal" candidate
      else {
        parentNode = (int *)*childNode;
        currentNode = childNode;
      }
      childNode = parentNode;
    } while (*(char *)((int)parentNode + 0x15) == '\0');
  }
  
  // Now determine the result based on the last candidate found
  stackNode = this;
  
  // If we never found a node with key <= search key, or the candidate's key is > search key
  if ((currentNode == *(int **)(this + 4)) || (*key < (uint)currentNode[3])) {
    // Return the tree's sentinel (null node)
    stackParent = this;
    stackParent2 = *(int **)(this + 4);
    parentNode = &stackParent;
  }
  else {
    // Return the last node that was <= search key
    parentNode = &stackNode;
  }
  
  // Output the result node (pointer and its parent/child info)
  int resultNode = parentNode[1];
  *outNode = *parentNode;
  outNode[1] = resultNode;
  
  return;
}