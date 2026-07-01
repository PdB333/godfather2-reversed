// FUNC_NAME: UILobbyScreen::showLobby
void __fastcall UILobbyScreen::showLobby(int this)
{
    // Copy byte from offset 0x1F4 to 0x160 (likely a flag or state)
    *(char *)(this + 0x160) = *(char *)(this + 0x1F4);

    // Update UI elements with values from various offsets
    FUN_00965c20(
        *(int *)(this + 0x120), // +0x120: some UI data
        *(int *)(this + 0x128), // +0x128
        *(int *)(this + 0x12C), // +0x12C (300 decimal)
        *(int *)(this + 0x130), // +0x130
        *(int *)(this + 0x138), // +0x138
        *(int *)(this + 0xE4),  // +0xE4
        *(int *)(this + 0x114), // +0x114
        *(int *)(this + 0x124), // +0x124
        *(int *)(this + 0xFC),  // +0xFC
        *(int *)(this + 0x104)  // +0x104
    );

    // Show the lobby screen
    FUN_005a04a0("ShowLobby", 0, &DAT_00d8cdec, 0);

    // If current state (at +0xDC) is not 3, transition to a new state
    if (*(int *)(this + 0xDC) != 3) {
        FUN_005c0260(this + 0x10, &LAB_00963ee0, 1);
    }

    // Set some global state to 5
    FUN_00970400(5);

    // If a flag at +0x144 is zero, deactivate a button
    if (*(char *)(this + 0x144) == '\0') {
        FUN_005a04a0("DeactivateButton", 0, &DAT_00d8cdec, 1, &DAT_00d796d0);
    }
}