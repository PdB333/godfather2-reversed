// FUNC_NAME: BinarySearchTree::removeNode
void __thiscall BinarySearchTree::removeNode(undefined4 *this, uint *key)
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  
  iVar3 = this[1]; // +0x04: depth/height of tree
  puVar5 = (uint *)*this; // +0x00: root node
  if (-1 < iVar3) {
    do {
      puVar7 = *(uint **)(puVar5[2] + iVar3 * 4); // +0x08: child array at current depth
      if (puVar7 != (uint *)0x0) {
        puVar6 = puVar7;
        do {
          puVar7 = puVar6;
          if (*key <= *puVar6) break; // Compare keys
          puVar7 = *(uint **)(puVar6[2] + iVar3 * 4); // Traverse right child
          puVar5 = puVar6;
          puVar6 = puVar7;
        } while (puVar7 != (uint *)0x0);
      }
      iVar3 = iVar3 + -1;
      *(uint **)(this[5] + 4 + iVar3 * 4) = puVar5; // +0x14: path stack
    } while (-1 < iVar3);
    if ((puVar7 != (uint *)0x0) && (*puVar7 == *key)) {
      uVar4 = 0;
      do {
        iVar2 = *(int *)(*(int *)(this[5] + uVar4 * 4) + 8); // +0x08: child array of node on path
        iVar3 = uVar4 * 4;
        if (*(uint **)(iVar2 + uVar4 * 4) != puVar7) break; // Check if this is the node to remove
        iVar1 = uVar4 * 4;
        uVar4 = uVar4 + 1;
        *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(puVar7[2] + iVar1); // Replace child pointer
      } while (uVar4 <= (uint)this[1]); // +0x04: depth
      FUN_009c8f10(puVar7[2]); // Free child array
      FUN_009c8eb0(puVar7); // Free node
      this[4] = this[4] + -1; // +0x10: decrement node count
    }
  }
  return;
}