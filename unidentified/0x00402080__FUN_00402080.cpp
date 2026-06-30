std::uint32_t __thiscall FUN_00402080(int param_1, std::uint32_t* param_2)
{
    std::uint32_t uVar1;
    std::uint32_t uVar2;
    int iVar3;
    bool bVar4;

    uVar2 = *reinterpret_cast<std::uint32_t*>(param_1 + 4);
    iVar3 = *reinterpret_cast<int*>(param_1 + 8);

    if ((~static_cast<std::uint8_t>(uVar2 >> 2) & 1) != 0) {
        if (iVar3 != 0) {
            for (uVar2 = *reinterpret_cast<std::uint32_t*>(iVar3 + ((*param_2 & 3) * 4));
                 uVar2 != 0;
                 uVar2 = *reinterpret_cast<std::uint32_t*>(uVar2 + 8)) {
                if (*reinterpret_cast<std::uint32_t*>(uVar2 + 0x10) == *param_2) {
                    return (uVar2 & 0xffffff00) | 1;
                }
            }
        }
        return uVar2 & 0xffffff00;
    }

    uVar1 = *param_2;
    if (((uVar2 >> 3) & 1) == 0) {
        iVar3 = *reinterpret_cast<int*>(iVar3 + ((uVar1 & 0x1f) * 4));
        bVar4 = iVar3 == 0;
        if (bVar4) {
            goto LAB_00402105;
        }
        while (*reinterpret_cast<std::uint32_t*>(iVar3 + 0x10) != uVar1) {
            iVar3 = *reinterpret_cast<int*>(iVar3 + 8);
            if (iVar3 == 0) {
                return 0;
            }
        }
    }
    else {
        iVar3 = *reinterpret_cast<int*>(iVar3 + ((uVar1 & 0xff) * 4));
        bVar4 = iVar3 == 0;
        if (bVar4) {
            goto LAB_00402105;
        }
        do {
            if (*reinterpret_cast<std::uint32_t*>(iVar3 + 0x10) == uVar1) {
                break;
            }
            iVar3 = *reinterpret_cast<int*>(iVar3 + 8);
        } while (iVar3 != 0);
    }

    bVar4 = iVar3 == 0;

LAB_00402105:
    return (static_cast<std::uint32_t>(iVar3) & 0xffffff00) |
           static_cast<std::uint32_t>(!bVar4);
}