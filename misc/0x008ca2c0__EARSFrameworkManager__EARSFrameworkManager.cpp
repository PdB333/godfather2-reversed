// FUNC_NAME: EARSFrameworkManager::EARSFrameworkManager
// Address: 0x008ca2c0
// Constructor for the main framework manager. Initializes the vtable,
// zeroes out core fields, and stores the instance globally.
// The global DAT_01129990 is the singleton pointer.

// Forward declaration of base class initializer (called at offset 0x10)
extern void FUN_008ca0d0();

class EARSFrameworkManager {
public:
    static EARSFrameworkManager* ms_pInstance; // global singleton (DAT_01129990)

    // +0x00: vtable pointer (set to VTABLE_ADDR_00d7bf40)
    void* vtable;

    // +0x04: unknown field (initialized to 0)
    int field_04;

    // +0x08: unknown field (initialized to 0)
    int field_08;

    // +0x0C: unknown field (initialized to 0)
    int field_0C;

    // +0x10: byte field (initialized to 0 after base init)
    char field_10;

    // Constructor – returns 'this' to match __fastcall convention
    EARSFrameworkManager* __fastcall construct() {
        ms_pInstance = this;

        // Set vtable
        vtable = (void*)0x00d7bf40;

        // Zero out first three integer fields
        field_04 = 0;
        field_08 = 0;
        field_0C = 0;

        // Call base class constructor / initialization routine
        FUN_008ca0d0();

        // Initialize the byte field to 0
        field_10 = 0;

        return this;
    }
};

// Global instance pointer definition
EARSFrameworkManager* EARSFrameworkManager::ms_pInstance = nullptr;