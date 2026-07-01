// FUNC_NAME: DonControlGadget::handleInputAction
undefined4 __thiscall DonControlGadget::handleInputAction(int this, int actionId)
{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  
  iVar3 = FUN_00466840(); // likely getActionId_Select or similar
  if (actionId == iVar3) {
    FUN_005a04a0("Select",0,&DAT_00d8c478,0); // playSound or sendEvent
    FUN_00958ee0(); // donControlGadget_selectAction
    return 0;
  }
  iVar3 = FUN_00466860(); // likely getActionId_Back
  if (actionId != iVar3) {
    switch(actionId) {
    case 0:
    case 2:
    case 4:
      goto switchD_009591e1_caseD_0;
    default:
      return 0;
    case 6:
      FUN_005a04a0("MoveLeft",0,&DAT_00d8c478,0);
      return 0;
    case 7:
      FUN_005a04a0("MoveRight",0,&DAT_00d8c478,0);
      return 0;
    case 8:
      FUN_005a04a0("MoveUp",0,&DAT_00d8c478,0);
      return 0;
    case 9:
      FUN_005a04a0("MoveDown",0,&DAT_00d8c478,0);
      return 0;
    case 10:
      // Check if there's a valid selection (via vtable at +0x84)
      iVar3 = (*(code *)**(undefined4 **)(this + 0x84))(); // getSelectedItem
      if (iVar3 != 0) {
        pcVar4 = (char *)(*(code *)**(undefined4 **)(this + 0x84))(); // getSelectedItemText
        pcVar1 = pcVar4 + 1;
        do {
          cVar2 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar2 != '\0');
        if (pcVar4 != pcVar1) {
          iVar3 = (*(code *)**(undefined4 **)(this + 0x108))(); // getSubItem
          if (iVar3 != 0) {
            pcVar4 = (char *)(*(code *)**(undefined4 **)(this + 0x108))(); // getSubItemText
            pcVar1 = pcVar4 + 1;
            do {
              cVar2 = *pcVar4;
              pcVar4 = pcVar4 + 1;
            } while (cVar2 != '\0');
            if (pcVar4 != pcVar1) {
              return 0;
            }
          }
        }
      }
      FUN_00402050(&DAT_011302e8,0); // clearSelection or reset
      FUN_009be990(); // donControlGadget_confirmAction
      return 0;
    }
  }
  // Back action
  if (*(char *)(this + 0x2ac) == '\0') { // check if canGoBack
    FUN_005a04a0("MoveBack",0,&DAT_00d8c478,0);
    FUN_00958ee0(); // donControlGadget_backAction
    FUN_00958fc0(); // donControlGadget_updateDisplay
    return 0;
  }
switchD_009591e1_caseD_0:
  return 1;
}