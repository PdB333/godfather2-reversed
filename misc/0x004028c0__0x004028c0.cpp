#include <cstdint>

using undefined = void;

extern std::uint32_t DAT_0110ae8c;
extern std::int16_t DAT_01161380[0x1ff * 4];
extern std::uint16_t _DAT_01162378;

void FUN_004028c0()
{
    std::uint32_t uVar1;

    uVar1 = 0;
    DAT_0110ae8c = 0;
    do {
        DAT_01161380[uVar1 * 4] = static_cast<std::int16_t>(uVar1) + 1;
        uVar1 = uVar1 + 1;
    } while (uVar1 < 0x1ff);
    _DAT_01162378 = 0xffff;
    return;
}