#include <cstdint>

extern int FUN_004025a0(std::uint32_t param_1);
extern void FUN_00402920(int param_1, std::uint32_t param_2);

void FUN_004035c0(std::uint32_t param_1, std::uint32_t param_2)
{
    const int object = FUN_004025a0(param_1);

    if (object != 0) {
        FUN_00402920(object + 0x56, param_2);
    }
}