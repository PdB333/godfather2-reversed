// Reversed C++23 source for FUN_004011d0 at 0x004011d0
// This implementation mirrors the exact binary semantics described in the decompile.
// It operates on a small control block pointed to by param_1, stores a function-table
// pointer, calls FUN_00ab6080 with an offset derived value, then writes a lab-label
// pointer back into *param_1 and clears a global flag.

#include <cstdint>

// Forward declarations matching the decompiled externs used by the original binary.
// In the real project these would come from the actual headers.
extern "C" {
    // Global state storage used by this family of functions
    extern uint32_t DAT_01223378;

    // Pointer to the function table entry to be stored in *param_1
    extern void *PTR_FUN_00e2f050;

    // Lab-like symbol label we store into *param_1
    extern void *PTR_LAB_00e2f054;

    // The function at 0x00ab6080 taking a 32-bit value (or pointer-sized) as arg
    void FUN_00ab6080(uint32_t);

    // The memory-mapped structure or block used by this pattern
    // (No explicit type available; using uint32_t* cast as placeholder)
}

// The function implements: 
//   *param_1 = &PTR_FUN_00e2f050;
//   FUN_00ab6080(param_1[0x11]);
//   *param_1 = &PTR_LAB_00e2f054;
//   DAT_01223378 = 0;
void __fastcall FUN_004011d0(uint32_t *param_1)
{
    // Step 1: wire the first slot to the function table entry
    *param_1 = reinterpret_cast<uint32_t>(PTR_FUN_00e2f050);

    // Step 2: call helper with the value stored at offset 0x11 from param_1
    // Note: param_1[0x11] is treated as a 32-bit value (address-sized on 32/64-bit targets)
    FUN_00ab6080(param_1[0x11]);

    // Step 3: wire the first slot to the lab label
    *param_1 = reinterpret_cast<uint32_t>(PTR_LAB_00e2f054);

    // Step 4: clear the global flag
    DAT_01223378 = 0;
}