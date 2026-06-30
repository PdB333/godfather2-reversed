// FUNC_NAME: GameManager::processEvent
// Address: 0x0043b960
// Role: Calls the second virtual function on a subsystem obtained from the global game manager singleton.
// The global at DAT_01223410 is the GameManager base. Offset 0x2d4 holds a pointer to a subsystem object.
// The called function (vtable offset 4) is invoked with the given parameter and zero as arguments.
// This is a core dispatch used extensively throughout the game.

// Forward declaration of the subsystem's vtable type
struct SubsystemVTable {
    void (*entry0)();   // vtable[0]
    void (*entry1)(void* param, int zero); // vtable[4] - the actual function called
};

// The subsystem class (only the vtable pointer shown)
struct Subsystem {
    SubsystemVTable* vtable;
};

// The global GameManager structure (partial)
struct GameManager {
    uint8_t pad0[0x2D4];            // unknown padding
    Subsystem* m_pSubsystem;        // +0x2D4 pointer to the subsystem
};

// External global pointer to the GameManager singleton
extern GameManager* g_pGameManager;

// Reconstructed function: invokes the subsystem's method with param and 0
void GameManager::processEvent(void* param) {
    // Fetch the subsystem pointer from the game manager at offset 0x2D4
    Subsystem* subsystem = g_pGameManager->m_pSubsystem;
    // Call the second virtual function (vtable offset 4) with param and 0
    subsystem->vtable->entry1(param, 0);
}