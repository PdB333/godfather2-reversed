// FUNC_NAME: GameSystem::GameSystem
// Address: 0x004557b0
// Role: Constructor for a core game system object. Sets up vtable and function pointers at offsets 0, 0x0C, 0x10, then calls global initialization routines for EARS engine subsystems.

class GameSystem {
public:
    // +0x00: vtable pointer
    void* vtable;
    // +0x0C: pointer to a function or vtable (PTR_LAB_00e31948)
    void* field_0C;
    // +0x10: pointer to another function (PTR_FUN_00e31960)
    void* field_10;

    // Constructor: initializes the object and calls several engine startup functions.
    void __fastcall GameSystem() {
        // Set vtable and additional function pointers
        vtable = (void*)&PTR_FUN_00e31938;
        field_0C = (void*)&PTR_LAB_00e31948;
        field_10 = (void*)&PTR_FUN_00e31960;

        // Call global initialization routines (likely registering this system, initializing constants, or setting up global state)
        FUN_004086d0(&DAT_01206940);   // External init with global data
        FUN_00408310(&DAT_0120ea7c);   // External init with another global
        FUN_00564b90();                // No-arg engine init
        FUN_004083d0();                // Another no-arg init
    }
};