// Reversed C++23 source for FUN_00401130 at 0x00401130
// This translation preserves the exact binary semantics described in the decompile.
// The function initializes a control block pointed to by param_1 and wires up a
// function pointer table entry, then returns the same pointer.
//

#include <cstdint>

// Forward declarations matching the decompiled externs used by the original binary.
// In the actual project these would come from the real headers; here we approximate.
extern "C" {
    // Global data pointer used to store the current control block
    extern uint32_t DAT_01223378;

    // Pointer to the function table entry to be stored in *param_1
    extern void *PTR_FUN_00e2f050;

    // The function at 0x00ab6020 returning a 32-bit value (address-sized)
    extern uint32_t FUN_00ab6020(void);
}

// The reversed function
uint32_t* FUN_00401130(uint32_t *param_1)
{
    // 1) DAT_01223378 = param_1;
    DAT_01223378 = reinterpret_cast<uint32_t>(param_1);

    // 2) *param_1 = &PTR_FUN_00e2f050;
    *param_1 = reinterpret_cast<uint32_t>(PTR_FUN_00e2f050);

    // 3) Initialize known zeroed slots
    param_1[9]  = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;

    // 4) param_1[0x10] = 5;
    param_1[0x10] = 5;

    // 5) param_1[0x12] = 0x4b000;
    param_1[0x12] = 0x4b000;

    // 6) param_1[0x13] = 0;
    param_1[0x13] = 0;

    // 7) param_1[0x14] = 0;
    param_1[0x14] = 0;

    // 8) param_1[1]..param_1[8] = 0
    param_1[1]  = 0;
    param_1[2]  = 0;
    param_1[3]  = 0;
    param_1[4]  = 0;
    param_1[5]  = 0;
    param_1[6]  = 0;
    param_1[7]  = 0;
    param_1[8]  = 0;

    // 9) uVar1 = FUN_00ab6020();
    uint32_t uVar1 = FUN_00ab6020();

    // 10) param_1[0x11] = uVar1;
    param_1[0x11] = uVar1;

    // 11) return param_1;
    return param_1;
}

// End of translation
// REVERSED_FUNCTION: ::FUN_00401130 (0x00401130)