// Reversed: ::FUN_00405a80 (0x00405a80)

#include <cstdint>

class Context42 {
public:
    // Minimal scaffolding to mirror the decompiled layout
    // Adjust member names to reflect project conventions
    int* vptr;             // not used, placeholder for thiscall
    uint8_t pad0[0x80];      // offset 0x80
    int* some_ptr_0x80;      // at offset 0x80, used as base for iVar1
    int pad1;
    // ...
    int* field_0x6C;           // at offset 0x6C, used as iVar1 in loop
    // The actual layout is inferred from the decompiled function

    // The function we expose as a static wrapper to mimic thiscall behavior
    static uint32_t FUN_00405a80(Context42* this_, int* param_2) {
        // local copies to mimic int iVar1, iVar2
        int iVar1;
        int iVar2;

        // iVar1 = *(int *)(param_1 + 0x80);
        iVar1 = *(reinterpret_cast<int*>(reinterpret_cast<char*>(this_) + 0x80));

        // iVar2 = ((*param_2 * 0x21 + param_2[1]) * 0x21 + param_2[2]) * 0x21 + param_2[3];
        // param_2 is int*
        iVar2 = (static_cast<int>(param_2[0]) * 0x21 + param_2[1]);
        iVar2 = (iVar2 * 0x21) + param_2[2];
        iVar2 = (iVar2 * 0x21) + param_2[3];

        // if ((iVar1 != 0) && (*(int *)(iVar1 + 0x2c) == iVar2)) { return *(undefined4 *)(iVar1 + 0x1c); }
        if (iVar1 != 0) {
            int v = *(reinterpret_cast<int*>(reinterpret_cast<char*>(iVar1) + 0x2c));
            if (v == iVar2) {
                return *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(iVar1) + 0x1c);
            }
        }

        // iVar1 = *(int *)(param_1 + 0x6c);
        iVar1 = *(reinterpret_cast<int*>(reinterpret_cast<char*>(this_) + 0x6C));

        // while (true) { if (iVar1 == 0) { return 0; } if (*(int *)(iVar1 + 0x2c) == iVar2) break; iVar1 = *(int *)(iVar1 + 4); }
        while (true) {
            if (iVar1 == 0) {
                return 0;
            }
            int at2c = *(reinterpret_cast<int*>(reinterpret_cast<char*>(iVar1) + 0x2c));
            if (at2c == iVar2) {
                break;
            }
            iVar1 = *(reinterpret_cast<int*>(reinterpret_cast<char*>(iVar1) + 4));
        }

        // return *(undefined4 *)(iVar1 + 0x1c);
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(iVar1) + 0x1c);
    }

    // Helper to illustrate usage in C++23 style (not required for external linkage)
    uint32_t call_FUN_00405a80(int* param_2) {
        return FUN_00405a80(this, param_2);
    }
};

// Note: This reconstruction preserves the exact logic/order of operations from the Ghidra decomp,
// while mapping offsets to plausible member access as per project conventions.
// The real project would replace Context42 with the actual class name and proper member fields.


// End of reversed function representation
REVERSED_FUNCTION: ::FUN_00405a80 (0x00405a80)