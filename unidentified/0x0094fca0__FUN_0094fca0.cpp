// FUNC_NAME: SomeClass::constructor
// Address: 0x0094fca0
// Role: Constructor for a class with multiple inheritance (vtable pointers at offsets 0, 4, and 0x4C).
// Sets global flag g_bInitialized = 0, calls base initialization, and optionally calls a cleanup function if param_2 & 1.

#include <cstdint>

// Forward declarations for external functions
void __thiscall FUN_005c16e0(void* this); // Base class initialization
void __thiscall FUN_005c4480(void* this); // Possibly destructor or cleanup

// Global variable
extern int32_t g_bInitialized; // DAT_01130004

// Vtable pointers (external symbols)
extern void* PTR_FUN_00d8bb28; // Primary vtable
extern void* PTR_LAB_00d8bb04; // Secondary vtable (offset +0x04)
extern void* PTR_LAB_00d8bb00; // Tertiary vtable (offset +0x4C) - first assignment
extern void* PTR_LAB_00d8bafc; // Tertiary vtable (offset +0x4C) - second assignment (overwrites)

class SomeClass {
public:
    // Constructor
    // param_2: bit 0 indicates whether to call cleanup function (e.g., for heap-allocated objects)
    void* __thiscall constructor(uint8_t param_2) {
        // Set vtable pointers for multiple inheritance
        *(void**)this = &PTR_FUN_00d8bb28;          // +0x00: primary vtable
        *(void**)((uint8_t*)this + 4) = &PTR_LAB_00d8bb04; // +0x04: secondary vtable
        // Note: The decompiler shows two consecutive assignments to offset +0x4C.
        // This may be a decompilation artifact; we assume the second overwrites the first.
        *(void**)((uint8_t*)this + 0x4C) = &PTR_LAB_00d8bb00; // +0x4C: tertiary vtable (first)
        *(void**)((uint8_t*)this + 0x4C) = &PTR_LAB_00d8bafc; // +0x4C: tertiary vtable (second, overwrites)

        // Reset global initialization flag
        g_bInitialized = 0;

        // Call base class initialization
        FUN_005c16e0(this);

        // If bit 0 of param_2 is set, call cleanup function (e.g., for heap-allocated objects)
        if ((param_2 & 1) != 0) {
            FUN_005c4480(this);
        }

        return this;
    }
};