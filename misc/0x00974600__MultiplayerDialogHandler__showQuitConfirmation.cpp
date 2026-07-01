// FUNC_NAME: MultiplayerDialogHandler::showQuitConfirmation
void __fastcall MultiplayerDialogHandler::showQuitConfirmation(int *this)
{
    int dialogHandle;
    
    // Set bit 0 at offset 0x66 (UI state flag)
    *(ushort *)((int)this + 0x66) |= 1;
    
    // Call virtual function at vtable+0x0C (likely some initialization/update)
    (**(code **)(*this + 0xc))();
    
    // Set bit 1 at offset 0x66
    *(ushort *)((int)this + 0x66) |= 2;
    
    // Hide main menu (or previous UI)
    FUN_005a04a0("MenuHide", 0, &DAT_00d8f604, 0);
    
    // Create/retrieve UI dialog handle (0xF0 = dialog type ID for quit confirmation?)
    dialogHandle = FUN_009c8e50(0xf0);
    if (dialogHandle == 0) {
        dialogHandle = 0;
    }
    else {
        dialogHandle = FUN_00982280(0); // Initialize dialog from template
    }
    
    // Set dialog title/description text from localization string
    FUN_00981eb0("$mp_online_quit_confirmation");
    
    // Configure dialog behavior:
    // +0x0C = result code (2 = secondary button? maybe "Yes")
    *(int *)(dialogHandle + 0xc) = 2;
    // +0x14 = pointer to callback function for button press
    *(int *)(dialogHandle + 0x14) = (int)&LAB_009745c0;
    
    // Finalize/show dialog
    FUN_00982e10();
}