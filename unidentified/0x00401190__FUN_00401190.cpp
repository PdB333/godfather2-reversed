// Reversed C++23 source for FUN_00401190 at 0x00401190
// This translation preserves the exact binary semantics described in the decompile.
// The function initializes a control block pointed to by param_1, calls a helper,
// optionally invokes a second helper based on the low bit of param_2, and returns
// the same pointer after wiring up a couple of stateful references.

#include <cstdint>

// Forward declarations matching the original binary's externs.
// In the real project these would come from the actual headers.
extern "C" {
    // Global state storage used by this family of functions
    extern uint32_t DAT_01223378;

    // Pointer to the function table entry to be stored in *param_1
    extern void *PTR_FUN_00e2f050;

    // Lab and helper functions referenced by the decompiled code
    void FUN_00ab6080(uint32_t);
    void FUN_009c8eb0(uint32_t *);
}

// If the project has a distinct LAB/LAB-like symbol, map it here.
// The decompiled code uses PTR_LAB_00e2f054, but the actual address symbol
// should be provided by the real headers. For this reconstruction, we model
// it as a single assignment to a function-table-like slot by casting the label
// to a gray-box pointer constant when available. If not, this line effectively
// stores the address literal for the lab label.
extern void *PTR_LAB_00e2f054;

// The original signature is a thiscall on a void-like block;
// we express the idiomatic C++ equivalent as returning the same type as param_1
// and taking the same first-arg type, plus the flag byte as a second argument.
undefined4* FUN_00401190(undefined4* param_1, uint8_t param_2)
{
    // 1) Set the first slot to point to the function-table entry
    *param_1 = reinterpret_cast<undefined4>(PTR_FUN_00e2f050);

    // 2) Call a helper using the value at offset 0x11 (index 17)
    FUN_00ab6080(param_1[0x11]);

    // 3) Wire up LAB entry (exact address comes from PTR_LAB_00e2f054)
    *param_1 = reinterpret_cast<undefined4>(PTR_LAB_00e2f054);

    // 4) Clear the global state variable used for this subsystem
    DAT_01223378 = 0;

    // 5) If the low bit of param_2 is set, invoke a secondary initializer
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(param_1);
    }

    // 6) Return the original block pointer
    return param_1;
}

// End marker required by the task format
REVERSED_FUNCTION: ::FUN_00401190 (0x00401190)