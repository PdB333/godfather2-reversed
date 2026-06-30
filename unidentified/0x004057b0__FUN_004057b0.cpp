#include <cstdint>

std::int32_t __cdecl FUN_004a8310(std::uint32_t param_1);

struct FUN_004057b0_Context
{
    std::uint8_t  gap_00[0xA4];
    std::uint32_t entries[0x20]; // [0xA4]
    std::uint32_t count;         // [0x124]
};

std::int32_t __thiscall FUN_004057b0(FUN_004057b0_Context* self)
{
    std::int32_t result = 0;
    std::uint32_t index = 0;
    std::uint32_t* entry = self->entries;

    do
    {
        if (self->count <= index)
        {
            return result;
        }

        result = FUN_004a8310(*entry);
        index = index + 1;
        entry = entry + 1;
    } while (result == 0);

    return result;
}