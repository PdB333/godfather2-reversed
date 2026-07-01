// Xbox PDB: EARS_Apt_UISelectMenu_SMAction_QuitGame
// FUNC_NAME: GameMenu::handleQuitConfirmation
// Address: 0x00985de0
// Role: Handles the quit confirmation dialog within the main menu system.
// Called when the player selects "Quit Game" from the options menu.
void __thiscall GameMenu::handleQuitConfirmation(int *thisMenu, int param_2)
{
    int iVar1;

    // Set flag bit 0 at offset +0x1a (likely a "dirty" or "active update" flag)
    *(ushort *)(thisMenu + 0x1a) = *(ushort *)(thisMenu + 0x1a) | 1;
    
    // Call virtual function at vtable+0xc (likely OnShow or PreUpdate)
    (**(code **)(*thisMenu + 0xc))();
    
    // Set flag bit 1 at offset +0x1a (e.g., "visible" or "enabled")
    *(ushort *)(thisMenu + 0x1a) = *(ushort *)(thisMenu + 0x1a) | 2;
    
    // Hide the current menu (probably hide the options menu)
    // FUN_005a04a0 is a menu visibility/hide function
    FUN_005a04a0("MenuHide", 0, &DAT_00d873d4, 0);
    
    // Try to get/create a dialog object with ID 0xf0 (240)
    iVar1 = FUN_009c8e50(0xf0);
    if (iVar1 == 0) {
        iVar1 = 0;
    }
    else {
        // If object exists, initialize it with a specific parameter (0)
        iVar1 = FUN_00982280(0);
    }
    
    // Load localized string for the quit confirmation dialog
    FUN_00981eb0("$select_menu_quit_confirmation");
    
    // Set up dialog structure:
    // +0x0c: type/state (2 = confirmation dialog)
    *(undefined4 *)(iVar1 + 0xc) = 2;
    
    // +0x14: function pointer (callback for "Yes" action)
    *(undefined1 **)(iVar1 + 0x14) = &LAB_00985d10;
    
    // +0x10: user data (param_2, likely context or callback ID)
    *(undefined4 *)(iVar1 + 0x10) = param_2;
    
    // Show the dialog (activate it)
    FUN_00982e10();
    
    return;
}