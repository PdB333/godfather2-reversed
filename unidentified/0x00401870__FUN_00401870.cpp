#include <cstdint>

struct FUN_00401870_Entry
{
    int handle;          // +0x00
    std::int32_t unk_04; // +0x04
    int accumulated;     // +0x08
    std::int32_t unk_0c; // +0x0c
};

struct FUN_00401870_Object
{
    std::uint8_t pad_00[0x38];
    FUN_00401870_Entry* entries; // +0x38
};

extern int DAT_00e2eff8;

extern void FUN_00abd570();
extern void FUN_00ac3d30(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
extern int FUN_00ac2870(void* param_1);
extern int FUN_00ac28e0();
extern void FUN_00abd5c0();

int __thiscall FUN_00401870(FUN_00401870_Object* self, int index, int param_2, int param_3)
{
    FUN_00401870_Entry* const entry = self->entries + index;

    int result = 0;

    if (((entry->handle != 0) && (param_2 != 0)) && (param_3 != 0)) {
        FUN_00abd570();
        FUN_00ac3d30(entry->handle, param_2, entry->accumulated, 0, param_3, 0, 0, 0, 0xff);

        do {
            result = FUN_00ac2870(&DAT_00e2eff8);
        } while (result == 0);

        result = FUN_00ac28e0();
        entry->accumulated = entry->accumulated + result;
        FUN_00abd5c0();
    }

    return result;
}