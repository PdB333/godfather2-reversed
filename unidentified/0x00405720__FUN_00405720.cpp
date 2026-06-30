#include <cstdint>

std::int32_t __cdecl FUN_004a8180(std::uint32_t param_1, std::uint32_t param_2);

struct FUN_00405720_Context
{
    std::uint8_t  gap_00[0x124];
    std::uint32_t count; // [0x124]
};

std::int32_t __thiscall FUN_00405720(
    FUN_00405720_Context* self,
    std::uint32_t param_2,
    std::uint32_t param_3)
{
    std::int32_t result = 0;
    std::uint32_t index = 0;

    do
    {
        if (self->count <= index)
        {
            return result;
        }

        result = FUN_004a8180(param_2, param_3);
        index = index + 1;
    } while (result == 0);

    return result;
}