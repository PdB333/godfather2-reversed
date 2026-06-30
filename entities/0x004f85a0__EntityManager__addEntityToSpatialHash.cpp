// FUNC_NAME: EntityManager::addEntityToSpatialHash
undefined1 EntityManager::addEntityToSpatialHash(int this, int *hashTable)
{
  int iVar1;
  undefined4 in_EAX;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int unaff_FS_OFFSET;
  int local_10;
  int local_c;
  int iStack_8;
  
  local_10 = FUN_004f7a90(hashTable[1],in_EAX); // Get number of cells to check
  *(undefined1 *)hashTable = 0; // Clear result flag
  if (local_10 == 0) {
    return 0;
  }
  if (0 < local_10) {
    piVar8 = (int *)(this + 0x1c); // +0x1c: entity list pointer
    do {
      iVar6 = 0;
      if (0 < hashTable[4]) { // +0x10: existing cell count
        piVar2 = hashTable;
        do {
          piVar2 = piVar2 + 2;
          if (*piVar8 == *(int *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x24 + *piVar2)
             ) goto LAB_004f86df;
          iVar6 = iVar6 + 1;
        } while (iVar6 < hashTable[4]);
      }
      if (hashTable[4] < hashTable[1]) { // +0x04: max cells
        piVar2 = (int *)*piVar8;
        FUN_00519c80(&local_c); // Allocate cell
        iVar6 = local_c;
        if (local_c != 0) {
          iVar1 = **(int **)(unaff_FS_OFFSET + 0x2c);
          iVar7 = *(int *)(iVar1 + 8) + local_c;
          iVar3 = (**(code **)(*piVar2 + 4))(); // Get entity bounds
          *(int *)(iVar7 + 0x10) = iVar3;
          if (iVar3 != 0) {
            uVar4 = (**(code **)(*piVar2 + 8))(); // Get entity position
            *(undefined4 *)(iVar7 + 0x1c) = uVar4;
          }
          *(int **)(iVar7 + 0x24) = piVar2; // Store entity pointer
          puVar5 = (undefined4 *)(*(int *)(iVar1 + 8) + 8 + iVar6);
          *puVar5 = 0;
          puVar5[1] = 0;
          puVar5 = (undefined4 *)(*(int *)(iVar1 + 8) + iVar6);
          *puVar5 = *(undefined4 *)(this + 0x14); // +0x14: previous cell
          puVar5[1] = *(undefined4 *)(this + 0x18); // +0x18: next cell
          if (*(int *)(this + 0x14) != 0) {
            piVar2 = (int *)(*(int *)(this + 0x14) + 8 + *(int *)(iVar1 + 8));
            *piVar2 = iVar6;
            piVar2[1] = iStack_8;
          }
          *(int *)(this + 0x14) = iVar6;
          *(int *)(this + 0x18) = iStack_8;
          piVar2 = (int *)(*(int *)(iVar1 + 8) + 0x30 + iVar6);
          *piVar2 = *piVar2 + 1; // Increment cell reference count
          if (hashTable[4] == 0) {
            hashTable[4] = 1;
            hashTable[2] = iVar6; // +0x08: first cell
            hashTable[3] = iStack_8; // +0x0c: last cell
          }
          *(undefined1 *)hashTable = 1; // Set success flag
        }
      }
LAB_004f86df:
      piVar8 = piVar8 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return (char)*hashTable;
}