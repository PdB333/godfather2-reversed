// FUNC_NAME: SimManager::resetSimulation
void __thiscall SimManager::resetSimulation(int param_1, int param_2)
{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  
  if (param_2 != 0) {
    // Clear all objects from simulation
    FUN_008c6ab0(param_1);
  }
  if (*(int *)(param_1 + 0xc0) != 0) {
    // Release audio resources
    FUN_0084a730(*(undefined4 *)(param_1 + 0x40));
  }
  *(undefined4 *)(param_1 + 0x74) = 0;
  // Update simulation state
  FUN_006b2f70();
  if (*(int *)(param_1 + 0x78) == 0) {
    // Destroy all objects in the list
    for (iVar3 = *(int *)(param_1 + 0x68); iVar3 != 0; iVar3 = iVar3 + -1) {
      FUN_006b5c50(0);
    }
  }
  else {
    // Process objects in the array
    iVar3 = *(int *)(param_1 + 0xac);
    while (iVar3 = iVar3 + -1, -1 < iVar3) {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0xa8) + iVar3 * 4);
      cVar2 = FUN_00791230();
      if (cVar2 == '\0') {
        // Remove object from simulation
        FUN_006b56a0(iVar3);
      }
      else {
        // Destroy object
        FUN_006b5c50(uVar1);
      }
    }
  }
  *(undefined4 *)(param_1 + 0x6c) = 0;
  // Update simulation state
  FUN_006b2f70();
  iVar3 = *(int *)(param_1 + 0x40);
  *(int *)(param_1 + 0x3c) = iVar3;
  *(undefined4 *)(param_1 + 0x40) = 0;
  if (iVar3 == 0x637b907) {
    if (*(int *)(param_1 + 0xc4) == 0) {
      // Get default simulation speed
      iVar3 = FUN_0084b430(*(undefined4 *)(param_1 + 0x38));
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar3 + 0x14);
    }
    else if (*(int *)(param_1 + 0xc4) == 1) {
      // Get simulation speed for paused state
      iVar3 = FUN_0084b400(*(undefined4 *)(param_1 + 0x38));
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar3 + 0x18);
    }
  }
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x60);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x60);
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) & 0xf7ffffff;
  return;
}