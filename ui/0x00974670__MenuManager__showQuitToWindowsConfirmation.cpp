// FUNC_NAME: MenuManager::showQuitToWindowsConfirmation
void __fastcall MenuManager::showQuitToWindowsConfirmation(int *this)
{
  int iVar1;
  
  // Set flag at +0x66 bit 0 (likely indicating a menu is active or blocking)
  *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) | 1;
  
  // Call virtual function at vtable+0xc (likely onShow or onActivate)
  (**(code **)(*this + 0xc))();
  
  // Set flag at +0x66 bit 1 (additional state)
  *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) | 2;
  
  // Broadcast "MenuHide" event to hide current menu
  FUN_005a04a0("MenuHide", 0, &DAT_00d8f604, 0);
  
  // Allocate a new dialog/menu object (0xf0 = 240 bytes)
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    // Initialize the dialog object
    iVar1 = FUN_00982280(0);
  }
  
  // Set the confirmation message text (localized string key)
  FUN_00981eb0("$select_menu_quit_to_windows_confirmation");
  
  // Set dialog type to 2 (likely confirmation dialog)
  *(undefined4 *)(iVar1 + 0xc) = 2;
  
  // Set callback function pointer at +0x14 (address of confirmation handler)
  *(undefined1 **)(iVar1 + 0x14) = &LAB_009745e0;
  
  // Show the dialog
  FUN_00982e10();
  return;
}