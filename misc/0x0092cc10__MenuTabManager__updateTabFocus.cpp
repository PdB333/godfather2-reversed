// FUNC_NAME: MenuTabManager::updateTabFocus
void __thiscall MenuTabManager::updateTabFocus(int this, int param_2)
{
  int iVar1;
  int uVar2;
  int local_c[3];
  
  if (*(int *)(this + 0x5c) == 4) {
    (**(code **)(*DAT_011304fc + 0x2c))();
  }
  else if (*(int *)(this + 0x5c) == 5) {
    FUN_0092c300();
  }
  // Log exit tab event
  FUN_005a04a0("ExitTab",0,&DAT_00d88708,0);
  
  // Calculate new tab index based on direction (param_2 = -1 for left, +1 for right)
  iVar1 = DAT_00e565fc; // Number of tabs in normal state
  if (*(int *)(this + 0x50) != 0) {
    iVar1 = DAT_00e565f8; // Number of tabs in submenu state
  }
  iVar1 = (*(int *)(this + 0x58) + iVar1 + param_2) % iVar1;
  *(int *)(this + 0x58) = iVar1; // +0x58 = currentTabIndex
  
  // Get new tab ID from appropriate lookup table
  if (*(int *)(this + 0x50) == 0) { // +0x50 = isSubmenu
    uVar2 = *(int *)(&DAT_00e565e4 + iVar1 * 4); // Normal tab table
  }
  else {
    uVar2 = *(int *)(&DAT_00e565d0 + iVar1 * 4); // Submenu tab table
  }
  *(int *)(this + 0x5c) = uVar2; // +0x5c = currentTabId
  
  local_c[0] = DAT_01130208;
  local_c[1] = 0;
  local_c[2] = 0;
  FUN_00408a00(local_c,0); // Clear input state?
  FUN_00954870(); // Update UI elements?
  
  // Register update/draw callbacks for tab content
  this = this + 0x14; // +0x14 = tabContentList
  FUN_005c0d50(this,&LAB_005bfc10,0); // Register draw callback
  FUN_005c0d50(this,&LAB_0092cb80,0); // Register update callback
  FUN_005c0d50(this,&LAB_005bfbe0,0); // Register input callback
  return;
}