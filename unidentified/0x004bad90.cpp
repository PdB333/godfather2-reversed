// FUNC_004bad90: GameCore::initialize
void __thiscall GameCore::initialize(GameCore* this)
{
    // Set vtable pointer to class-specific function table
    *this = &g_vtable_GameCore; // class vtable at 0x00e35c20

    // Initialize two global manager objects (likely memory pools or critical sections)
    MemoryManager::init(&g_mgr1);   // DAT_01218040
    MemoryManager::init(&g_mgr2);   // DAT_01218048

    // Platform-specific initialization (OS, threading, etc.)
    Platform::init();               // FUN_00407430

    // Subsystem initializations (order likely: input, then audio)
    InputManager::init();           // FUN_004bc3f0
    AudioManager::init();           // FUN_004bc280
}