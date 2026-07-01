// FUNC_NAME: BTree::insertNode
undefined4 * __thiscall BTree::insertNode(int this, int *root, uint *key, undefined1 *value)
{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *unaff_retaddr;
  
  iVar6 = *root;
  if (iVar6 == 0) {
    // Root is null, allocate a new node
    puVar4 = *(undefined4 **)(this + 8);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = &DAT_01218a14;
    }
    // Allocate 0x18 bytes for node (6 fields: 4 ints + 2 shorts?)
    puVar4 = (undefined4 *)(**(code **)**(undefined4 **)(this + 0xc))(0x18,puVar4);
    if (puVar4 != (undefined4 *)0x0) {
      iVar6 = *root;
      uVar1 = *unaff_retaddr;
      *puVar4 = 0;           // +0x00: left child
      puVar4[1] = 0;         // +0x04: right child
      puVar4[2] = 0;         // +0x08: parent
      puVar4[3] = 0;         // +0x0C: key
      puVar4[4] = uVar1;     // +0x10: value (or some data)
      *(char *)(puVar4 + 5) = (char)iVar6; // +0x14: color (red/black?)
      *root = (int)puVar4;
      *(int *)(this + 4) = *(int *)(this + 4) + 1; // increment node count
      return puVar4;
    }
    *root = 0;
    *(int *)(this + 4) = *(int *)(this + 4) + 1;
    return (undefined4 *)0x0;
  }
  
  // Traverse tree to find insertion point
  if (*key < *(uint *)(iVar6 + 0x10)) {
    // Go left
    puVar4 = (undefined4 *)BTree::insertNode(iVar6 + 8, key, value);
    if (puVar4[1] == 0) {
      puVar4[1] = *root;
    }
    piVar2 = *(int **)(*root + 8);
    if (piVar2 == (int *)0x0) {
      iVar6 = -1;
    }
    else {
      iVar6 = *piVar2;
    }
    piVar3 = *(int **)(*root + 0xc);
    if (piVar3 == (int *)0x0) {
      iVar5 = -1;
    }
    else {
      iVar5 = *piVar3;
    }
    if (iVar6 - iVar5 == 2) {
      // Balance: left-heavy case
      if (*key < (uint)piVar2[4]) {
        FUN_00859680(root);  // rotate right
        return puVar4;
      }
      FUN_008597e0(root);    // rotate left-right
      return puVar4;
    }
  }
  else {
    if (*key <= *(uint *)(iVar6 + 0x10)) {
      // Key already exists, update value
      *(undefined1 *)(iVar6 + 0x14) = *value;
      return (undefined4 *)*root;
    }
    // Go right
    puVar4 = (undefined4 *)BTree::insertNode(iVar6 + 0xc, key, value);
    if (puVar4[1] == 0) {
      puVar4[1] = *root;
    }
    piVar2 = *(int **)(*root + 0xc);
    if (piVar2 == (int *)0x0) {
      iVar6 = -1;
    }
    else {
      iVar6 = *piVar2;
    }
    piVar3 = *(int **)(*root + 8);
    if (piVar3 == (int *)0x0) {
      iVar5 = -1;
    }
    else {
      iVar5 = *piVar3;
    }
    if (iVar6 - iVar5 == 2) {
      // Balance: right-heavy case
      if ((uint)piVar2[4] < *key) {
        FUN_00859730(root);  // rotate left
        return puVar4;
      }
      FUN_00859800(root);    // rotate right-left
      return puVar4;
    }
  }
  FUN_00859120();  // some error/assertion handler
  return puVar4;
}