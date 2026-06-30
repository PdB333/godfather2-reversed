// Reversed faithful C++23 for FUN_004014f0 at 0x004014f0
// This translation preserves the control flow, data access patterns, and
// external calls as observed in the decompiled function.
// Note: Offsets on the object pointed to by param_1 are mapped to explicit member names.

#include <cstdint>

class Context {
public:
    // Offsets observed: 0x24 (count), 0x28 (array base?), 0x2c (last item or cached uVar2)
    // For fidelity, we expose the exact offset accessors used by FUN_004014f0.
    int get_count() const { return *reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(this) + 0x24); }
    void set_count(int v) { *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x24) = v; }

    int get_slot(int idx) const {
        const int* base = reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(this) + 0x28);
        return base[idx];
    }
    void set_slot(int idx, int value) {
        int* base = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x28);
        base[idx] = value;
    }

    // The 0x34 field used in call: *(undefined4 *)(param_1 + 0x34)
    uint32_t get_field34() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x34); }

    // The 0x38/0x3C/0x40 fields exist conceptually as handles/counts used by the function;
    // We expose accessors only as needed by the translated logic.
    uint32_t get_field38() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x38); }
    uint32_t get_field3C() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x3C); }
    uint32_t get_field40() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x40); }

    // The 0x30 field is updated with the result of FUN_00ac2100
    void set_field30(uint32_t v) { *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x30) = v; }
};

// Forward declarations of external functions (prototypes derived from usage)
extern "C" {
    // iVar1 = FUN_009c8e50(0x20);
    int FUN_009c8e50(int);

    // uVar2 = FUN_00b90190(*(undefined4 *)(param_1 + 0x34));
    uint32_t FUN_00b90190(uint32_t);

    // FUN_00ac2090(uVar2,0) and FUN_00ac2090(&DAT_00e273dc,1)
    void FUN_00ac2090(uint32_t, int);

    // uVar2 = FUN_00ac2100(uVar2,uVar4);
    uint32_t FUN_00ac2100(uint32_t, uint32_t);

    // FUN_00ac1120(puVar3,uVar4);
    void FUN_00ac1120(void*, uint32_t);

    // iVar1 = FUN_00b901d0(param_2,0);
    int FUN_00b901d0(uint32_t, int);
}

// Global data symbol used in the decompiled code
extern "C" {
    extern uint8_t DAT_012051f8;
    extern void *DAT_00e273dc;
}

// The function uses a single-threaded "initialized" flag at DAT_012051f8.
// When zero, it performs a one-time initialization sequence.
bool __thiscall FUN_004014f0(int param_1, uint32_t param_2)
{
    int iVar1;
    uint32_t uVar2;
    uint8_t* puVar3;
    uint32_t uVar4;

    if (DAT_012051f8 == '\0') {
        iVar1 = FUN_009c8e50(0x20);
        if (iVar1 == 0) {
            uVar2 = 0;
        } else {
            uVar2 = FUN_00b90190(*reinterpret_cast<uint32_t*>(param_1 + 0x34));
        }
        uVar4 = 0;

        // store uVar2 into param_1 + 0x2c
        *reinterpret_cast<uint32_t*>(param_1 + 0x2c) = uVar2;

        FUN_00ac2090(uVar2, 0);

        uVar2 = FUN_00ac2100(uVar2, uVar4);

        uVar4 = 1;

        puVar3 = reinterpret_cast<uint8_t*>(&DAT_00e273dc);
        // store new value into param_1 + 0x30
        *reinterpret_cast<uint32_t*>(param_1 + 0x30) = uVar2;

        FUN_00ac2090(reinterpret_cast<uint32_t>(&DAT_00e273dc), 1);
        FUN_00ac1120(puVar3, uVar4);
    }

    iVar1 = FUN_00b901d0(param_2, 0);
    if (iVar1 != 0) {
        // Write iVar1 into the next available slot: param_1 + 4 + count*4
        int count = *reinterpret_cast<int*>(param_1 + 0x24);
        *reinterpret_cast<int*>(param_1 + 4 + count * 4) = iVar1;
        // Increment the count
        *reinterpret_cast<int*>(param_1 + 0x24) = count + 1;
    }

    if (*reinterpret_cast<int*>(param_1 + 0x24) != 0) {
        DAT_012051f8 = '\x01';
    }

    return *reinterpret_cast<int*>(param_1 + 0x24) != 0;
}

// End of reversed function block

/* REVERSED_FUNCTION: ::FUN_004014f0 (0x004014f0) */