// FUNC_NAME: BinaryTree::advanceToNextNode
void __fastcall BinaryTree::advanceToNextNode(int *treeContext)
{
  char cVar1;
  int *currentNode;
  int iVar3;
  int iVar4;
  
  if (*treeContext == 0) {
    FUN_00b97aea();
  }
  currentNode = (int *)treeContext[1];
  if (*(char *)((int)currentNode + 0x19) == '\0') {
    iVar3 = *currentNode;
    if (*(char *)(iVar3 + 0x19) == '\0') {
      cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x19);
      iVar4 = *(int *)(iVar3 + 8);
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*(int *)(iVar4 + 8) + 0x19);
        iVar3 = iVar4;
        iVar4 = *(int *)(iVar4 + 8);
      }
      treeContext[1] = iVar3;
      return;
    }
    currentNode = (int *)currentNode[1];
    cVar1 = *(char *)((int)currentNode + 0x19);
    while ((cVar1 == '\0' && (treeContext[1] == *currentNode))) {
      treeContext[1] = (int)currentNode;
      currentNode = (int *)currentNode[1];
      cVar1 = *(char *)((int)currentNode + 0x19);
    }
    if (*(char *)(treeContext[1] + 0x19) != '\0') {
      FUN_00b97aea();
      return;
    }
    treeContext[1] = (int)currentNode;
  }
  else {
    iVar3 = currentNode[2];
    treeContext[1] = iVar3;
    if (*(char *)(iVar3 + 0x19) != '\0') {
      FUN_00b97aea();
      return;
    }
  }
  return;
}