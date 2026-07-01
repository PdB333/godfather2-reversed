// FUNC_NAME: OnlineMenu::showQuitConfirmation
void OnlineMenu::showQuitConfirmation(void)
{
  int menu;
  
  menu = FUN_009c8e50(0xf0); // Allocate menu object (0xf0 bytes)
  if (menu == 0) {
    menu = 0;
  }
  else {
    menu = FUN_00982280(0); // Initialize menu with type 0 (confirmation dialog)
  }
  FUN_00981eb0("$mp_online_quit_confirmation"); // Set localization string key
  *(undefined4 *)(menu + 0xc) = 2; // +0x0C: menu type = 2 (confirmation)
  *(undefined1 **)(menu + 0x14) = &LAB_00964290; // +0x14: callback function pointer
  FUN_00982e10(); // Show/display the menu
  return;
}