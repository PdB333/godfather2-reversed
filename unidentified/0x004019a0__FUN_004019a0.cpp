#include <cstdint>

extern void FUN_00abd570();
extern void FUN_00ac41a0(std::uint32_t param_1, int param_2, int param_3, int param_4, int param_5);
extern int FUN_00ac28b0();
extern void FUN_00abd5c0();

bool FUN_004019a0(std::uint32_t param_1)
{
    FUN_00abd570();
    FUN_00ac41a0(param_1, 0, 0, 0, 0xff);
    const int result = FUN_00ac28b0();
    FUN_00abd5c0();
    return result != 0;
}