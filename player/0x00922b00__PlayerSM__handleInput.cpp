// FUNC_NAME: PlayerSM::handleInput
undefined4 __thiscall PlayerSM::handleInput(int thisPtr, int inputAction)
{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  iVar2 = FUN_00466840(); // likely getCurrentGameState()
  if (inputAction != iVar2) {
    iVar2 = FUN_00466860(); // likely getCurrentGameMode()
    if (inputAction == iVar2) {
      cVar1 = FUN_00957d00(); // likely isPlayerInCutscene()
      if (cVar1 != '\0') {
        local_c = DAT_01130310; // some global string or ID
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c,0); // likely playSound()
        return 0;
      }
      local_8 = 0;
      local_4 = 0;
      local_c = DAT_011302c0; // another global string or ID
      FUN_00408a00(&local_c,0); // likely playSound()
      return 0;
    }
    switch(inputAction) {
    case 0: // e.g., ACTION_NONE
    case 3: // e.g., ACTION_MOVE
    case 5: // e.g., ACTION_JUMP
      return 1;
    case 8: // e.g., ACTION_ATTACK
      FUN_00921de0(0xffffffff); // likely startAttack(-1)
      break;
    case 9: // e.g., ACTION_SPECIAL
      FUN_00921de0(1); // likely startAttack(1)
      return 0;
    case 10: // e.g., ACTION_INTERACT
      if ((*(int *)(thisPtr + 0x58) == 0) && (*(char *)(thisPtr + 0xa1) != '\0')) {
        FUN_00922a60(); // likely interactWithObject()
        return 0;
      }
      break;
    case 0xc: // e.g., ACTION_RELOAD
      FUN_00922e20(7,0); // likely reloadWeapon(7,0)
      return 0;
    }
    return 0;
  }
  if ((*(int *)(thisPtr + 0x58) == 1) && (*(char *)(thisPtr + 0xa0) != '\0')) {
    FUN_00922490(); // likely enterVehicle()
    return 0;
  }
  local_c = DAT_011302c0; // another global string or ID
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0); // likely playSound()
  return 0;
}