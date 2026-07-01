//FUNC_NAME: MPMenuManager::showJoinGameAsDonDialog
void __fastcall MPMenuManager::showJoinGameAsDonDialog(MPMenuManager* this)
{
    // Allocate a dialog structure of 0xF0 bytes (240 bytes)
    JoinGameAsDonDialog* dialog = (JoinGameAsDonDialog*)FUN_009c8e50(0xF0);
    if (dialog != nullptr) {
        // Initialize the dialog (constructor-like call)
        dialog = (JoinGameAsDonDialog*)FUN_00982280(0); // 0 indicates no parent or default
    }

    // Set the dialog title to localized string "$mp_join_game_as_don"
    FUN_00981eb0("$mp_join_game_as_don");

    // Initialize dialog fields
    dialog->selectedOption = 0; // +0x0C: default selection index

    // Add two options: Yes and No
    FUN_00981e70("$mp_online_menu_yes", 0, 0); // option index 0
    FUN_00981e70("$mp_online_menu_no", 1, 0);  // option index 1

    // Set the callback function pointer (e.g., button handler)
    dialog->callback = &LAB_00971620; // +0x14: function pointer to handle selection

    // Mark the parent menu as having an active dialog (flag at +0x2E0)
    *(uint8_t*)((uint8_t*)this + 0x2E0) = 1;

    // Show the dialog and update UI
    FUN_00983190(); // likely showDialog()
    FUN_00982e10(); // likely updateUI() or refresh()
}