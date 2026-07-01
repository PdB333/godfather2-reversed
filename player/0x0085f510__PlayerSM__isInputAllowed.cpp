// FUNC_NAME: PlayerSM::isInputAllowed
bool __fastcall PlayerSM::isInputAllowed() {
    // Check if global input is allowed (e.g., not paused, menu closed)
    bool globalInputAllowed = FUN_00544ba0(); // GlobalSystem::isInputActive()
    if (!globalInputAllowed) {
        return false;
    }

    // Check local flag at offset 0xf2b (bit 0) for player-specific input enable
    if ((*(byte *)(this + 0xf2b) & 1) == 0) {
        return false;
    }

    return true;
}