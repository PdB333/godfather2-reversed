// FUNC_NAME: GameManager::GameManager

#include <cstdint>

// Global state variables
extern uint32_t DAT_012059dc; // +0x12059dc
extern uint32_t DAT_012059e0; // +0x12059e0
extern uint32_t DAT_012233f4; // +0x12233f4

// External vtable pointers
extern void* PTR_FUN_00e3105c;   // vtable for base class
extern void* PTR_LAB_00e31068;   // vtable at offset 8
extern void* PTR_LAB_00e31078;   // vtable at offset 20 (initial)
extern void* PTR_LAB_00e3107c;   // vtable at offset 20 (final)

// Forward declarations of sub-initializers
void __cdecl FUN_0043eae0(void);
void __cdecl FUN_004083d0(void);
void __cdecl FUN_0049c640(void);

// Object structure (partial: only known vtable offsets)
struct GameManager {
    void* vtable0;  // +0x00
    uint32_t field_4;  // +0x04 (unknown)
    void* vtable2;  // +0x08
    uint32_t field_C;  // +0x0C (unknown)
    uint32_t field_10; // +0x10 (unknown)
    void* vtable5;  // +0x14
};

// Constructor
void __fastcall GameManager::GameManager(GameManager* thisObject)
{
    // Set up vtable pointers (initial stub versions)
    thisObject->vtable0 = &PTR_FUN_00e3105c;
    thisObject->vtable2 = &PTR_LAB_00e31068;
    thisObject->vtable5 = &PTR_LAB_00e31078;

    // Initialize global singleton flags to 0
    DAT_012059dc = 0;
    DAT_012059e0 = 0;

    // Sub-initialization (may use the stub vtable)
    FUN_0043eae0();

    // After sub-init, replace the vtable at offset 0x14 with the final version
    thisObject->vtable5 = &PTR_LAB_00e3107c;

    // Reset another global flag
    DAT_012233f4 = 0;

    // Additional system initializations
    FUN_004083d0();
    FUN_0049c640();
}