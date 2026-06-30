// FUNC_NAME: EntityManager::filterEntitiesByType
int* EntityManager::filterEntitiesByType(int thisPtr, int* outArray)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  uint entityIndex;
  uint entityCount;
  
  piVar7 = (int *)0x0;
  *outArray = 0;
  outArray[1] = 0;
  outArray[2] = 0;
  piVar3 = (int *)FUN_00ad8d40(); // Get some global manager
  if (piVar3 != (int *)0x0) {
    piVar7 = (int *)(**(code **)(*piVar3 + 0x34))(); // Get entity manager
  }
  piVar3 = (int *)(**(code **)(*piVar7 + 0x24))(); // Get type registry
  iVar6 = *(int *)(thisPtr + 0xc); // +0xC: entity type filter
  uVar4 = (**(code **)(*piVar3 + 0x3c))(0); // Get number of registered types
  entityCount = 0;
  if (iVar6 != 0) {
    do {
      uVar2 = *(undefined4 *)(*(int *)(thisPtr + 0x14) + entityCount * 4); // +0x14: entity list
      uVar8 = 0;
      if (uVar4 != 0) {
        do {
          piVar7 = (int *)(**(code **)(*piVar3 + 0x24))(uVar8); // Get type at index
          iVar6 = *(int *)(uVar4 + 0x104); // +0x104: type ID
          iVar5 = (**(code **)(*piVar7 + 0xc))(); // Get entity type ID
          if (iVar5 == iVar6) goto LAB_004cbb2c; // Match found, skip adding
          uVar8 = uVar8 + 1;
        } while (uVar8 < uVar4);
      }
      iVar6 = outArray[2]; // Capacity
      if (outArray[1] == iVar6) { // Need to grow array
        if (iVar6 == 0) {
          iVar6 = 1;
        }
        else {
          iVar6 = iVar6 * 2;
        }
        FUN_004cbc70(iVar6); // Grow array
      }
      puVar1 = (undefined4 *)(*outArray + outArray[1] * 4);
      outArray[1] = outArray[1] + 1; // Increment count
      if (puVar1 != (undefined4 *)0x0) {
        *puVar1 = uVar2; // Add entity to output
      }
LAB_004cbb2c:
      entityCount = entityCount + 1;
    } while (entityCount < uVar4);
  }
  return outArray;
}