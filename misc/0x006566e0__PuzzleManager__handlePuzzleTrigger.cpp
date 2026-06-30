// FUNC_NAME: PuzzleManager::handlePuzzleTrigger
void PuzzleManager::handlePuzzleTrigger(void)

{
  code *pcVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  undefined1 local_114 [8];
  undefined1 local_10c [8];
  char local_104 [260];
  
  FUN_0064b9e0(0x40,local_10c);
  FUN_0064b9e0(0x40,local_114);
  piVar3 = (int *)FUN_00655130(); // Get puzzle manager instance
  if ((piVar3 != (int *)0x0) && ((piVar3[0x6d] == 1 || (piVar3[0x6d] == 4)))) { // +0x1B4 state check
    cVar2 = FUN_006549b0(); // Check if puzzle is active
    if (cVar2 == '\\0') {
      cVar2 = FUN_006549b0(); // Double check
      if (cVar2 == '\\0') {
        FUN_0064c6b0(local_104); // Get current level name
        iVar4 = 7;
        bVar7 = true;
        pcVar5 = local_104;
        pcVar6 = "Puzzle";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        } while (bVar7);
        if ((bVar7) && (*(char *)((int)piVar3 + 0x132) == '\\0')) { // +0x132 puzzle not yet triggered
          *(undefined1 *)((int)piVar3 + 0x132) = 1; // Mark puzzle as triggered
          piVar3[0x67] = 0; // +0x19C reset timer
          piVar3[0x6d] = 1; // +0x1B4 set state to active
          FUN_00654a70((int)piVar3 + 0x133); // Initialize puzzle data at +0x133
          FUN_00655960(); // Play puzzle start sound
          return;
        }
        pcVar1 = *(code **)(*piVar3 + 0xc); // vtable +0xC = onPuzzleFailed
        piVar3[0x6d] = 6; // +0x1B4 set state to failed
        (*pcVar1)(2,local_104); // Call onPuzzleFailed(2, levelName)
        FUN_006550d0(); // Cleanup puzzle resources
      }
    }
  }
  return;
}