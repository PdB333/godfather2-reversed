// FUNC_NAME: UIButtonHandler::handleButton2Click
bool UIButtonHandler::handleButton2Click(char *buttonPath)
{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  undefined1 local_40 [64];
  
  iVar1 = 0x1e;
  bVar3 = true;
  pcVar2 = "/fopt/buttons/button_2/button";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar3 = *pcVar2 == *buttonPath;
    pcVar2 = pcVar2 + 1;
    buttonPath = buttonPath + 1;
  } while (bVar3);
  if (bVar3) {
    // Button path matches, trigger roll-out animation
    FUN_00910160(local_40, &DAT_00d796d4); // Likely format string or localization
    FUN_005a04a0("RollOutButton", 0, &DAT_00d8a0dc, 1, local_40); // Play animation event
  }
  return bVar3;
}