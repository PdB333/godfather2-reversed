#include <cstdint>

extern "C" void __fastcall FUN_00407880(int count);
extern "C" void __fastcall FUN_004d3b50();

struct FUN_00407480_Array
{
    std::uint8_t* entries; // [0x00]
    int count;             // [0x04]
    int capacity;          // [0x08]
};

extern "C" void __fastcall FUN_00407480(FUN_00407480_Array* param_1)
{
    int iVar1 = param_1->capacity;

    if (param_1->count == iVar1) {
        if (iVar1 == 0) {
            iVar1 = 1;
        }
        else {
            iVar1 = iVar1 * 2;
        }

        FUN_00407880(iVar1);
    }

    iVar1 = param_1->count;
    param_1->count = iVar1 + 1;

    if (param_1->entries + iVar1 * 0x10 != nullptr) {
        FUN_004d3b50();
        return;
    }

    return;
}