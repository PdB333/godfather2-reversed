// FUNC_NAME: initializeGameGlobals
// Function at 0x004c5a80: Initializes global game engine data structure (singleton).
// Returns pointer to the main global structure at address 0x01218110.

struct GameGlobals {
    // +0x00: vtable pointer (PTR_LAB_00e36364)
    void** vtable; // 0x01218110
    // Other fields follow; we only care about those initialized here.
    // +0xA4? Actually offsets from 0x01218110:
    // 0x012181b4 - 0x01218110 = 0xA4
    uint32_t field_A4; // 0x012181b4 = 0
    // 0x012181cc - 0x01218110 = 0xBC
    // 0x012181d0 - 0x01218110 = 0xC0
    // 0x012181d4 - 0x01218110 = 0xC4
    // 0x012181d8 - 0x01218110 = 0xC8
    // 0x012181dc - 0x01218110 = 0xCC
    // 0x012181e0 - 0x01218110 = 0xD0
    // 0x012181e4 - 0x01218110 = 0xD4
    // 0x012181e8 - 0x01218110 = 0xD8
    uint32_t field_BC; // 0x012181cc = DAT_00e2b1a4
    uint32_t field_C0; // 0x012181d0 = DAT_00e2b1a4
    uint32_t field_C4; // 0x012181d4 = DAT_00e2e230
    uint32_t field_C8; // 0x012181d8 = 0
    uint32_t field_CC; // 0x012181dc = 0
    uint32_t field_D0; // 0x012181e0 = 0
    uint32_t field_D4; // 0x012181e4 = 0
    uint32_t field_D8; // 0x012181e8 = 0
};

// External references (likely defined elsewhere)
extern void FUN_006126d0(void); // Sub-initialization function
extern uint32_t DAT_00e2b1a4; // Some constant or variable
extern uint32_t DAT_00e2e230; // Some constant or variable

// Global instance pointer
GameGlobals* gGameGlobals; // At address 0x01218110? Actually the struct starts there.

// Function implementation
GameGlobals* initializeGameGlobals() {
    // Call sub-initialization (possibly sets up allocator or base systems)
    FUN_006126d0();

    // Set up the global game globals structure
    // Note: These globals are at fixed addresses in the .data section.
    // We reconstruct as if they are static members of a class or direct globals.

    // Assign vtable pointer
    gGameGlobals->vtable = &PTR_LAB_00e36364; // External vtable symbol

    // Initialize fields with constants (likely default values)
    gGameGlobals->field_BC = DAT_00e2b1a4;
    gGameGlobals->field_C0 = DAT_00e2b1a4;
    gGameGlobals->field_C4 = DAT_00e2e230;

    // Zero out remaining fields
    gGameGlobals->field_C8 = 0;
    gGameGlobals->field_CC = 0;
    gGameGlobals->field_D0 = 0;
    gGameGlobals->field_D4 = 0;
    gGameGlobals->field_D8 = 0;
    gGameGlobals->field_A4 = 0; // Offset 0xA4

    // Return pointer to the struct (address 0x01218110)
    return gGameGlobals;
}