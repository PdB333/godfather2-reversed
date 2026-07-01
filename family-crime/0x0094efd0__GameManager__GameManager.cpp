// FUNC_NAME: GameManager::GameManager
// Constructor for the main GameManager singleton. Sets up vtable pointers and initializes fields.
// Address: 0x0094efd0

// Forward declaration of helper function
void sub_94ebd0(int param);

// Global pointer to the single GameManager instance
GameManager* g_gameManagerInstance = nullptr;

// Vtable structures (defined elsewhere, assumed)
extern void* const g_vtable_00d8ba90[];   // Base class vtable
extern void* const g_vtable_00d8ba80[];   // Derived/interface vtable
extern void* const g_vtable_00e2f19c[];   // Unused? (overwritten)

class GameManager {
public:
    // Vtable pointers (first two DWORDs)
    void* vtableBase;       // +0x00: points to g_vtable_00d8ba90
    void* vtableDerived;    // +0x04: points to g_vtable_00d8ba80
    int field_0x08;         // +0x08: initialized to 1
    int field_0x0C;         // +0x0C: initialized to 0
    // ... other fields up to offset 0x20
    int field_0x20;         // +0x20: cleared to 0
    int field_0x24;         // +0x24: cleared to 0
    int field_0x28;         // +0x28: cleared to 0
    // Additional fields assumed

    GameManager() {
        // Store this instance globally
        g_gameManagerInstance = this;

        // Set up vtable pointers
        this->vtableBase = (void*)&g_vtable_00d8ba90;     // +0x00
        this->vtableDerived = (void*)&g_vtable_00d8ba80;  // +0x04 (overwrites earlier assignment)

        // Initialization of simple fields
        this->field_0x08 = 1;
        this->field_0x0C = 0;

        // Call helper to initialize sub-object (e.g., allocator, stream manager)
        sub_94ebd0(8);   // Argument 8 likely indicates a type or size

        // Clear more fields
        this->field_0x20 = 0;
        this->field_0x24 = 0;
        this->field_0x28 = 0;
    }
};