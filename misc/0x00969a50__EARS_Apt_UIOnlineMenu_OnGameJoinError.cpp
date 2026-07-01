// Xbox PDB: EARS_Apt_UIOnlineMenu_OnGameJoinError
// FUNC_NAME: NetSession::handleJoinGameError
void __thiscall NetSession::handleJoinGameError(int errorCode) {
    // 0x00969a50
    FUN_00982c90(); // Clear previous error state

    // Virtual call: vtable+8 (probably reset/update something)
    (**(code **)(*this + 8))();

    // Clear a flag at offset 0x1bd*4 = 0x774
    this[0x1bd] &= 0xfffffffd;

    // Virtual call again
    (**(code **)(*this + 8))();

    // Load generic error string (likely from localized string table)
    FUN_004d3bc0("$mp_online_generic_join_game_error");

    // Select specific error string based on errorCode
    const char* errorString;
    switch (errorCode) {
    case 0: // MP_ONLINE_GAME_FULL
        errorString = "$mp_online_game_full";
        break;
    case 1: // MP_NO_PUBLIC_SLOTS
        errorString = "$mp_no_public_slots";
        break;
    default:
        goto defaultCase; // Unhandled code – skip setting error string
    case 3: // MP_HOST_MUST_RETURN
        errorString = "$mp_host_must_return";
        break;
    case 0x3d: // MP_HOST_STRICT_NAT_FULL
        errorString = "$mp_host_strict_nat_full";
        break;
    case 0x3e: // MP_CANNOT_JOIN_NO_DON_SLOTS
        errorString = "$mp_cannot_join_no_don_slots";
        break;
    case 0x3f: // MP_CANNOT_JOIN_NO_NON_DON_SLOTS
        errorString = "$mp_cannot_join_no_non_don_slots";
    }
    if (errorCode != 2 && errorCode != 0x3d && errorCode != 0x3e && errorCode != 0x3f) {
        defaultCase:
        // Set the localized string for display
        FUN_004d3d90(errorString);
    }

    // Allocate memory for dialog structure (size 0xF0 bytes)
    int dialogMem = FUN_009c8e50(0xF0);
    if (dialogMem == 0) {
        dialogMem = 0;
    } else {
        dialogMem = FUN_00982280(0); // Likely creates a dialog object
    }

    // Set dialog type and callback
    *(int*)(dialogMem + 0x0C) = 3; // Dialog type 3 (maybe error dialog)
    *(code**)(dialogMem + 0x14) = FUN_00982b30; // Callback function (e.g., on dismiss)

    // Display the dialog
    FUN_00982e10();

    // Check if we are in the main menu state (offset 0x37*4 = 0xDC)
    if (this[0x37] == 6) { // State 6 likely = MainMenuState
        FUN_00965ea0(); // Possibly return to main menu or clean up
    }

    // Free temporary string if dynamically allocated (stack cleanup)
    // Note: puStack_10 was a pointer on stack, guarded by a check
    // In the original code, if puStack_10 was not null, it was freed via a destructor call
    // We simulate with an if block
    if (errorString != 0) {
        // This cleanup is handled by the Lua string management – not needed in C++
        // (The original placed a destructor call via a stack cookie)
    }
}