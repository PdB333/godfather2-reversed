// FUNC_NAME: LinkedList::insertAfter
void __thiscall LinkedList::insertAfter(int *node, int *newNode)
{
  int *nextNode;
  int *prevNode;
  
  nextNode = (int *)*node;
  *node = *(int *)((int)nextNode + 8);
  if (*(char *)(*(int *)((int)nextNode + 8) + 0x15) == '\0') {
    *(int **)(*(int *)((int)nextNode + 8) + 4) = node;
  }
  *(int *)((int)nextNode + 4) = node[1];
  if (node == *(int **)(*(int *)((int)newNode + 0x1c) + 4)) {
    *(int *)(*(int *)((int)newNode + 0x1c) + 4) = (int)nextNode;
    *(int **)((int)nextNode + 8) = node;
    node[1] = (int)nextNode;
    return;
  }
  prevNode = (int *)node[1];
  if (node == (int *)prevNode[2]) {
    prevNode[2] = (int)nextNode;
    *(int **)((int)nextNode + 8) = node;
    node[1] = (int)nextNode;
    return;
  }
  *prevNode = (int)nextNode;
  *(int **)((int)nextNode + 8) = node;
  node[1] = (int)nextNode;
  return;
}