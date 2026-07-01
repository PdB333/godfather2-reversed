// FUNC_NAME: GameManager::bootstrap
// 0x00861700 - Core initialization sequence for GameManager, calls three subsystem init routines.
void __thiscall GameManager::bootstrap(void) {
    // Initialize audio/render/memory subsystem 1
    initSubsystemA();
    // Initialize input/controller subsystem 2 (uses this pointer)
    initSubsystemB();
    // Initialize streaming/network subsystem 3
    initSubsystemC();
}