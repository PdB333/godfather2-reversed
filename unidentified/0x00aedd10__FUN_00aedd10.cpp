// Reconstructed reverse-engineered source for FUN_00aedd10
// Address: 0x00aedd10
//
// Notes:
// - This implementation preserves the original instruction ordering and side-effects.
// - Types match the decompiler's undefined4/undefined2 usage: use uint32_t for undefined4 and uint16_t for undefined2.
// - The global pointer table PTR_PTR_00ef51d4 is declared as an extern pointer-to-pointer so the exact call site
//   (**(code **)(PTR_PTR_00ef51d4 + 8))() can be expressed and invoked exactly as in the binary.
// - All calls and memory accesses are performed with the same ordering as the decompiled output.

#include <cstdint>
#include <cstddef>
extern "C" {

// Represent the decompiler's 'code *' as a function pointer returning uint32_t and taking no parameters.
using IndirectNoArgFn = uint32_t (*)();

// Global pointer table symbol referenced by the original binary: PTR_PTR_00ef51d4
// It is a pointer to an array of function pointers (or to a vtable-like table).
// The original binary performs: uVar1 = (**(code **)(PTR_PTR_00ef51d4 + 8))();
// Which means: read pointer at address (PTR_PTR_00ef51d4 + 8), treat it as pointer-to-function, then call it.
// We represent PTR_PTR_00ef51d4 as pointer-to-uintptr_t so pointer arithmetic matches byte offsets.
extern uintptr_t* PTR_PTR_00ef51d4;

// External callees recovered from cross-references.
uint32_t FUN_00c7e2e0(uint32_t a1, const char* a2, uint32_t a3, uint16_t a4);
void FUN_00c7db90(uint32_t a1, uint32_t a2);

} // extern "C"


// Reverse of: undefined4 __thiscall FUN_00aedd10(int param_1,int param_2,char param_3)
extern "C" uint32_t __thiscall FUN_00aedd10(int param_1, int param_2, char param_3)
{
    // Treat members at offsets using named locals to match decompiler types.
    // thisObj->objPtr  at +0x08 (undefined4)
    // thisObj->stored at +0x0C (undefined4)
    uint32_t objPtr;
    uint32_t indirectResult;
    uint32_t callResult;

    // if (*(int *)(param_1 + 8) == 0) { return 0xffffff36; }
    objPtr = *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_1))) + 8);
    if (objPtr == 0) {
        return 0xFFFFFF36u; // matches undefined4 literal returned by original
    }

    // uVar1 = (**(code **)(PTR_PTR_00ef51d4 + 8))();
    // Preserve exact pointer arithmetic and dereference order from the decompilation:
    // 1) compute PTR_PTR_00ef51d4 + 8 (byte offset)
    // 2) read a pointer (uintptr_t) from that address
    // 3) treat that read value as function pointer and call it
    {
        // Compute address of the pointer-sized slot at PTR_PTR_00ef51d4 + 8 bytes
        // Note: PTR_PTR_00ef51d4 is uintptr_t*; add 8 bytes -> reinterpret as (char*) then add 8 then cast back.
        uintptr_t slot_ptr_value = 0;
        // Read pointer value at byte offset +8 from PTR_PTR_00ef51d4
        auto base = reinterpret_cast<std::uint8_t*>(PTR_PTR_00ef51d4);
        // Read the machine pointer stored at base + 8
        uintptr_t* slot_addr = reinterpret_cast<uintptr_t*>(base + 8);
        slot_ptr_value = *slot_addr;
        // Now treat that value as a function pointer and call it
        IndirectNoArgFn fn = reinterpret_cast<IndirectNoArgFn>(slot_ptr_value);
        indirectResult = fn();
    }

    // *(undefined4 *)(param_1 + 0xc) = uVar1;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_1))) + 0xC) = indirectResult;

    // uVar1 = FUN_00c7e2e0(*(undefined4 *)(param_1 + 8),"fesl.ea.com",*(undefined4 *)(param_2 + 4),
    //                      *(undefined2 *)(param_2 + 8));
    // Prepare arguments preserving types: undefined4, const char*, undefined4, undefined2
    {
        uint32_t arg1 = *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_1))) + 8);
        const char* arg2 = "fesl.ea.com";
        uint32_t arg3 = *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_2))) + 4);
        uint16_t arg4 = *reinterpret_cast<uint16_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_2))) + 8);

        callResult = FUN_00c7e2e0(arg1, arg2, arg3, arg4);
    }

    // if (param_3 != '\0') { FUN_00c7db90(*(undefined4 *)(param_1 + 8),1); }
    if (param_3 != '\0') {
        uint32_t arg_for_db90 = *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(static_cast<std::intptr_t>(param_1))) + 8);
        FUN_00c7db90(arg_for_db90, 1u);
    }

    // return uVar1;
    return callResult;
}

REVERSED_FUNCTION: ::FUN_00aedd10 (0x00aedd10)