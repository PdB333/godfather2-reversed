// Xbox PDB: EARS_Apt_UIMobfaceMenu_HandleInput
// FUNC_NAME: PlayerActionableTargetSM::handleActionInput
undefined4 __thiscall PlayerActionableTargetSM::handleActionInput(int thisPtr, int actionId)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = FUN_00466840(); // likely getSelectActionId()
  if (actionId == iVar2) {
    pcVar4 = "Select";
  }
  else {
    iVar2 = FUN_00466860(); // likely getMoveBackActionId()
    if (actionId != iVar2) goto switchD_0091169b_switchD;
    if (*(char *)(thisPtr + 0x2ed) != '\0') { // +0x2ed: some flag (e.g., bCanMoveBack)
      return 1;
    }
    pcVar4 = "MoveBack";
  }
  FUN_005a04a0(pcVar4,0,&DAT_00d83ad0,0); // likely playAnimation or sendInputEvent
  FUN_00911050(); // likely updateState()
switchD_0091169b_switchD:
  switch(actionId) {
  case 0:
  case 2:
  case 4:
    return 1;
  default:
    return 0;
  case 6:
    FUN_005a04a0("MoveLeft",0,&DAT_00d83ad0,0);
    return 0;
  case 7:
    FUN_005a04a0("MoveRight",0,&DAT_00d83ad0,0);
    return 0;
  case 8:
    FUN_005a04a0("MoveUp",0,&DAT_00d83ad0,0);
    return 0;
  case 9:
    FUN_005a04a0("MoveDown",0,&DAT_00d83ad0,0);
    return 0;
  case 10:
    break;
  case 0xc:
    FUN_005a04a0("AdvancedOption",0,&DAT_00d83ad0,0);
    return 0;
  }
  iVar2 = (*(code *)**(undefined4 **)(thisPtr + 0x50))(); // +0x50: vtable pointer for some sub-object
  if (iVar2 != 0) {
    pcVar3 = (char *)(*(code *)**(undefined4 **)(thisPtr + 0x50))();
    pcVar4 = pcVar3 + 1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != pcVar4) {
      iVar2 = (*(code *)**(undefined4 **)(thisPtr + 0xd4))(); // +0xd4: another vtable pointer
      if (iVar2 != 0) {
        pcVar3 = (char *)(*(code *)**(undefined4 **)(thisPtr + 0xd4))();
        pcVar4 = pcVar3 + 1;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        if (pcVar3 != pcVar4) {
          return 0;
        }
      }
    }
  }
  FUN_00402050(&DAT_011302e8,0); // likely setGlobalFlag or clearInput
  FUN_009be990(); // likely exitCurrentState or popState
  return 0;
}