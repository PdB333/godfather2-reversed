// FUNC_NAME: SomeList::replaceNode
void __thiscall SomeList::replaceNode(int this, int newNode)
{
  int *currentNodePtr;
  int *nextNodePtr;
  int currentNode;
  
  currentNodePtr = (int *)(this + 0x4c);
  // Check if current node exists and is not a sentinel (0x48)
  if (((*(int *)(this + 0x4c) != 0) && (*(int *)(this + 0x4c) != 0x48)) &&
     (nextNodePtr = (int *)(this + 0x54), nextNodePtr != currentNodePtr)) {
    currentNode = *currentNodePtr;
    // If next node differs from current, replace it
    if (*nextNodePtr != currentNode) {
      if (*nextNodePtr != 0) {
        FUN_004daf90(nextNodePtr); // Likely freeNode or removeNode
      }
      *nextNodePtr = currentNode;
      if (currentNode != 0) {
        *(undefined4 *)(this + 0x58) = *(undefined4 *)(currentNode + 4);
        *(int **)(currentNode + 4) = nextNodePtr;
      }
    }
  }
  // Adjust newNode: if null, keep null; otherwise offset by 0x48 (sentinel size)
  if (newNode == 0) {
    newNode = 0;
  }
  else {
    newNode = newNode + 0x48;
  }
  // Replace the current node with the adjusted newNode
  if (*currentNodePtr != newNode) {
    if (*currentNodePtr != 0) {
      FUN_004daf90(currentNodePtr);
    }
    *currentNodePtr = newNode;
    if (newNode != 0) {
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(newNode + 4);
      *(int **)(newNode + 4) = currentNodePtr;
    }
  }
  return;
}