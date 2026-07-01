// FUNC_NAME: BinaryTree::advanceToNextActiveNode
void __fastcall BinaryTree::advanceToNextActiveNode(int *treeContext)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  // If root is null, call error handler
  if (*treeContext == 0) {
    FUN_00b97aea(); // likely error/assert handler
  }
  
  piVar2 = (int *)treeContext[1]; // current node pointer (offset +0x04)
  
  // Check if current node is inactive (byte at +0x25)
  if (*(char *)((int)piVar2 + 0x25) == '\0') {
    iVar3 = *piVar2; // left child pointer
    if (*(char *)(iVar3 + 0x25) == '\0') {
      // Traverse left children until we find an active node
      cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x25); // right child's active flag
      iVar4 = *(int *)(iVar3 + 8); // right child pointer
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*(int *)(iVar4 + 8) + 0x25); // check right child's active flag
        iVar3 = iVar4;
        iVar4 = *(int *)(iVar4 + 8); // move to right child
      }
      treeContext[1] = iVar3; // set current to the found node
      return;
    }
    
    // Move to parent (offset +0x04) and check active flag
    piVar2 = (int *)piVar2[1]; // parent pointer
    cVar1 = *(char *)((int)piVar2 + 0x25);
    while ((cVar1 == '\0' && (treeContext[1] == *piVar2))) {
      // If current node is left child of parent and parent is inactive, move up
      treeContext[1] = (int)piVar2;
      piVar2 = (int *)piVar2[1]; // grandparent
      cVar1 = *(char *)((int)piVar2 + 0x25);
    }
    
    if (*(char *)(treeContext[1] + 0x25) != '\0') {
      FUN_00b97aea(); // error: found active node unexpectedly
      return;
    }
    treeContext[1] = (int)piVar2; // set current to the found node
  }
  else {
    // Current node is active, move to its right child (offset +0x08)
    iVar3 = piVar2[2]; // right child pointer
    treeContext[1] = iVar3;
    if (*(char *)(iVar3 + 0x25) != '\0') {
      FUN_00b97aea(); // error: right child is active unexpectedly
      return;
    }
  }
  return;
}