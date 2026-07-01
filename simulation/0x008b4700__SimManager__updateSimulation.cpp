// FUNC_NAME: SimManager::updateSimulation
void __fastcall SimManager::updateSimulation(int thisPtr)
{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puStack_10;
  int iStack_c;
  int iStack_8;
  
  // Check if the simulation is active and the game is not paused
  if ((*(int *)(DAT_01223484 + 8) != 0) && (cVar1 = FUN_00481620(), cVar1 != '\0')) {
    // Update the global time manager if available
    if ((*(int *)(DAT_01223484 + 0x30) != 0) && (*(int *)(DAT_01223484 + 8) != 0)) {
      piVar2 = (int *)(**(code **)(**(int **)(DAT_01223484 + 0x30) + 4))();
      (**(code **)(*piVar2 + 4))();
    }
    // If there are pending objects to process, process them
    if (*(int *)(thisPtr + 400) != 0) {
      FUN_008b3c40();
    }
    uVar6 = 0;
    // Iterate through all active simulation objects
    if (*(int *)(thisPtr + 0x1b0) != 0) {
      piVar2 = (int *)(thisPtr + 0x18c);
      do {
        // Get the current time step from the time manager
        if ((*(int *)(DAT_01223484 + 0x30) == 0) || (*(int *)(DAT_01223484 + 8) == 0)) {
          uVar3 = 0;
        }
        else {
          uVar3 = (**(code **)**(undefined4 **)(DAT_01223484 + 0x30))();
        }
        iVar4 = *(int *)(thisPtr + 0x194);
        // Resize the object array if needed
        if (*(int *)(thisPtr + 400) == iVar4) {
          if (iVar4 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = iVar4 * 2;
          }
          FUN_008b3980(iVar4);
        }
        puVar5 = (undefined4 *)(*piVar2 + *(int *)(thisPtr + 400) * 4);
        *(int *)(thisPtr + 400) = *(int *)(thisPtr + 400) + 1;
        if (puVar5 != (undefined4 *)0x0) {
          *puVar5 = uVar3;
        }
        // Call the update method on the simulation object
        (**(code **)**(undefined4 **)(*piVar2 + uVar6 * 4))();
        // Call the post-update method
        (**(code **)(**(int **)(*piVar2 + uVar6 * 4) + 0x3c))();
        // Notify the event system about the update
        FUN_008b3fb0(*(undefined4 *)(thisPtr + 0x60),uVar6,0);
        // Process any pending events from the event queue
        while ((iStack_c != 0 || (iStack_8 != 0))) {
          puVar5 = (undefined4 *)(*(code *)*puStack_10)();
          FUN_008b3bc0(puVar5[2],*puVar5);
          (*(code *)puStack_10[1])();
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(uint *)(thisPtr + 0x1b0));
    }
  }
  return;
}