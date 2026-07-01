// FUNC_NAME: OnlineMenu::showDonModeConfirmation
void OnlineMenu::showDonModeConfirmation(bool isDonMode)
{
    int menuHandle;
    char* confirmText;
    
    menuHandle = FUN_009c8e50(0xf0); // Allocate menu with 0xf0 bytes
    if (menuHandle == 0) {
        menuHandle = 0;
    }
    else {
        menuHandle = FUN_00982280(0); // Initialize menu with 0 options
    }
    
    confirmText = "$mp_online_menu_confirm_don_mode";
    if (isDonMode == false) {
        confirmText = "$mp_join_game_as_don";
    }
    
    FUN_00981eb0(confirmText); // Set menu title text
    *(undefined4 *)(menuHandle + 0xc) = 0; // +0x0C: menu option count
    FUN_00981e70("$mp_online_menu_yes", 0, 0); // Add "Yes" button at index 0
    FUN_00981e70("$mp_online_menu_no", 1, 0);  // Add "No" button at index 1
    *(undefined1 **)(menuHandle + 0x14) = &LAB_00971ec0; // +0x14: callback function pointer
    DAT_011308ed = isDonMode; // Store don mode flag
    *(char **)(menuHandle + 0x10) = &DAT_011308ed; // +0x10: pointer to callback data
    FUN_00982e10(); // Show/activate the menu
    return;
}