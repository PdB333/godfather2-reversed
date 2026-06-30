#include <cstdint>

using undefined4 = std::uint32_t;

undefined4 __thiscall FUN_00401970(int param_1, int param_2)
{
    return *reinterpret_cast<undefined4*>(
        *reinterpret_cast<int*>(param_1 + 0x38) + 0x0c + param_2 * 0x10
    );
}