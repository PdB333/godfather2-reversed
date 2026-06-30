// FUNC_NAME: Module::registerVtableAndConstruct
// Address: 0x005f2da0
// Purpose: Sets up a 4-entry virtual function table and calls a base class constructor on a global instance.
// Used during module initialization (e.g., UI, network, or gameplay system).

#include <cstdint>

// Forward declarations for the virtual function implementations
extern void impl_1(); // 0x005f26f0
extern void impl_2(); // 0x005f2830
extern void impl_3(); // 0x005f29e0
extern void impl_4(); // 0x005f2b40

// Base class constructor for the module (takes instance pointer)
extern void __cdecl moduleConstructor(void* instance); // 0x005dbc10

// Global module instance (size unknown, at 0x00e3f4d0)
extern uint8_t g_moduleInstance[];

// Vtable entries stored as separate globals (contiguous, at 0x011a0f14 - 0x011a0f20)
extern void (*_DAT_011a0f14)();  // vtable[0]
extern void (*_DAT_011a0f18)();  // vtable[1]
extern void (*_DAT_011a0f1c)();  // vtable[2]
extern void (*_DAT_011a0f20)();  // vtable[3]

uint8_t __cdecl registerVtableAndConstruct()
{
    // Set the virtual function table for the module
    _DAT_011a0f14 = impl_1; // +0x00
    _DAT_011a0f18 = impl_2; // +0x04
    _DAT_011a0f1c = impl_3; // +0x08
    _DAT_011a0f20 = impl_4; // +0x0C

    // Call the base class constructor on the global instance
    moduleConstructor(g_moduleInstance);

    return 1; // success
}