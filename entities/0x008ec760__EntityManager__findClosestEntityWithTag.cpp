// FUNC_NAME: EntityManager::findClosestEntityWithTag
undefined4 * __thiscall EntityManager::findClosestEntityWithTag(int thisPtr, undefined4 *outEntityId, int maxDistance, int *outDistance)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int local_14;
  int local_10;
  
  iVar6 = DAT_0122337c; // Global game state pointer
  *outEntityId = 0xfe16702f; // Invalid entity ID sentinel
  *outDistance = 4; // Initial max distance
  local_10 = 0;
  local_14 = thisPtr + 0x20; // +0x20: first entity list (e.g., active entities)
  do {
    iVar2 = **(int **)(local_14 + 4); // Get first entity in list
    while( true ) {
      iVar3 = *(int *)(local_14 + 4); // End of list sentinel
      if (local_14 == 0) {
        FUN_00b97aea(); // Crash/assert
      }
      if (iVar2 == iVar3) break;
      if (local_10 == 0) {
        // First pass: check if entity is valid (not destroyed)
        if (local_14 == 0) {
          FUN_00b97aea();
        }
        if (iVar2 == *(int *)(local_14 + 4)) {
          FUN_00b97aea();
        }
        uVar7 = FUN_004059b0(*(undefined4 *)(iVar2 + 0xc)); // Hash entity ID
        for (puVar4 = *(uint **)(*(int *)(iVar6 + 0x50) + (uVar7 % *(uint *)(iVar6 + 0x54)) * 4);
            puVar4 != (uint *)0x0; puVar4 = (uint *)puVar4[2]) {
          if (*puVar4 == uVar7) {
            if (((puVar4 != (uint *)0x0) && (puVar4[1] != 0)) && (*(int *)(puVar4[1] + 0x24) == 0))
            goto LAB_008ec821;
            break;
          }
        }
      }
      else {
LAB_008ec821:
        // Entity is valid, check distance
        if (local_14 == 0) {
          FUN_00b97aea();
        }
        if (iVar2 == *(int *)(local_14 + 4)) {
          FUN_00b97aea();
        }
        puVar5 = (undefined4 *)**(undefined4 **)(iVar2 + 0x10); // +0x10: entity transform
        iVar3 = (*(undefined4 **)(iVar2 + 0x10))[7]; // +0x1C: distance squared
        while (puVar5 != (undefined4 *)0x0) {
          piVar1 = puVar5 + 7;
          puVar5 = (undefined4 *)*puVar5;
          if (iVar3 < *piVar1) {
            iVar3 = *piVar1;
          }
        }
        if ((iVar3 <= maxDistance) && (iVar3 <= *outDistance)) {
          if (iVar2 == *(int *)(local_14 + 4)) {
            FUN_00b97aea();
          }
          *outEntityId = *(undefined4 *)(iVar2 + 0xc); // +0x0C: entity ID
          *outDistance = iVar3;
        }
      }
      FUN_008ea280(); // Advance to next entity in list
    }
    local_10 = local_10 + 1;
    local_14 = thisPtr + 0x2c; // +0x2C: second entity list (e.g., inactive/pooled)
    if (1 < local_10) {
      return param_2;
    }
  } while( true );
}