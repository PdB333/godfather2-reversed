// FUNC_NAME: GameManager::updateSubsystem
void __thiscall GameManager::updateSubsystem(int param_2) {
    // Check if the game is active (global function at 0x00481620)
    if (IsGameActive()) {
        // Call update on subsystem object stored at this+0x568
        SubSystemUpdate(*(int*)(this + 0x568), param_2);
    }
}