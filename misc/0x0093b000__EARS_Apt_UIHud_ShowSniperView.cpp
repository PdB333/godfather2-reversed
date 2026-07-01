// Xbox PDB: EARS_Apt_UIHud_ShowSniperView
// FUNC_NAME: PlayerActionableTargetSM::showSniperView
void __thiscall PlayerActionableTargetSM::showSniperView(PlayerActionableTargetSM* this, int playerIndex) {
    char buffer[16]; // formatted text buffer

    // Check if sniper view is already shown (bit 29)
    if (!(*(uint*)((int)this + 0x5c) & 0x20000000)) {
        // Set sniper view active flag
        *(uint*)((int)this + 0x5c) |= 0x20000000;

        // Build the UI message key (likely "SniperView" with player index)
        formatString(buffer, sizeof(buffer), &DAT_00e325c4, playerIndex);

        // Show the sniper view overlay
        showUIHint("ShowSniperView", 0, &DAT_00d8a64c, 1, buffer);

        // Enter sniper camera state (static function)
        enterSniperView();

        // Check if other views should be suppressed (bit 19)
        if (!(*(uint*)((int)this + 0x5c) & 0x80000)) {
            // Suppress all UI except sniper and health
            showUIHint("SuppressAllExceptSniperViewAndHealth", 0, &DAT_00d8a64c, 0);
        }
    }
}