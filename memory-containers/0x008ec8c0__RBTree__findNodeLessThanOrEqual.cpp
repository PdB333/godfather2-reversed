// FUNC_NAME: RBTree::findNodeLessThanOrEqual
void __thiscall RBTree::findNodeLessThanOrEqual(int this, int *outNode, uint *key)
{
  int *currentNode;
  int *nextNode;
  int *stackNode;
  int stackThis;
  int *stackCurrent;
  int *stackOut;
  
  currentNode = *(int **)(this + 4); // +0x4: root node pointer
  if (*(char *)((int)currentNode[1] + 0x25) == '\0') { // +0x25: node color flag (0 = red, 1 = black)
    nextNode = (int *)currentNode[1];
    do {
      if ((uint)nextNode[3] < *key) { // +0xC: node key value
        stackNode = (int *)nextNode[2]; // +0x8: right child
      }
      else {
        stackNode = (int *)*nextNode; // +0x0: left child
        currentNode = nextNode;
      }
      nextNode = stackNode;
    } while (*(char *)((int)stackNode + 0x25) == '\0');
  }
  stackThis = this;
  if ((currentNode == *(int **)(this + 4)) || (*key < (uint)currentNode[3])) {
    stackOut = this;
    stackCurrent = *(int **)(this + 4);
    stackNode = &stackOut;
  }
  else {
    stackNode = &stackThis;
  }
  int result = stackNode[1];
  *outNode = *stackNode;
  outNode[1] = result;
  return;
}