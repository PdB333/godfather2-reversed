// FUNC_NAME: GameManager::processUpdate
// Function at 0x006143a0: Delegates work to internal processing and conditionally calls debug update.
void __thiscall GameManager::processUpdate(void* arg1, void* arg2, void* arg3, void* arg4) {
    // Call internal processing function with this pointer as the last argument.
    internalProcess(arg1, arg2, arg3, arg4, this);
    // Check global debug flag (bit 0) and invoke debug update if set.
    if ((g_debugFlags & 1) != 0) {
        debugUpdate();
    }
}