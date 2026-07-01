// FUNC_NAME: GodfatherGameManager::handleGameStateChange
void __fastcall GodfatherGameManager::handleGameStateChange(int thisPtr)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined8 local_9c;
  undefined4 local_94;
  undefined8 local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined8 local_80;
  undefined4 local_78;
  undefined4 local_74;
  undefined8 local_70;
  undefined4 local_68;
  undefined4 local_64;
  undefined8 local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined8 local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined8 local_40;
  undefined4 local_38;
  undefined4 local_34;
  undefined8 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_14;
  
  // Check if current game state is valid and not a specific state (0x48 = 72)
  if ((*(int *)(thisPtr + 100) != 0) && (*(int *)(thisPtr + 100) != 0x48)) {
    // Calculate offset from state pointer
    if (*(int *)(thisPtr + 100) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(thisPtr + 100) + -0x48;
    }
    // Get state type from offset +0x11c
    iVar2 = *(int *)(iVar2 + 0x11c);
    if (iVar2 == 8) {
      // State type 8: Simple state change
      if (*(int *)(thisPtr + 0x48) == 0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = (int *)(*(int *)(thisPtr + 0x48) + -0x48);
      }
      iVar2 = *piVar4;
      uVar3 = FUN_007254f0(); // Get some global object
      (**(code **)(iVar2 + 0x1c))(uVar3); // Call virtual function at offset 0x1c
    }
    else {
      if (iVar2 == 0x10) {
        // State type 16: Another simple state change
        if (*(int *)(thisPtr + 0x48) == 0) {
          piVar4 = (int *)0x0;
        }
        else {
          piVar4 = (int *)(*(int *)(thisPtr + 0x48) + -0x48);
        }
        if (*(int *)(thisPtr + 100) != 0) {
          iVar2 = *piVar4;
          uVar3 = FUN_007254f0();
          (**(code **)(iVar2 + 0x1c))(uVar3);
          return;
        }
        iVar2 = *piVar4;
        uVar3 = FUN_007254f0();
        (**(code **)(iVar2 + 0x1c))(uVar3);
        return;
      }
      if (iVar2 == 0x20) {
        // State type 32: Complex state change with data
        local_84 = 0;
        local_74 = 0;
        local_64 = 0;
        local_54 = _DAT_00d5780c; // Global data reference
        cVar1 = FUN_00725280(&local_90); // Initialize some structure
        if (cVar1 == '\0') {
          // Initialization failed, set error flag
          *(uint *)(thisPtr + 0x6c) = *(uint *)(thisPtr + 0x6c) | 4;
          return;
        }
        local_44 = 0;
        local_34 = 0;
        local_24 = 0;
        local_14 = _DAT_00d5780c;
        // Copy structure data
        local_9c = local_60;
        local_40 = local_80;
        local_48 = local_88;
        local_94 = local_58;
        local_50 = local_90;
        local_38 = local_78;
        local_30 = local_70;
        local_28 = local_68;
        if (*(int *)(thisPtr + 0x48) == 0) {
          piVar4 = (int *)0x0;
        }
        else {
          piVar4 = (int *)(*(int *)(thisPtr + 0x48) + -0x48);
        }
        // Call virtual function with structure data
        (**(code **)(*piVar4 + 0x1c))(&local_9c);
        if (*(int *)(thisPtr + 0x48) != 0) {
          (**(code **)(*(int *)(*(int *)(thisPtr + 0x48) + -0x48) + 0x20))(&local_54);
          return;
        }
        (**(code **)(iRam00000000 + 0x20))(&local_54);
        return;
      }
    }
  }
  return;
}