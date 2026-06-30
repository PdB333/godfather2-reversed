#include <cstdint>

using undefined1 = std::uint8_t;
using undefined4 = std::uint32_t;

extern "C" void FUN_00abd570();
extern "C" void FUN_00ab64e0(int a1, int a2);
extern "C" void FUN_00ac4290(
    int a1,
    undefined4 a2,
    int a3,
    int a4,
    int a5,
    int a6,
    void* a7,
    void* a8,
    int a9
);
extern "C" void FUN_00ab5130(void* param_1);
extern "C" int FUN_00ac2870(void* param_1);
extern "C" int FUN_00ac28e0();
extern "C" void FUN_00ab50b0();
extern "C" void FUN_00abd5c0();

extern "C" std::uint8_t DAT_00e2eff8;
extern "C" std::uint8_t DAT_00e2effc;
extern "C" void LAB_00401760();

class Context {
public:
    struct Entry {
        int value;                  // +0x00
        std::uint8_t active;        // +0x04
        std::uint8_t pad05;         // +0x05
        std::uint8_t pad06;         // +0x06
        std::uint8_t nameUsed;      // +0x07
        std::uint32_t cachedValue;  // +0x08
        std::uint32_t computedValue;// +0x0C
    };

    Entry* entries() {
        return *reinterpret_cast<Entry**>(reinterpret_cast<std::uint8_t*>(this) + 0x38);
    }

    const Entry* entries() const {
        return *reinterpret_cast<Entry* const*>(reinterpret_cast<const std::uint8_t*>(this) + 0x38);
    }

    int FUN_00401780(int param_2, undefined4 param_3, int param_4) {
        int iVar1;
        int* piVar2;
        undefined1 local_68[100];

        piVar2 = reinterpret_cast<int*>(param_2 * 0x10 + reinterpret_cast<int>(entries()));
        if (*piVar2 != 0) {
            iVar1 = piVar2[2];
            if (static_cast<std::uint32_t>(piVar2[3]) < static_cast<std::uint32_t>(iVar1 + param_4)) {
                param_4 = piVar2[3] - iVar1;
            }
            if (param_4 != 0) {
                FUN_00abd570();
                FUN_00ab64e0(0, 1);
                FUN_00ac4290(*piVar2, param_3, iVar1, 0, param_4, 0, reinterpret_cast<void*>(&LAB_00401760), local_68, 0xff);
                FUN_00ab5130(&DAT_00e2effc);
                iVar1 = FUN_00ac2870(&DAT_00e2eff8);
                if (iVar1 == 1) {
                    iVar1 = FUN_00ac28e0();
                }
                else {
                    iVar1 = 0;
                }
                piVar2[2] = piVar2[2] + iVar1;
                FUN_00ab50b0();
                FUN_00abd5c0();
                return iVar1;
            }
        }
        return 0;
    }
};