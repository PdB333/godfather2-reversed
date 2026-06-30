#include <cstdint>

using undefined4 = std::uint32_t;

static inline int CONCAT31(std::uint32_t high3, std::uint8_t low1)
{
    return static_cast<int>(((high3 & 0x00ffffffU) << 8) | static_cast<std::uint32_t>(low1));
}

int FUN_00401e20(undefined4* param_1, undefined4* param_2)
{
    std::uint8_t bVar1;
    std::uint32_t uVar4;
    const std::uint8_t* pbVar2;
    int iVar3;
    const std::uint8_t* pbVar5;
    bool bVar6;

    iVar3 = static_cast<int>(param_1[1]);
    uVar4 = static_cast<std::uint32_t>(iVar3) >> 8;

    if (iVar3 != static_cast<int>(param_2[1])) {
        return static_cast<int>(uVar4 << 8);
    }

    if (iVar3 == 0) {
        return CONCAT31(uVar4, 1);
    }

    pbVar5 = reinterpret_cast<const std::uint8_t*>(static_cast<std::uintptr_t>(param_2[0]));
    pbVar2 = reinterpret_cast<const std::uint8_t*>(static_cast<std::uintptr_t>(param_1[0]));

    while (true) {
        bVar1 = *pbVar2;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
            break;
        }

        if (bVar1 == 0) {
            return CONCAT31(0, 1);
        }

        bVar1 = pbVar2[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) {
            break;
        }

        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;

        if (bVar1 == 0) {
            return CONCAT31(0, 1);
        }
    }

    iVar3 = (1 - static_cast<std::uint32_t>(bVar6)) - static_cast<std::uint32_t>(bVar6 != 0);
    return CONCAT31(static_cast<std::uint32_t>(iVar3) >> 8, static_cast<std::uint8_t>(iVar3 == 0));
}