// FUNC_NAME: GodfatherGameManager::activatePlayerState
void __thiscall GodfatherGameManager::activatePlayerState(int thisPtr, int state)
{
  int iVar1;
  int *piVar2;
  
  if (state != 0) {
    if (state == 1) {
      DAT_01130590 = DAT_01130590 | 0x800;  // Set some game flag
    }
    else if (state == 2) {
      DAT_01130590 = DAT_01130590 | 0x8000;  // Set another game flag
    }
    else if (state == 3) {
      uVar3 = FUN_0089c630();  // Some state-related function
      FUN_00930930(uVar3);     // Process state transition
    }
  }
  
  // Check if player is not in certain states (bit 7 and bit 1 of +0x37c)
  if (((*(uint *)(thisPtr + 0x37c) >> 7 & 1) == 0) && ((*(uint *)(thisPtr + 0x37c) >> 1 & 1) == 0))
  {
    // Check global pointer and possibly active game state
    if ((DAT_012233a0 == 0) ||
       (((iVar1 = **(int **)(DAT_012233a0 + 4), iVar1 == 0 || (iVar1 == 0x1f30)) ||
        ((*(uint *)(iVar1 + 0x56c) >> 5 & 1) == 0)))) {
      FUN_0040c1f0(0xff000000, DAT_00d5c454, 1, 1);  // Set screen/fade color
    }
    
    // Check if some system is active
    if (DAT_01129c4c != 0) {
      FUN_0093c210();  // Update some system
      FUN_00983190();  // Update renderer/UI
    }
    
    // Check if there's an active callback/manager
    if (DAT_0112ebb0 != (undefined4 *)0x0) {
      if (*(int *)(thisPtr + 0x36c) != 0) {
        FUN_00454310(0);  // Clear/disable input
      }
      if (DAT_0112ebb0 != (undefined4 *)0x0) {
        (**(code **)*DAT_0112ebb0)(1);  // Call manager callback with param=1
      }
    }
    
    // Set bit 7 in state flags (+0x37c)
    *(uint *)(thisPtr + 0x37c) = *(uint *)(thisPtr + 0x37c) | 0x80;
    
    piVar2 = DAT_01129828;
    if ((*(uint *)(thisPtr + 0x37c) >> 3 & 1) != 0) {
      FUN_008f1e70(0x30);  // Schedule delayed callback
      (**(code **)(*piVar2 + 0x18))(FUN_008a43d0, thisPtr);  // Call state change handler
      return;
    }
    FUN_008a43d0(0, thisPtr);  // Direct state change handler call
  }
  return;
}