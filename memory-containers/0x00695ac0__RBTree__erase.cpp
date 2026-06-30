// FUNC_NAME: RBTree::erase

/* WARNING: Removing unreachable block (ram,0x00695c45) */
/* WARNING: Removing unreachable block (ram,0x00695c56) */
/* WARNING: Removing unreachable block (ram,0x00695c5f) */
/* WARNING: Removing unreachable block (ram,0x00695c62) */
/* WARNING: Removing unreachable block (ram,0x00695c52) */
/* WARNING: Removing unreachable block (ram,0x00695c70) */
/* WARNING: Removing unreachable block (ram,0x00695c81) */
/* WARNING: Removing unreachable block (ram,0x00695c8c) */
/* WARNING: Removing unreachable block (ram,0x00695c88) */
/* WARNING: Removing unreachable block (ram,0x00695c7c) */
/* WARNING: Removing unreachable block (ram,0x00695c8f) */

void __thiscall RBTree::erase(int this, undefined4 *result, undefined4 returnVal, int *node)
{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  undefined1 local_40 [4];
  uint local_3c;
  undefined4 local_2c;
  uint local_28;
  undefined **local_24;
  char *local_20;
  uint local_18;
  undefined4 local_8;
  uint local_4;
  
  // Check if the node is valid (non-null, at offset +0x29)
  if (*(char *)((int)node + 0x29) != '\0') {
    // Throw an exception: "invalid map/set<T> iterator"
    local_28 = 0xf;
    local_2c = 0;
    local_3c = local_3c & 0xffffff00;
    FUN_0043f9f0("invalid map/set<T> iterator", 0x1b);
    local_20 = "unknown";
    local_24 = &PTR_FUN_00da9810;
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    FUN_0043eeb0(local_40, 0, 0xffffffff);
    local_24 = &PTR_FUN_00da9834;
    if (DAT_0113d3a0 != (code *)0x0) {
      (*DAT_0113d3a0)(&local_24);
    }
    (*(code *)local_24[2])();
    std::_Throw((exception *)&local_24);
    local_24 = &PTR_FUN_00da9810;
    if (0xf < local_4) {
      FUN_009c8eb0(local_18);
    }
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    local_24 = &PTR_LAB_00e31044;
    if (0xf < local_28) {
      FUN_009c8eb0(local_3c);
    }
  }
  FUN_006941f0();
  piVar6 = (int *)*node;  // Get the left child of the node
  if (*(char *)((int)piVar6 + 0x29) == '\0') {
    if (*(char *)(node[2] + 0x29) == '\0') {
      piVar6 = (int *)node[2];  // Use right child if left is invalid?
    }
  }
  else {
    piVar6 = (int *)node[2];  // Use right child if left is invalid
  }
  piVar5 = (int *)node[1];  // Get the parent of the node
  if (*(char *)((int)piVar6 + 0x29) == '\0') {
    piVar6[1] = (int)piVar5;  // Set the parent of the replacement node
  }
  if (*(int **)(*(int *)(this + 4) + 4) == node) { // Check if node is root?
    *(int **)(*(int *)(this + 4) + 4) = piVar6;
  }
  else if ((int *)*piVar5 == node) {
    *piVar5 = (int)piVar6;  // Update left child of parent
  }
  else {
    piVar5[2] = (int)piVar6; // Update right child of parent
  }
  puVar1 = *(undefined4 **)(this + 4);
  if ((int *)*puVar1 == node) {
    piVar3 = piVar5;
    if (*(char *)((int)piVar6 + 0x29) == '\0') {
      piVar3 = (int *)FUN_00694030(piVar6);
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(this + 4);
  if (*(int **)(iVar2 + 8) == node) {
    if (*(char *)((int)piVar6 + 0x29) == '\0') {
      uVar4 = FUN_00694010(piVar6);
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if ((char)node[10] == '\x01') { // If the deleted node was RED
    if (piVar6 != *(int **)(*(int *)(this + 4) + 4)) {
      // Fix the red-black tree properties after deletion
      do {
        piVar3 = piVar5;
        if ((char)piVar6[10] != '\x01') break; // If the replacement node is BLACK
        piVar5 = (int *)*piVar3; // Get left child of sibling
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2]; // Get right child of sibling
          if ((char)piVar5[10] == '\0') {
            *(undefined1 *)(piVar5 + 10) = 1;
            *(undefined1 *)(piVar3 + 10) = 0;
            FUN_00694a30(piVar3);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0x29) == '\0') {
            if ((*(char *)(*piVar5 + 0x28) != '\x01') || (*(char *)(piVar5[2] + 0x28) != '\x01')) {
              if (*(char *)(piVar5[2] + 0x28) == '\x01') {
                *(undefined1 *)(*piVar5 + 0x28) = 1;
                *(undefined1 *)(piVar5 + 10) = 0;
                FUN_00693f00(piVar5);
                piVar5 = (int *)piVar3[2];
              }
              *(char *)(piVar5 + 10) = (char)piVar3[10];
              *(undefined1 *)(piVar3 + 10) = 1;
              *(undefined1 *)(piVar5[2] + 0x28) = 1;
              FUN_00694a30(piVar3);
              break;
            }
LAB_00695d64:
            *(undefined1 *)(piVar5 + 10) = 0;
          }
        }
        else {
          if ((char)piVar5[10] == '\0') {
            *(undefined1 *)(piVar5 + 10) = 1;
            *(undefined1 *)(piVar3 + 10) = 0;
            FUN_00693f00(piVar3);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0x29) == '\0') {
            if ((*(char *)(piVar5[2] + 0x28) == '\x01') && (*(char *)(*piVar5 + 0x28) == '\x01'))
            goto LAB_00695d64;
            if (*(char *)(*piVar5 + 0x28) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0x28) = 1;
              *(undefined1 *)(piVar5 + 10) = 0;
              FUN_00694a30(piVar5);
              piVar5 = (int *)*piVar3;
            }
            *(char *)(piVar5 + 10) = (char)piVar3[10];
            *(undefined1 *)(piVar3 + 10) = 1;
            *(undefined1 *)(*piVar5 + 0x28) = 1;
            FUN_00693f00(piVar3);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(this + 4) + 4));
    }
    *(undefined1 *)(piVar6 + 10) = 1; // Set the replacement node to BLACK
  }
  if (node[3] != 0) {
    (*(code *)node[6])(node[3]); // Call destructor if allocated
  }
  FUN_009c8eb0(node); // Deallocate node
  if (*(int *)(this + 8) != 0) {
    *(int *)(this + 8) = *(int *)(this + 8) + -1; // Decrement size
  }
  *result = returnVal;
  result[1] = node;
  return;
}