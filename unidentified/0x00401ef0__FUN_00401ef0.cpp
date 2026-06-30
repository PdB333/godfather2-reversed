#include <cstdint>

void __thiscall FUN_00401ef0(std::uint32_t* param_1, const std::uint32_t* param_2)
{
    *param_1 = ((param_2[0] * 0x21u + param_2[1]) * 0x21u + param_2[2]) * 0x21u + param_2[3];
    return;
}