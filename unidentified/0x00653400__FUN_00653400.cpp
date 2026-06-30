extern "C" std::uint32_t __fastcall FUN_00653400(std::uint32_t param_1, int unaff_ESI)
{
    std::uint32_t uVar1;
    std::uint32_t uVar2;
    std::uint32_t uVar3;
    int iVar4;
    std::uint32_t uVar5;
    std::uint32_t uVar6;
    int iVar7;
    float fVar8;
    std::uint32_t local_10;
    std::uint32_t local_c;
    std::uint32_t local_8;
    alignas(4) std::uint8_t uStack_4[8];

    iVar4 = static_cast<int>(param_1);
    param_1 = 0;
    FUN_0064b9e0(2, &param_1);
    uVar2 = param_1 & 3;

    param_1 = 0;
    FUN_0064b9e0(5, &param_1);
    uVar6 = param_1 & 0x1f;

    if (*reinterpret_cast<std::uint32_t*>(iVar4 + 0x2c) < *reinterpret_cast<std::uint32_t*>(iVar4 + 0x18)) {
        *reinterpret_cast<std::uint8_t*>(iVar4 + 0x1c) = 1;
    } else {
        *reinterpret_cast<std::uint32_t*>(iVar4 + 0x18) =
            *reinterpret_cast<std::uint32_t*>(iVar4 + 0x18) + 1;
    }

    local_10 = 0;
    FUN_0064b9e0(6, &local_10);

    param_1 = 0;
    FUN_0064b9e0(10, &param_1);
    uVar5 = param_1 & 0x3ff;

    param_1 = 0;
    FUN_0064b9e0(0, &param_1);

    local_8 = *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x90);
    local_10 = uVar6 | (local_10 & 0x3f) << 5 | local_8 & 0xfffff800;

    if (local_10 < local_8) {
        local_10 = local_10 + 0x800;
    }

    if (local_10 - local_8 < 0x20) {
        local_8 = *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x94);
        uVar5 = uVar5 | local_8 & 0xfffffc00;

        if (uVar5 < local_8) {
            uVar5 = uVar5 + 0x400;
        }

        if (uVar5 <= *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x98)) {
            if (*reinterpret_cast<int*>(unaff_ESI + 0x1b0) != 0) {
                FUN_0065a6c0(*reinterpret_cast<int*>(unaff_ESI + 0x1b0), local_10, uVar5, uVar2);
                local_8 = FUN_0064ca10(iVar4, *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x1b0));
                if (static_cast<char>(local_8) == '\0') {
                    goto LAB_0065374c;
                }
            }

            iVar7 = 0;
            local_8 = FUN_00652840(iVar4);
            if ((local_8 < 5) && (uVar2 < 3)) {
                local_c = local_8 + 3 >> 2;
                param_1 = 0;

                if (local_c != 0) {
                    do {
                        if (param_1 == local_c - 1) {
                            iVar4 = static_cast<int>((local_8 - iVar7) * 8);
                        } else {
                            iVar4 = 0x20;
                        }

                        uVar3 = FUN_0064bca0(iVar4);
                        *reinterpret_cast<std::uint32_t*>(uStack_4 + iVar7) = uVar3;

                        param_1 = param_1 + 1;
                        iVar7 = iVar7 + 4;
                    } while (param_1 < local_c);
                }

                param_1 = 0;
                FUN_0064b9e0(8, &param_1);
                local_8 = (param_1 & 0xff) * 8 + 4;

                uVar6 = local_10 - *reinterpret_cast<int*>(unaff_ESI + 0x90);
                if (0x20 < uVar6) {
                    iVar4 = static_cast<int>((uVar6 - 0x21) >> 5) + 1;
                    do {
                        uVar6 = uVar6 - 0x20;
                        iVar4 = iVar4 + -1;
                    } while (iVar4 != 0);

                    *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x9c) = 0;
                }

                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x9c) =
                    *reinterpret_cast<int*>(unaff_ESI + 0x9c) << (static_cast<std::uint8_t>(uVar6) & 0x1f) |
                    static_cast<std::uint32_t>(uVar2 == 0);

                local_c = uVar5 - *reinterpret_cast<int*>(unaff_ESI + 0x94);
                uVar6 = 0;

                if (local_c != 0) {
                    do {
                        uVar1 = *reinterpret_cast<int*>(unaff_ESI + 0x94) + 1 + uVar6;
                        param_1 =
                            (param_1 & 0xffffff00) |
                            static_cast<std::uint32_t>(
                                ((((reinterpret_cast<std::uint32_t*>(uStack_4))[uVar5 - uVar1 >> 5] &
                                   (1u << ((static_cast<char>(uVar5) - static_cast<char>(uVar1)) & 0x1fU)))) != 0));

                        *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xac) = 0;
                        FUN_00653b10();

                        if ((*reinterpret_cast<int*>(unaff_ESI + 0xac) != 0) &&
                            ((fVar8 =
                                  static_cast<float>(
                                      static_cast<int>(
                                          (*reinterpret_cast<int*>(*reinterpret_cast<int*>(unaff_ESI + 0x1a4) + 100) -
                                           *reinterpret_cast<int*>(unaff_ESI + 0xac)) -
                                          static_cast<int>(local_8))) *
                                      DAT_00e2fc48 +
                                  *reinterpret_cast<float*>(unaff_ESI + 0xc0) * DAT_0110a440,
                              *reinterpret_cast<float*>(unaff_ESI + 0xc0) = fVar8,
                              fVar8 < 0.0f))) {
                            *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xc0) = 0;
                        }

                        if (static_cast<char>(param_1) != '\0') {
                            *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xa0) =
                                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x10 + (uVar1 & 0x1f) * 4);
                        }

                        uVar6 = uVar6 + 1;
                    } while (uVar6 < local_c);
                }

                if (0x20 < local_10 - *reinterpret_cast<int*>(unaff_ESI + 0xa0)) {
                    *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xa0) = local_10 - 0x20;
                }

                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x94) = uVar5;
                uVar6 = *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x90);
                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x118) = 0;
                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x114) = 0;
                *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x90) = local_10;

                if ((uVar2 == 1) || (0x10 < local_10 - *reinterpret_cast<int*>(unaff_ESI + 0xa0))) {
                    FUN_00653a60();
                }

                if ((uVar6 != local_10) && (uVar2 == 0)) {
                    return 1;
                }

                return 0;
            }
        }
    }

LAB_0065374c:
    return local_8 & 0xffffff00;
}