// FUNC_NAME: SimNpc::SimNpc (constructor at 0x006cf9b0)
// Initializes a SimNpc (simulated NPC) with multiple base class vtables and sentinel fields.
// Typical EA EARS engine pattern: multiple inheritance with vtable pointers at +0x00, +0x3C, +0x48, +0x50.
// Calls base init, member init, and derived init functions.

#include <cstdint>

extern void __fastcall FUN_004737b0();   // EARS base object constructor / memory setup
extern void __fastcall FUN_00473750();   // common member initialization (zeros or sentinel writes)
extern void __fastcall FUN_006cf1a0();   // SimNpc-specific initialization

extern void* PTR_FUN_00d5f228;  // main vtable for SimNpc
extern void* PTR_LAB_00d5f214;  // vtable for first base class (e.g., Sentient)
extern void* PTR_LAB_00d5f210;  // vtable for second base class (e.g., Character)
extern void* PTR_LAB_00d5f20c;  // vtable for third base class (e.g., Entity)

__fastcall void SimNpc::SimNpc(void* this_pointer)
{
    FUN_004737b0();

    // Assign virtual tables for multiple inheritance
    *(void**)(this_pointer)                      = &PTR_FUN_00d5f228;  // +0x00: main vtable
    *(void**)((uint8_t*)this_pointer + 0x3C)    = &PTR_LAB_00d5f214;  // +0x3C: base vtable A
    *(void**)((uint8_t*)this_pointer + 0x48)    = &PTR_LAB_00d5f210;  // +0x48: base vtable B
    *(void**)((uint8_t*)this_pointer + 0x50)    = &PTR_LAB_00d5f20c;  // +0x50: base vtable C

    FUN_00473750();

    // Initialize fields – many set to zero, two set to 0xFE16702F (likely debug sentinel)
    *(int32_t*)((uint8_t*)this_pointer + 0xB4)   = 0;          // +0xB4: integer field
    *(uint16_t*)((uint8_t*)this_pointer + 0xB8)  = 0;          // +0xB8: short
    *(uint16_t*)((uint8_t*)this_pointer + 0xBA)  = 0;          // +0xBA: short (padded)
    *(int32_t*)((uint8_t*)this_pointer + 0xBC)   = 0;          // +0xBC: integer
    *(uint16_t*)((uint8_t*)this_pointer + 0xC0)  = 0;          // +0xC0: short
    *(uint16_t*)((uint8_t*)this_pointer + 0xC2)  = 0;          // +0xC2: short (padded)
    *(int32_t*)((uint8_t*)this_pointer + 0xC8)   = 0;          // +0xC8: integer
    *(int32_t*)((uint8_t*)this_pointer + 0xCC)   = 0xFE16702F; // +0xCC: sentinel
    *(int32_t*)((uint8_t*)this_pointer + 0xD0)   = 0;          // +0xD0: integer
    *(int32_t*)((uint8_t*)this_pointer + 0xD4)   = 0xFE16702F; // +0xD4: sentinel

    FUN_00473750();  // second member init (e.g., finalize zeroing)
    FUN_006cf1a0();  // derived class constructor
}