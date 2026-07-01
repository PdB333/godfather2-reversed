// FUNC_NAME: UIHudMinimapMarkerManager::handleButtonPress
undefined4 __thiscall UIHudMinimapMarkerManager::handleButtonPress(int this, byte *buttonName)
{
  byte bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  byte local_40 [64];
  
  if (*(char *)(this + 0x186) != '\0') {
    *(undefined1 *)(this + 0x186) = 0;
    return 1;
  }
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/tuto/buttons/button_2/button";
  pbVar5 = buttonName;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    uVar2 = FUN_00466860(); // likely getTutorialManager()
    FUN_005bf350(uVar2); // likely TutorialManager::skipTutorial()
    return 1;
  }
  FUN_00910160(local_40, "/tuto/mainmenu/menu/item_%d/menu_item/item", *(undefined4 *)(this + 0x5c));
  pbVar3 = local_40;
  do {
    bVar1 = *pbVar3;
    bVar6 = bVar1 < *buttonName;
    if (bVar1 != *buttonName) {
LAB_009902a4:
      iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_009902a9;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar6 = bVar1 < buttonName[1];
    if (bVar1 != buttonName[1]) goto LAB_009902a4;
    pbVar3 = pbVar3 + 2;
    buttonName = buttonName + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_009902a9:
  if (iVar4 == 0) {
    uVar2 = FUN_00466840(); // likely getMainMenuManager()
    FUN_005bf350(uVar2); // likely MainMenuManager::selectItem()
    return 1;
  }
  return 0;
}