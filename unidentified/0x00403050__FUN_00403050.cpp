#include <cstdint>

using uint = std::uint32_t;

struct FUN_00403050_Object
{
    std::uint8_t pad_00[0x1c];
    std::uint32_t value_1c;      // +0x1c
    std::uint8_t pad_20[0x04];
    int state_24;                // +0x24
    std::uint8_t pad_28[0x38];
    std::uint32_t flags_60;      // +0x60
    std::uint8_t pad_64[0x88];
    std::uint32_t bitIndex_ec;   // +0xec
};

struct DAT_0122337c_State
{
    std::uint8_t pad_00[0x128];
    std::uint32_t values[10];    // +0x128
    std::uint32_t count;         // +0x150
};

extern DAT_0122337c_State* DAT_0122337c;

void FUN_00403050(FUN_00403050_Object* self)
{
    self->flags_60 = self->flags_60 & 0xbfffffff;

    if (((-1 < static_cast<int>(self->flags_60)) && (self->state_24 == 3)) &&
        ((self->flags_60 & ((1U << (static_cast<std::uint8_t>(self->bitIndex_ec) & 0x1f)) - 1U)) == 0))
    {
        std::uint32_t* const puVar1 = &DAT_0122337c->count;

        if (DAT_0122337c->count < 10) {
            DAT_0122337c->values[DAT_0122337c->count] = self->value_1c;
            *puVar1 = *puVar1 + 1;
        }
    }
}