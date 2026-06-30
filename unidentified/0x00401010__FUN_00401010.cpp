// Reconstructed function: FUN_00401010 at 0x00401010
// Mirror the exact binary logic: if the input pointer is NULL, return the address
// of DAT_0120546e; otherwise return the value pointed to by param_1.
//
// NOTE: The symbol DAT_0120546e is represented here as an external symbol reference
// to match the original binary's data section. The return type is an unsigned 8-bit
// pointer (undefined1* in the decompiler), which corresponds to uint8_t* in C++.

#include <cstdint>

extern "C" {
    // External data symbol expected from the original binary's data segment.
    // The actual content is not used by this function; only its address is needed.
    extern uint8_t DAT_0120546e;
}

// The function preserves the parameter and return typing as in the decompiled form.
// It accepts a pointer to a 32-bit value; the value itself is interpreted as a
// pointer (or NULL). The cast/interpretation mirrors the original code's behavior.
extern "C" uint8_t* FUN_00401010(uint32_t* param_1) {
    uint8_t* puVar1;

    // Interpret the 32-bit value at *param_1 as a pointer to uint8_t.
    puVar1 = reinterpret_cast<uint8_t*>(*param_1);

    // If the resulting pointer is null, fall back to DAT_0120546e.
    if (puVar1 == nullptr) {
        puVar1 = &DAT_0120546e;
    }

    return puVar1;
}