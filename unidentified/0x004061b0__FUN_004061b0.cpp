#include <cstdint>

extern "C" std::int32_t FUN_004025a0(std::int32_t value);
extern "C" void FUN_00403050();

void FUN_004061b0(std::int32_t param_1)
{
    if (FUN_004025a0(param_1) != 0) {
        FUN_00403050();
    }
}