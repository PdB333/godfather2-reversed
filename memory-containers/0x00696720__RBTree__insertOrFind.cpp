// FUNC_NAME: RBTree::insertOrFind
void __thiscall RBTree::insertOrFind(int this, int *outNode, undefined4 key)
{
  char cVar1;
  undefined4 *currentNode;
  undefined4 *parentNode;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  bool isLeftChild;
  int root;
  undefined4 *insertParent;
  
  currentNode = (undefined4 *)(*(undefined4 **)(this + 4))[1]; // +0x4: root node pointer
  isLeftChild = true;
  cVar1 = *(char *)((int)currentNode + 0x29); // +0x29: node color (0 = red, 1 = black)
  parentNode = *(undefined4 **)(this + 4);
  while (cVar1 == '\0') {
    iVar4 = FUN_004d4b20(currentNode + 3); // compare key with node's key at +0xC
    isLeftChild = iVar4 < 0;
    if (isLeftChild) {
      puVar6 = (undefined4 *)*currentNode; // left child
    }
    else {
      puVar6 = (undefined4 *)currentNode[2]; // right child
    }
    parentNode = currentNode;
    currentNode = puVar6;
    cVar1 = *(char *)((int)puVar6 + 0x29);
  }
  root = this;
  insertParent = parentNode;
  if (isLeftChild) {
    if (parentNode == (undefined4 *)**(int **)(this + 4)) {
      piVar5 = (int *)FUN_006962c0(&root,1,parentNode,key); // insert as left child
      iVar4 = *piVar5;
      outNode[1] = piVar5[1];
      *(undefined1 *)(outNode + 2) = 1; // flag: new node inserted
      *outNode = iVar4;
      return;
    }
    FUN_00694160(); // error: invalid tree state
  }
  currentNode = insertParent;
  iVar4 = FUN_004d4b20(key); // compare key with insertParent's key
  if (-1 < iVar4) {
    outNode[1] = (int)currentNode;
    *(undefined1 *)(outNode + 2) = 0; // flag: existing node found
    *outNode = root;
    return;
  }
  piVar5 = (int *)FUN_006962c0(&root,isLeftChild,parentNode,key); // insert as right child
  iVar4 = *piVar5;
  outNode[1] = piVar5[1];
  *(undefined1 *)(outNode + 2) = 1; // flag: new node inserted
  *outNode = iVar4;
  return;
}