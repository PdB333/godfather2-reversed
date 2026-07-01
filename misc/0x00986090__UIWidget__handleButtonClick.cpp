// FUNC_NAME: UIWidget::handleButtonClick
undefined4 __thiscall UIWidget::handleButtonClick(int this, byte *param_2)
{
  byte bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  bool bVar6;
  byte local_64 [100];
  
  pcVar5 = "@/slct/buttons/button_2/button";
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = param_2;
  do {
    pcVar5 = (char *)((byte *)pcVar5 + 1);
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pcVar5 == *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar6);
  if (bVar6) {
    uVar2 = FUN_00466860(); // likely getInputManager or similar
    FUN_005bf350(uVar2);    // likely processButtonPress
    return 1;
  }
  // Build path string for current menu item index (stored at +0x64)
  FUN_00973f60(local_64, "/slct/pause_mc/menu_items_anim/menu_stub/menu_%d/shared_menu_item/item",
               *(undefined4 *)(this + 100)); // +0x64: menuItemIndex
  pbVar3 = local_64;
  do {
    bVar1 = *pbVar3;
    bVar6 = bVar1 < *param_2;
    if (bVar1 != *param_2) {
LAB_00986110:
      iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_00986115;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar6 = bVar1 < param_2[1];
    if (bVar1 != param_2[1]) goto LAB_00986110;
    pbVar3 = pbVar3 + 2;
    param_2 = param_2 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_00986115:
  if (iVar4 == 0) {
    FUN_00986020(); // handleMenuItemClick
    return 1;
  }
  return 0;
}