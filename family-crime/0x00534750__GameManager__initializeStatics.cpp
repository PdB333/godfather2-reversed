// FUNC_NAME: GameManager::initializeStatics
// Address: 0x00534750
// Description: Initializes global game manager singleton state. Sets most fields to zero and a set of pointer-like fields to a default sentinel value (DAT_00e2b1a4).
// Offsets are relative to the base of the global at 0x01219a70.

#include <cstdint>

// External low-level initialization (likely memory clear)
void engineInitializeMemory(); // FUN_006126d0

// Global constant – appears to be a default pointer value / sentinel
const uint32_t kDefaultPointerValue = 0x00E2B1A4; // DAT_00e2b1a4

// Global vtable pointer for the singleton's class
const void* kGameManagerVTable = (void*)0x00E386A8; // PTR_LAB_00e386a8

// Global singleton instance at 0x01219a70
// Structure is at least 0x160 bytes. Only fields accessed here are documented.
struct GameManagerState {
    // vtable pointer
    void* vtable; // +0x00

    // Padding or other fields omitted for brevity; all offsets below are relative to base.

    // Zero-initialized fields
    uint32_t field_0xB4; // +0xB4
    uint32_t field_0xB8; // +0xB8
    uint32_t field_0xC4; // +0xC4
    uint32_t field_0xD0; // +0xD0
    uint32_t field_0xD4; // +0xD4
    uint32_t field_0xD8; // +0xD8

    // Default pointer fields (set to kDefaultPointerValue)
    uint32_t somePointer1; // +0xDC
    uint32_t somePointer2; // +0xE0

    uint32_t field_0xE4; // +0xE4
    uint32_t field_0xE8; // +0xE8
    uint32_t field_0xEC; // +0xEC
    uint32_t field_0xF0; // +0xF0

    uint32_t somePointer3; // +0xF4

    uint32_t field_0xF8; // +0xF8
    uint32_t field_0xFC; // +0xFC
    uint32_t field_0x100; // +0x100
    uint32_t field_0x104; // +0x104

    uint32_t somePointer4; // +0x108

    uint32_t field_0x10C; // +0x10C
    uint32_t field_0x110; // +0x110
    uint32_t field_0x114; // +0x114
    uint32_t field_0x118; // +0x118

    uint32_t somePointer5; // +0x11C
    uint32_t somePointer6; // +0x120

    uint32_t field_0x124; // +0x124
    uint32_t field_0x128; // +0x128
    uint32_t field_0x12C; // +0x12C
    uint32_t field_0x130; // +0x130

    uint32_t somePointer7; // +0x134

    uint32_t field_0x138; // +0x138
    uint32_t field_0x13C; // +0x13C
    uint32_t field_0x140; // +0x140
    uint32_t field_0x144; // +0x144

    uint32_t somePointer8; // +0x148

    uint32_t field_0x14C; // +0x14C
    uint32_t field_0x150; // +0x150
    uint32_t field_0x154; // +0x154
    uint32_t field_0x158; // +0x158

    uint32_t somePointer9; // +0x15C
};

// Extern global instance
extern GameManagerState g_GameManagerState; // at 0x01219a70

// Initializes the global singleton and returns its address
GameManagerState* initializeGameManager()
{
    // Low-level memory initialization (may zero or set up something)
    engineInitializeMemory();

    // Zero-initialize all fields; the following assignments match the decompiled order.
    g_GameManagerState.field_0xB4 = 0;
    g_GameManagerState.field_0xB8 = 0;
    g_GameManagerState.field_0xC4 = 0;
    g_GameManagerState.field_0xD0 = 0;
    g_GameManagerState.field_0xD4 = 0;
    g_GameManagerState.field_0xD8 = 0;

    // Set a number of fields to the default pointer sentinel
    g_GameManagerState.somePointer1 = kDefaultPointerValue;
    g_GameManagerState.somePointer2 = kDefaultPointerValue;
    g_GameManagerState.field_0xE4 = 0;
    g_GameManagerState.field_0xE8 = 0;
    g_GameManagerState.field_0xEC = 0;
    g_GameManagerState.field_0xF0 = 0;
    g_GameManagerState.somePointer3 = kDefaultPointerValue;
    g_GameManagerState.field_0xF8 = 0;
    g_GameManagerState.field_0xFC = 0;
    g_GameManagerState.field_0x100 = 0;
    g_GameManagerState.field_0x104 = 0;
    g_GameManagerState.somePointer4 = kDefaultPointerValue;
    g_GameManagerState.field_0x10C = 0;
    g_GameManagerState.field_0x110 = 0;
    g_GameManagerState.field_0x114 = 0;
    g_GameManagerState.field_0x118 = 0;
    g_GameManagerState.somePointer5 = kDefaultPointerValue;
    g_GameManagerState.somePointer6 = kDefaultPointerValue;
    g_GameManagerState.field_0x124 = 0;
    g_GameManagerState.field_0x128 = 0;
    g_GameManagerState.field_0x12C = 0;
    g_GameManagerState.field_0x130 = 0;
    g_GameManagerState.somePointer7 = kDefaultPointerValue;
    g_GameManagerState.field_0x138 = 0;
    g_GameManagerState.field_0x13C = 0;
    g_GameManagerState.field_0x140 = 0;
    g_GameManagerState.field_0x144 = 0;
    g_GameManagerState.somePointer8 = kDefaultPointerValue;
    g_GameManagerState.field_0x14C = 0;
    g_GameManagerState.field_0x150 = 0;
    g_GameManagerState.field_0x154 = 0;
    g_GameManagerState.field_0x158 = 0;
    g_GameManagerState.somePointer9 = kDefaultPointerValue;

    // Set the vtable pointer
    g_GameManagerState.vtable = const_cast<void*>(kGameManagerVTable);

    return &g_GameManagerState;
}