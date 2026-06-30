#include <cstdint>

std::int32_t __cdecl FUN_004a8180(std::uint32_t param_1, std::uint32_t param_2);

struct FUN_004056d0_Context
{
    std::uint8_t  gap_00[0xA4];
    std::int32_t  values[32];      // starts at [0xA4]
    std::uint8_t  gap_124_123[0x124 - 0xA4 - sizeof(values)];
    std::uint32_t count;           // [0x124]
};

std::int32_t __cdecl FUN_004056d0(FUN_004056d0_Context* self, std::uint32_t param_2)
{
    std::int32_t result = 0;
    std::uint32_t index = 0;
    std::int32_t* currentValue = &self->values[0];

    do
    {
        if (self->count <= index)
        {
            return result;
        }

        const std::int32_t value = *currentValue;
        const std::int32_t found = FUN_004a8180(param_2, 0);
        if (found != 0)
        {
            result = value;
        }

        index = index + 1;
        currentValue = currentValue + 1;
    } while (result == 0);

    return result;
}