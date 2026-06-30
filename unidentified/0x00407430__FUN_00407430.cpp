#include <cstdint>

extern "C" void FUN_009c8f10(void* ptr);

struct FUN_00407430_Entry
{
    void* object;                             // [0x00]
    std::uint32_t field_0x04;                // [0x04]
    std::uint32_t field_0x08;                // [0x08]
    void (__fastcall* destroy)(void*);       // [0x0C]
};

struct FUN_00407430_Array
{
    FUN_00407430_Entry* entries; // [0x00]
    int count;                   // [0x04]
};

extern "C" void __fastcall FUN_00407430(FUN_00407430_Array* param_1)
{
    int iVar2 = param_1->count + -1;
    if (-1 < iVar2) {
        int iVar3 = iVar2 * 0x10;
        do {
            void* const iVar1 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(param_1->entries) + iVar3);
            if (iVar1 != nullptr) {
                (*reinterpret_cast<void (__fastcall**)(void*)>(
                    reinterpret_cast<std::uint8_t*>(param_1->entries) + iVar3 + 0xc))(iVar1);
            }
            iVar2 = iVar2 + -1;
            iVar3 = iVar3 + -0x10;
        } while (-1 < iVar2);
    }

    if (param_1->entries != nullptr) {
        FUN_009c8f10(param_1->entries);
    }
}