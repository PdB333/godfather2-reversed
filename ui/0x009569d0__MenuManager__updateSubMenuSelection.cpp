// FUNC_NAME: MenuManager::updateSubMenuSelection
void __thiscall MenuManager::updateSubMenuSelection(int this, int param_2)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  iVar2 = *(int *)(this + 0x70); // +0x70: subMenuCount
  if ((iVar2 < 1) ||
     (iVar2 = (param_2 + iVar2 + *(int *)(this + 0x74)) % iVar2, // +0x74: currentSubMenuIndex
     iVar2 == *(int *)(this + 0x74))) {
    puVar1 = &DAT_011301f8; // no change, use default data
  }
  else {
    *(int *)(this + 0x74) = iVar2; // update current sub-menu index
    (**(code **)(**(int **)(this + 0x54 + *(int *)(this + 0x6c) * 4) + 0x78))(iVar2); // call sub-menu's select function
    FUN_005a04a0("UpdateSubMenu",0,&DAT_00d8c174,0); // log sub-menu update
    puVar1 = &DAT_011302b0; // updated data
  }
  local_c = *puVar1;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0); // likely a string copy or assignment
  return;
}