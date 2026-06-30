#include <cstdint>

struct FUN_00403530_Object
{
    void** vftable;                      // +0x00
    void** secondaryVftable;             // +0x04
    std::uint8_t pad_08[0x54];
    void* member_5c;                     // +0x5c
    std::uint8_t pad_60[0x10];
    void* member_70;                     // +0x70
    std::uint8_t pad_74[0x04];
    void* member_78;                     // +0x78
    std::uint8_t pad_7c[0x0c];
    std::uint8_t flag_88;                // +0x88
};

extern std::uint32_t DAT_012067a4;

extern void FUN_00406a00();
extern void FUN_00408a00(void* param_1, int param_2);

std::uint8_t __fastcall FUN_00403530(FUN_00403530_Object* self)
{
    reinterpret_cast<void(__thiscall*)(void*)>(self->secondaryVftable[1])(self);

    if (self->member_5c == nullptr) {
        FUN_00406a00();
    }

    if (((self->flag_88 != 0) && (self->member_70 == nullptr)) &&
        (self->member_78 == nullptr)) {
        struct
        {
            std::uint32_t value;
            std::uint32_t zero0;
            std::uint8_t zero1;
        } stackValue{
            DAT_012067a4,
            0,
            0,
        };

        FUN_00408a00(&stackValue, 0);
        self->flag_88 = 0;
    }

    return self->flag_88;
}