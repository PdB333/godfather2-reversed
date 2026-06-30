// Function at 0x00426450: GameEngine::initialize - Called during startup to initialize input, memory, and global systems
void __thiscall GameEngine::initialize(GameEngine* this)
{
    // Initialize input subsystem (likely controller/keyboard setup)
    InputSystem::initialize(this);  // calls FUN_00424c90
    // Initialize memory management (pool allocators, etc.)
    MemorySystem::initialize(this); // calls FUN_004a21d0
    // Perform global/static initialization (e.g., timers, logging)
    App::initialize();              // calls FUN_004252e0
}