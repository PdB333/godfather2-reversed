std::uint32_t __thiscall block(
    int param_1,
    int* param_2,
    float param_3,
    char* param_4,
    std::uint32_t param_5)
{
    std::uint32_t* puVar1;
    float fVar2;
    std::uint8_t bVar3;
    undefined4* puVar5;
    int iVar6;
    std::uint32_t uVar7;
    std::uint32_t uVar8;
    int* piVar9;
    int iVar10;
    undefined1* puVar11;
    std::uint8_t* pbVar12;
    std::uint32_t local_bc;
    std::uint32_t local_b8;
    std::uint32_t local_b4;
    std::uint32_t local_b0;
    undefined1* local_a8 = nullptr;
    void (__cdecl* local_9c)(undefined1*) = nullptr;
    undefined1* local_98 = nullptr;
    void (__cdecl* local_8c)(undefined1*) = nullptr;
    std::uint32_t auStack_88[33];

    local_b0 = param_5;

    FUN_00401d30(*reinterpret_cast<undefined4*>(*param_2 + 4), &DAT_00e2f0a0);

    if ((param_4 != nullptr) && (*param_4 != '\0')) {
        iVar6 = *reinterpret_cast<int*>(*param_2);
        local_bc = 0;

        if (*reinterpret_cast<int*>(param_1 + 0x48) != 0) {
            piVar9 = *reinterpret_cast<int**>(param_1 + 0x44);

            do {
                if (*piVar9 == iVar6) {
                    pbVar12 = reinterpret_cast<std::uint8_t*>(*reinterpret_cast<int*>(*param_2 + 4));
                    iVar10 = 0;

                    if ((pbVar12 != nullptr) && ((bVar3 = *pbVar12), bVar3 != 0)) {
                        iVar10 = 0;

                        do {
                            std::uint32_t uVar4 = static_cast<std::uint32_t>(bVar3);
                            pbVar12 = pbVar12 + 1;

                            if (uVar4 - 0x41 < 0x1a) {
                                uVar4 = uVar4 + 0x20;
                            }

                            iVar10 = iVar10 * 0x1003f + static_cast<int>(uVar4);
                            bVar3 = *pbVar12;
                        } while (bVar3 != 0);
                    }

                    iVar10 = FUN_004db3a0(iVar10, &DAT_00e2f0a0, 4);

                    if (iVar10 == piVar9[1]) {
                        puVar5 = reinterpret_cast<undefined4*>(piVar9[2] * 0x10 + *reinterpret_cast<int*>(param_1 + 0x154));
                        FUN_004d41f0(0, puVar5[0], 0, puVar5[1]);
                        local_b0 = param_5 | 4;
                        break;
                    }
                }

                local_bc = local_bc + 1;
                piVar9 = piVar9 + 5;
            } while (local_bc < *reinterpret_cast<std::uint32_t*>(param_1 + 0x48));
        }
    }

    puVar11 = local_a8;
    if (local_a8 == nullptr) {
        puVar11 = &DAT_0120546e;
    }

    if (*reinterpret_cast<int*>(*param_2) == 0) {
        local_b4 = FUN_00405900(puVar11, 0);
    } else {
        local_b4 = FUN_004059b0(*reinterpret_cast<int*>(*param_2));
    }

    if (local_b4 != 0) {
        iVar6 = FUN_004025a0(local_b4);

        if ((*reinterpret_cast<int*>(iVar6 + 0x24) == 2) || (*reinterpret_cast<int*>(iVar6 + 0x24) == 4)) {
            local_b4 = 0;
        }
    }

    if (local_b4 == 0) {
        uVar7 =
            static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(reinterpret_cast<int>(param_2) + 10) & 1) +
            static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(param_2 + 2));

        std::uint32_t uVar4 = 0;

        if (uVar7 != 0) {
            do {
                iVar6 = *reinterpret_cast<int*>(param_2[4] + uVar4 * 4);
                iVar10 = FUN_00405fd0(param_2, iVar6);

                if (iVar10 == 0) {
                    uVar8 = FUN_00403a50(
                        *reinterpret_cast<undefined4*>(iVar6 + 4),
                        static_cast<float>(uVar7) + param_3 + DAT_00e2b1a4,
                        param_5 | 0x1a,
                        0,
                        0);
                } else {
                    fVar2 = static_cast<float>(static_cast<int>(uVar4));
                    if (static_cast<int>(uVar4) < 0) {
                        fVar2 = fVar2 + DAT_00e44578;
                    }

                    uVar8 = FUN_00403c40(iVar10, fVar2 + param_3, param_4, param_5 | 0x18);
                }

                if (uVar8 == 0) {
                    goto LAB_0040404d;
                }

                auStack_88[uVar4] = uVar8;
                uVar4 = uVar4 + 1;
            } while (uVar4 < uVar7);
        }

        puVar11 = local_a8;
        if (local_a8 == nullptr) {
            puVar11 = &DAT_0120546e;
        }

        local_b4 = FUN_00404590(param_1, *reinterpret_cast<undefined4*>(*param_2), puVar11, param_3, local_b0);

        if (local_b4 != 0) {
            local_bc = 0;

            for (puVar1 = *reinterpret_cast<std::uint32_t**>(
                     *reinterpret_cast<int*>(param_1 + 0x50) +
                     (local_b4 % *reinterpret_cast<std::uint32_t*>(param_1 + 0x54)) * 4);
                 puVar1 != nullptr;
                 puVar1 = reinterpret_cast<std::uint32_t*>(puVar1[2])) {
                if (*puVar1 == local_b4) {
                    if (puVar1 != nullptr) {
                        local_bc = puVar1[1];
                    }
                    break;
                }
            }

            if ((*reinterpret_cast<std::uint8_t*>(local_bc + 0x50) & 0x40) == 0) {
                local_b8 = 0;

                if (((*reinterpret_cast<std::uint8_t*>(reinterpret_cast<int>(param_2) + 10) & 1) +
                     static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(param_2 + 2))) != 0) {
                    do {
                        uVar4 = 0;

                        for (puVar1 = *reinterpret_cast<std::uint32_t**>(
                                 *reinterpret_cast<int*>(param_1 + 0x50) +
                                 (auStack_88[local_b8] % *reinterpret_cast<std::uint32_t*>(param_1 + 0x54)) * 4);
                             puVar1 != nullptr;
                             puVar1 = reinterpret_cast<std::uint32_t*>(puVar1[2])) {
                            if (*puVar1 == auStack_88[local_b8]) {
                                if (puVar1 != nullptr) {
                                    uVar4 = puVar1[1];
                                }
                                break;
                            }
                        }

                        *reinterpret_cast<short*>(uVar4 + 0x54) =
                            *reinterpret_cast<short*>(uVar4 + 0x54) + 1;
                        local_b8 = local_b8 + 1;
                    } while (local_b8 <
                             ((*reinterpret_cast<std::uint8_t*>(reinterpret_cast<int>(param_2) + 10) & 1) +
                              static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(param_2 + 2))));
                }

                *reinterpret_cast<std::uint32_t*>(local_bc + 0x50) =
                    *reinterpret_cast<std::uint32_t*>(local_bc + 0x50) | 0x40;
            }

            bVar3 = *reinterpret_cast<std::uint8_t*>(reinterpret_cast<int>(param_2) + 9);
            local_bc = 0;

            if (bVar3 != 0) {
                do {
                    piVar9 = reinterpret_cast<int*>(
                        FUN_00405fd0(
                            param_2,
                            *reinterpret_cast<undefined4*>(
                                param_2[4] +
                                (static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(param_2 + 2)) +
                                 static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(reinterpret_cast<int>(param_2) + 10) & 1) +
                                 local_bc) * 4)));

                    FUN_00401d30(*reinterpret_cast<undefined4*>(*piVar9 + 4), &DAT_00e2f0a0);

                    puVar11 = local_98;
                    if (local_98 == nullptr) {
                        puVar11 = &DAT_0120546e;
                    }

                    uVar4 = FUN_00404590(
                        param_1,
                        *reinterpret_cast<undefined4*>(*piVar9),
                        puVar11,
                        param_3,
                        param_5 | 0x10);

                    if (uVar4 != 0) {
                        uVar7 = 0;

                        for (puVar1 = *reinterpret_cast<std::uint32_t**>(
                                 *reinterpret_cast<int*>(param_1 + 0x50) +
                                 (uVar4 % *reinterpret_cast<std::uint32_t*>(param_1 + 0x54)) * 4);
                             puVar1 != nullptr;
                             puVar1 = reinterpret_cast<std::uint32_t*>(puVar1[2])) {
                            if (*puVar1 == uVar4) {
                                if (puVar1 != nullptr) {
                                    uVar7 = puVar1[1];
                                }
                                break;
                            }
                        }

                        *reinterpret_cast<short*>(uVar7 + 0x54) =
                            *reinterpret_cast<short*>(uVar7 + 0x54) + 1;
                    }

                    if (local_98 != nullptr) {
                        local_8c(local_98);
                    }

                    local_bc = local_bc + 1;
                } while (local_bc < bVar3);
            }
        }
    } else {
        iVar6 = FUN_004025a0(local_b4);

        if ((((*reinterpret_cast<int*>(iVar6 + 0x24) == 1) || (*reinterpret_cast<int*>(iVar6 + 0x24) == 0)) &&
             (*reinterpret_cast<float*>(iVar6 + 0x48) != param_3)) &&
            (((param_5 & 8) == 0) || (*reinterpret_cast<float*>(iVar6 + 0x48) < param_3))) {
            FUN_004042e0(local_b4, param_3);
        }

        if ((param_5 & 0x10) == 0) {
            *reinterpret_cast<std::uint32_t*>(iVar6 + 0x50) =
                *reinterpret_cast<std::uint32_t*>(iVar6 + 0x50) | 0x20;
        }
    }

LAB_0040404d:
    if (local_a8 != nullptr) {
        local_9c(local_a8);
    }

    return local_b4;
}