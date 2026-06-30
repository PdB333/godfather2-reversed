#include <cstdint>

struct FUN_004057f0_Entry
{
    std::uint8_t  gap_00[0x8];
    std::uint16_t count; // [0x8]
};

struct FUN_004057f0_Context
{
    std::uint8_t  gap_00[0xA4];
    std::uint32_t entries[0x20]; // [0xA4]
    std::uint32_t count;         // [0x124]
};

std::uint32_t __thiscall FUN_004057f0(FUN_004057f0_Context* self, std::uint32_t param_1)
{
    std::uint32_t index = 0;

    if (self->count == 0)
    {
        return 0;
    }

    std::uint32_t* entry = self->entries;

    while (true)
    {
        const std::uint32_t value = *entry;

        if (!(param_1 < value + 0x10U ||
              value + 0x10U + static_cast<std::uint32_t>(
                  reinterpret_cast<FUN_004057f0_Entry*>(value)->count
              ) * 0x14U <= param_1))
        {
            return self->entries[index];
        }

        index = index + 1;
        entry = entry + 1;

        if (self->count <= index)
        {
            return 0;
        }
    }
}