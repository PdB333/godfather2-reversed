// FUNC_NAME: GameManager::GameManager
// Address: 0x006a86b0
// Constructor for GameManager.  Sets up vtable and base interface pointer,
// handles sub‑object cleanup, initializes global state, and optionally
// registers the object.
// Offsets: +0x00 vtable, +0x0C baseInterface, +0x14 m_pSubObject

class GameManager {
public:
    GameManager(byte createFlags);

private:
    // +0x00
    void* vtable;
    // +0x04 … +0x08 unknown
    // +0x0C pointer to base vtable (changed during construction)
    void* baseInterface;
    // +0x14 pointer to a sub‑object (may be null)
    void* m_pSubObject;
};

GameManager::GameManager(byte createFlags) {
    // Set primary vtable for this class
    this->vtable = &g_GameManagerVTable;          // PTR_FUN_00d5d8b8

    // Set initial base vtable pointer
    this->baseInterface = &g_BaseVTable1;         // PTR_LAB_00d5d8b4

    // Initialize global context (e.g., memory allocator)
    FUN_004086d0(&g_GlobalContext);               // DAT_012069c4

    // If a sub‑object already exists, destroy it and clear the pointer
    if (this->m_pSubObject != nullptr) {
        FUN_004daf90(&this->m_pSubObject);        // destroys sub‑object, sets to null
    }

    // Replace base interface pointer with a different vtable
    this->baseInterface = &g_BaseVTable2;         // PTR_LAB_00d5d898

    // Reset global state flag
    g_SomeGlobalCounter = 0;                      // DAT_011299b4

    // Perform further initialization
    FUN_004083d0();

    // If bit 0 is set, register this object (e.g., add to a global list)
    if ((createFlags & 1) != 0) {
        FUN_009c8eb0(this);                       // registers the new object
    }
}