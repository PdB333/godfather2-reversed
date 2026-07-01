// FUNC_NAME: PlayerManager::checkCrewAvailabilityAndShowDialog
void PlayerManager::checkCrewAvailabilityAndShowDialog(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  // Check if the global game manager is valid
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // offset to PlayerManager
  }
  
  // Get the crew component from the player manager (+0x1ed8)
  iVar1 = *(int *)(iVar1 + 0x1ed8);
  
  // Check if crew component exists, is not a special value (0x48), and has crew members (+0x160)
  if (((iVar1 != 0) && (iVar1 != 0x48)) && (uVar4 = 0, *(int *)(iVar1 + 0x160) != 0)) {
    iVar3 = 0;
    do {
      // Check each crew member's availability status
      iVar2 = FUN_008c8170(); // likely crewMember->isAvailable()
      if (iVar2 < 6) { // some threshold (maybe 6 = busy/on mission)
        iVar3 = iVar3 + 1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(iVar1 + 0x160)); // loop through all crew members
    
    // If any crew member is available, show the crew dialog
    if (iVar3 != 0) {
      FUN_00985de0(1); // showCrewDialog(true)
      return;
    }
  }
  
  // No available crew members, show the "need crew" dialog
  iVar1 = FUN_009c8e50(0xf0); // allocate dialog object (size 0xF0)
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // initialize dialog
  }
  
  FUN_00981eb0("$mp_online_need_crew"); // set dialog text
  *(undefined4 *)(iVar1 + 0xc) = 1; // set dialog type/state
  FUN_00982400(1); // set dialog flags
  *(code **)(iVar1 + 0x14) = FUN_009854f0; // set callback function
  FUN_00982e10(); // show dialog
  return;
}