// FUNC_NAME: UIStateManager::showQuitConfirmDialog
void UIStateManager::showQuitConfirmDialog(void)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate 0xF0 bytes for a UI dialog object
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // construct the dialog object (likely a UI dialog base)
  }
  FUN_00981eb0("$ui_fe_app_quit_confirm"); // set the dialog text to localized string for quit confirmation
  *(undefined4 *)(iVar1 + 0xc) = 2; // set dialog type/state to 2 (e.g., confirm dialog)
  *(undefined1 **)(iVar1 + 0x14) = &LAB_00931980; // set callback function pointer (e.g., onConfirm)
  FUN_00982e10(); // show/push the dialog onto the UI stack
  return;
}