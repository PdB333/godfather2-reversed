// FUNC_NAME: RedBlackTree::rotateLeft
void __fastcall RedBlackTree::rotateLeft(int *treeRoot, int *nodeX, int *nodeY)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *nodeX;
  piVar1 = *(int **)(iVar4 + 8);  // nodeX->right
  iVar2 = *(int *)(iVar4 + 4);    // nodeX->parent
  *(int *)(iVar4 + 8) = piVar1[3]; // nodeX->right = nodeY->left
  if (piVar1[3] != 0) {
    *(int *)(piVar1[3] + 4) = *nodeX; // nodeY->left->parent = nodeX
  }
  piVar1[3] = *nodeX;  // nodeY->left = nodeX
  *(int **)(*nodeX + 4) = piVar1; // nodeX->parent = nodeY
  piVar3 = (int *)*nodeX;  // nodeX (the node itself)
  if ((int *)piVar3[3] == (int *)0x0) { // nodeX->left == NULL
    iVar4 = -1;
  }
  else {
    iVar4 = *(int *)piVar3[3]; // nodeX->left->color
  }
  if ((int *)piVar3[2] == (int *)0x0) { // nodeX->right == NULL
    iVar5 = -1;
  }
  else {
    iVar5 = *(int *)piVar3[2]; // nodeX->right->color
  }
  if (iVar4 <= iVar5) {
    iVar4 = iVar5;
  }
  *piVar3 = iVar4 + 1; // nodeX->color = max(child colors) + 1
  if ((int *)*nodeX == (int *)0x0) {
    iVar4 = -1;
  }
  else {
    iVar4 = *(int *)*nodeX; // nodeX->color
  }
  if ((int *)piVar1[2] == (int *)0x0) { // nodeY->right == NULL
    iVar5 = -1;
  }
  else {
    iVar5 = *(int *)piVar1[2]; // nodeY->right->color
  }
  if (iVar4 <= iVar5) {
    iVar4 = iVar5;
  }
  *piVar1 = iVar4 + 1; // nodeY->color = max(child colors) + 1
  piVar1[1] = iVar2;   // nodeY->parent = nodeX->parent
  if (iVar2 != 0) {
    if (*(int *)(iVar2 + 8) == *nodeX) { // parent->left == nodeX
      *(int **)(iVar2 + 8) = piVar1;     // parent->left = nodeY
      *nodeX = (int)piVar1;              // treeRoot = nodeY
      return;
    }
    *(int **)(iVar2 + 0xc) = piVar1;     // parent->right = nodeY
    *nodeX = (int)piVar1;                // treeRoot = nodeY
    return;
  }
  *nodeY = (int)piVar1;  // treeRoot = nodeY
  *nodeX = (int)piVar1;  // treeRoot = nodeY (same)
  return;
}