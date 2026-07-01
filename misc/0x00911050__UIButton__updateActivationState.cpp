// FUNC_NAME: UIButton::updateActivationState
void __fastcall UIButton::updateActivationState(int this)
{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  // Check if global UI manager is active and visible
  if ((DAT_01130004 != 0) && (*(char *)(DAT_01130004 + 0x48) != '\0')) {
    // Determine button state string based on +0x2ed flag (isActive?)
    if (*(char *)(this + 0x2ed) == '\0') {
      pcVar4 = "ActivateButton";
    }
    else {
      pcVar4 = "DeactivateButton";
    }
    // Send UI event (likely to UI system)
    FUN_005a04a0(pcVar4, 0, &DAT_00d83ad0, 1, &DAT_00e36da0);
  }
  
  // Get text string from vtable at +0x50 (likely getText or getLabel)
  iVar2 = (*(code *)**(undefined4 **)(this + 0x50))();
  if (iVar2 != 0) {
    pcVar3 = (char *)(*(code *)**(undefined4 **)(this + 0x50))();
    pcVar4 = pcVar3 + 1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != pcVar4) {
      // Get action string from vtable at +0xd4 (likely getAction or getCommand)
      iVar2 = (*(code *)**(undefined4 **)(this + 0xd4))();
      if (iVar2 != 0) {
        pcVar3 = (char *)(*(code *)**(undefined4 **)(this + 0xd4))();
        pcVar4 = pcVar3 + 1;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        if (pcVar3 != pcVar4) {
          // If both text and action are non-empty, deactivate button
          FUN_005a04a0("DeactivateButton", 0, &DAT_00d83ad0, 1, &DAT_00d796d0);
          return;
        }
      }
    }
  }
  // Otherwise activate button
  FUN_005a04a0("ActivateButton", 0, &DAT_00d83ad0, 1, &DAT_00d796d0);
  return;
}