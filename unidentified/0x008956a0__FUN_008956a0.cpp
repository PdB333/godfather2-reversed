// FUNC_NAME: UnknownClass::constructor

#include <cstdint>

// Reconstructed constructor at 0x008956a0
// This function initializes an object with multiple virtual function tables (vtables) and zeroes many fields.
void* __thiscall UnknownClass::constructor(void* thisPtr, uint32_t initializationParam) {
    // Call some base initialization function with the given parameter (not with this)
    // FUN_0046c590 likely initializes a separate object or performs a base class operation
    extern void baseInitialize(uint32_t param);
    baseInitialize(initializationParam);

    // Set primary vtable at offset 0x00
    *(void**)(thisPtr) = (void*)&PTR_FUN_00d77984;  // +0x00: primary vtable

    // Set secondary vtable at offset 0x3C
    *(void**)((uint8_t*)thisPtr + 0x3C) = (void*)&PTR_LAB_00d77974;  // +0x3C: vtable2

    // Set vtable at offset 0x48
    *(void**)((uint8_t*)thisPtr + 0x48) = (void*)&PTR_LAB_00d77970;  // +0x48: vtable3

    // First set vtable at offset 0x50 to a purecall stub (abstract interface)
    *(void**)((uint8_t*)thisPtr + 0x50) = (void*)&PTR___purecall_00d77960;  // +0x50: temporary purecall vtable

    // Zero out various fields
    *(uint32_t*)((uint8_t*)thisPtr + 0x54) = 0;  // +0x54: member (int)
    *(uint32_t*)((uint8_t*)thisPtr + 0x58) = 0;  // +0x58: member (int)
    *(uint32_t*)((uint8_t*)thisPtr + 0x5C) = 0;  // +0x5C: member (int)
    *(uint16_t*)((uint8_t*)thisPtr + 0x62) = 0;  // +0x62: short member
    *(uint32_t*)((uint8_t*)thisPtr + 0x64) = 0;  // +0x64: member (int)
    *(uint16_t*)((uint8_t*)thisPtr + 0x6A) = 0;  // +0x6A: short member
    *(uint32_t*)((uint8_t*)thisPtr + 0x6C) = 0;  // +0x6C: member (int)
    *(uint32_t*)((uint8_t*)thisPtr + 0x70) = 0;  // +0x70: member (int)
    *(uint16_t*)((uint8_t*)thisPtr + 0x72) = 0;  // +0x72: short member
    *(uint32_t*)((uint8_t*)thisPtr + 0x74) = 0;  // +0x74: member (int)

    // Overwrite the vtable at offset 0x50 with the final table
    *(void**)((uint8_t*)thisPtr + 0x50) = (void*)&PTR_LAB_00d77968;  // +0x50: final vtable4

    return thisPtr;
}