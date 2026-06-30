// FUNC_NAME: BTreeIterator::advanceToNextLeaf
void __fastcall BTreeIterator::advanceToNextLeaf(int *this)
{
  char nodeFlag;
  int sibling;
  int *currentNode;
  int *parentNode;

  if (this[0] == 0) {
    FUN_00b97aea(); // likely assert or error handler
  }
  sibling = this[1];
  if (*(char *)(sibling + 0x25) == '\0') { // if current node is not flagged
    parentNode = *(int **)(sibling + 8); // get parent
    if (*(char *)((int)parentNode + 0x25) != '\0') { // if parent is flagged
      sibling = *(int *)(sibling + 4); // move to sibling
      nodeFlag = *(char *)(sibling + 0x25);
      while ((nodeFlag == '\0' && (this[1] == *(int *)(sibling + 8)))) { // while not flagged and same parent
        this[1] = sibling;
        sibling = *(int *)(sibling + 4);
        nodeFlag = *(char *)(sibling + 0x25);
      }
      this[1] = sibling;
      return;
    }
    nodeFlag = *(char *)(*parentNode + 0x25);
    currentNode = (int *)*parentNode;
    while (nodeFlag == '\0') {
      nodeFlag = *(char *)(*currentNode + 0x25);
      parentNode = currentNode;
      currentNode = (int *)*currentNode;
    }
    this[1] = (int)parentNode;
    return;
  }
  // If current node is flagged, handle error
  FUN_00b97aea(); // likely assert or error handler
  return;
}