// FUNC_NAME: GameManager::~GameManager
// Reconstructed destructor for GameManager (hypothetical class based on EA EARS engine)
// Function address: 0x005c4520
// Calls base class destructor (0x005c4290) and virtual cleanup via secondary vtable

// Assumed class layout (offsets in bytes):
// +0x00 : vtable pointer (primary, for GameManager or its base)
// +0x04 : vtable pointer (secondary, for an additional base or interface)
// ... other members ...

// Global state cleaned up by this destructor
// DAT_0119caf0, 0x0119caf4, 0x0119caf8, 0x012234ec

class GameManager {
public:
    void* vtable0;     // +0x00: primary vtable
    void* vtable1;     // +0x04: secondary vtable (used for virtual cleanup)
    // ... other members ...
};

void __thiscall GameManager::~GameManager(unsigned char deletingFlag)
{
    // Set primary vtable to base class vtable (likely BaseManager)
    this->vtable0 = &BaseManager::_vtable; // PTR_FUN_00e3ea08

    // Call base class destructor (0x005c4290)
    BaseManager::~BaseManager(this);

    // Call virtual cleanup function from secondary vtable at offset 0x0C
    (*(void (__thiscall**)(GameManager*))((int*)this->vtable1)[3])(this); // offset 0xC in vtable

    // Restore vtable to derived class (maybe for further cleanup)
    this->vtable0 = &GameManager::_vtable; // PTR_LAB_00e3ea0c

    // Zero global state variables
    g_SomeGlobal1 = 0; // DAT_0119caf0
    g_SomeGlobal2 = 0; // DAT_0119caf4
    g_SomeGlobal3 = 0; // DAT_0119caf8
    g_SomeGlobal4 = 0; // DAT_012234ec

    // If the deleting flag is set, deallocate memory
    if ((deletingFlag & 1) != 0) {
        operator delete(this); // FUN_009c8eb0
    }
}