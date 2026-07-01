// FUNC_NAME: UIHudMinimapMarkerManager::updateSelectItem
void UIHudMinimapMarkerManager::updateSelectItem(void)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = DAT_01129930;
  if (DAT_01129930 != 0) {
    puVar1 = (undefined4 *)(DAT_01129930 + 0xcc);  // +0xCC: some pointer field
    puVar2 = (undefined4 *)(DAT_01129930 + 200);    // +0xC8: another pointer field
    uVar3 = *(undefined4 *)(DAT_01129930 + 0xc4);    // +0xC4: backup value
    *(undefined4 *)(DAT_01129930 + 0xc4) = 0;        // Clear the field
    FUN_0095fbc0(0,*puVar2,*puVar1);                  // Call internal update/minimap function
    FUN_005a04a0("UpdateSelectItem",0,&DAT_00d8cdec,0); // Log/fire event "UpdateSelectItem"
    *(undefined4 *)(iVar4 + 0xc4) = uVar3;            // Restore the backup value
    FUN_0095e7d0(0);                                  // Post-update processing
  }
  return;
}