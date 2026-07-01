// FUNC_NAME: GodfatherGameManager::showDebugMenuForPlayer
void __thiscall GodfatherGameManager::showDebugMenuForPlayer(int playerIndex) {
    // Compare playerIndex with current player indices from two managers.
    // DAT_0113000c + 0x10 -> vtable of main player manager, func at offset +4 (likely GetPlayerIndex)
    int mainPlayerIdx = (**(code **)(*(int *)(DAT_0113000c + 0x10) + 4))();
    if (playerIndex != mainPlayerIdx) {
        int secondPlayerIdx = (**(code **)(*(int *)(DAT_01130064 + 0x10) + 4))();
        if (playerIndex != secondPlayerIdx) {
            return; // Not a valid player to open this menu
        }
    }

    // Mark flag at +0x5c indicating menu is active
    *(int*)(this + 0x5c) = 1;

    // Show the debug menu (likely a pause menu or debug overlay)
    // Parameters: "ShowMenu" command, zero, string resource (DAT_00d8f7f8), zero
    ShowMenu("ShowMenu", 0, &DAT_00d8f7f8, 0);
}