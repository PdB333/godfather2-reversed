// FUNC_NAME: MenuManager::showQuitToWindowsConfirmation
void __fastcall MenuManager::showQuitToWindowsConfirmation(int *this)
{
  int iVar1;
  
  // Set flag bit 0 at offset +0x34 (ushort at +0x1a from int*)
  *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) | 1;
  
  // Call virtual function at vtable+0xc (likely some initialization/state change)
  (**(code **)(*this + 0xc))();
  
  // Set flag bit 1 at offset +0x34
  *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) | 2;
  
  // Hide the menu (likely a UI function)
  FUN_005a04a0("MenuHide", 0, &DAT_00d873d4, 0);
  
  // Allocate a dialog/menu object (0xf0 = 240 bytes)
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    // Initialize the dialog with parameter 0
    iVar1 = FUN_00982280(0);
  }
  
  // Set the confirmation text
  FUN_00981eb0("$select_menu_quit_to_windows_confirmation");
  
  // Set dialog type to 2 (confirmation dialog)
  *(undefined4 *)(iVar1 + 0xc) = 2;
  
  // Set callback function pointer at +0x14
  *(undefined1 **)(iVar1 + 0x14) = &LAB_00985ab0;
  
  // Show the dialog
  FUN_00982e10();
  return;
}