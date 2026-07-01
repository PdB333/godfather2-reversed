// Xbox PDB: EARS_Apt_UITutorials_HandleInput
// FUNC_NAME: PresentationManager::handleInputAction
int __thiscall PresentationManager::handleInputAction(int *this, int action)
{
  int iVar1;
  int iVar2;
  char *sVar3;
  
  // Check if action is confirm (1) and a cutscene or movie is playing (+0x61 flag)
  if (action == 1) {
    if (*(char *)(this + 0x61) != '\0') {
      return 1;
    }
  }
  // If a movie is active, handle specific actions
  else if (*(char *)(this + 0x61) != '\0') {
    iVar1 = FUN_00466840(); // GetActionAccept() or similar
    if (action == iVar1) {
      // Check if we are in the main game loop
      iVar1 = FUN_00683410(*(undefined4 *)(DAT_0112980c + 4)); // Get current module
      iVar2 = FUN_00683280("GameMainLoop"); // Hash lookup for string
      if (iVar1 == iVar2) {
        // Close the movie viewer / set flag
        FUN_00402050(&DAT_011302c8, 0); // Set some global flag to false
        FUN_005a04a0("GetMovieEvent", 0, &DAT_00d91b68, 0); // Fire event
        FUN_00408980(this + 0x5f, this + 0x3b); // Copy/move memory (maybe restore state)
        FUN_00402050(this + 0x5f, 0); // Clear some flag
        FUN_005c1ad0(); // UpdateUI() or render related
        FUN_005c1ad0(); // Double update (maybe double buffer)
        *(char *)(this + 0x61) = '\0'; // Clear movie flag
      }
      // Mark something as handled
      *(char *)(DAT_01129a74 + 0x3a2) = '\0';
      return 0;
    }
    // Handle back/cancel action
    iVar1 = FUN_00466860(); // GetActionBack() or similar
    if (action == iVar1) {
      // Call virtual function for cancel behavior
      (*(code **)(*this + 0x2c))(); // VTable offset 0x2c: onCancel or onClose
      FUN_00402050(&DAT_01130310, 0); // Set another global flag
      return 0;
    }
    // Handle navigation actions (MoveUp / MoveDown)
    if (action == 8) {
      sVar3 = "MoveUp";
    }
    else {
      if (action != 9) {
        return 0;
      }
      sVar3 = "MoveDown";
    }
    FUN_005a04a0(sVar3, 0, &DAT_00d91b68, 0);
    FUN_00402050(&DAT_011301c0, 0);
  }
  return 0;
}