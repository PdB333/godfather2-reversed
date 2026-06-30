// FUNC_NAME: GlobalGameManager::init
// Function address: 0x00467ef0
// This is a constructor/initializer for a global manager object in the EARS engine.
// It sets up vtables, initializes fields with sentinel values (common EA debug signatures),
// and stores the instance in a global pointer.
// The object appears to be a singleton system manager.

#include <cstdint>

// Forward declarations for external symbols
extern void* PTR_FUN_00e31f54; // Primary vtable pointer
extern void* PTR_LAB_00e31f60; // Secondary vtable pointer (possibly for second base class)
extern uint32_t DAT_00e2eff4;   // Default initialization value (appears 3 times)
extern uint32_t DAT_00e2b1a4;   // Another default initialization value (appears 2 times)
extern GlobalGameManager* DAT_01223470; // Global variable storing singleton instance

// Forward declaration of base class initializer called at the end
void baseInit(void* this); // Address: 0x0043e2e0

// Class representing the global game manager
class GlobalGameManager {
public:
    // Field offsets (all offsets in bytes relative to this):
    void* vtable0;                   // +0x00
    void* vtable4;                   // +0x04
    uint32_t field_0x08;             // +0x08
    uint32_t field_0x0C;             // +0x0C
    uint32_t field_0x10;             // +0x10
    uint32_t field_0x14;             // +0x14
    uint32_t field_0x18;             // +0x18
    uint32_t field_0x1C;             // +0x1C
    uint32_t field_0x20;             // +0x20
    uint32_t field_0x24;             // +0x24
    uint32_t field_0x28;             // +0x28
    uint32_t field_0x2C;             // +0x2C
    uint32_t field_0x30;             // +0x30
    uint32_t field_0x34;             // +0x34
    uint8_t  field_0x38_byte;        // +0x38 (byte at offset 0x38)
    uint32_t field_0x3C;             // +0x3C
    // Additional fields may follow

    // Constructor-like initializer (called on raw memory buffer)
    // Returns this pointer as per original assembly (ECX/EDX __fastcall)
    GlobalGameManager* init();
};

// Implementation
GlobalGameManager* GlobalGameManager::init() {
    // Set vtable pointers (order matters: first set, then overwritten for second)
    vtable4 = &PTR_LAB_00e31f60; // Write secondary vtable early
    vtable0 = &PTR_FUN_00e31f54; // Primary vtable
    vtable4 = &PTR_LAB_00e31f60; // Confirm secondary vtable (overwrites initial)

    // Initialize fields with global constants
    field_0x08 = DAT_00e2eff4;
    field_0x0C = DAT_00e2eff4;
    field_0x10 = DAT_00e2eff4;
    field_0x14 = DAT_00e2b1a4;
    field_0x18 = DAT_00e2b1a4;
    field_0x1C = 0;
    field_0x20 = 0;
    field_0x24 = 1;               // +0x24: default value 1
    field_0x28 = 0xbadbadba;      // +0x28: debug sentinel
    field_0x2C = 0xbeefbeef;      // +0x2C: sentinel
    field_0x30 = 0xeac15a55;      // +0x30: sentinel
    field_0x34 = 0x91100911;      // +0x34: sentinel
    field_0x38_byte = 0;          // +0x38: zeroed byte
    field_0x3C = 96000;           // +0x3C: initial frequency/interval value

    // Redundant writes (as seen in decompilation)
    field_0x28 = 0xbadbadba;
    field_0x24 = 1;
    field_0x3C = 96000;

    // Store this instance in global singleton pointer
    DAT_01223470 = this;

    // Call base class initializer (likely a parent class constructor)
    baseInit(this);

    return this;
}