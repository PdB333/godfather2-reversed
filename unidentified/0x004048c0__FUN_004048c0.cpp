void __thiscall FUN_004048c0(void* this_, std::uint32_t* param_2, unsigned int param_3)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    if ((param_3 & 1U) == 0) {
        if ((param_2[0x14] & 0x20U) == 0) {
            return;
        }

        param_2[0x14] = param_2[0x14] & 0xFFFFFFDFU;
        FUN_00402f40(8, 1);
    } else {
        auto& refCount = *reinterpret_cast<std::int16_t*>(param_2 + 0x15);
        if (refCount == 0) {
            return;
        }

        refCount = static_cast<std::int16_t>(refCount - 1);
    }

    if (((*reinterpret_cast<std::uint8_t*>(param_2 + 0x14) & 0x20U) == 0) &&
        (*reinterpret_cast<std::int16_t*>(param_2 + 0x15) == 0)) {
        const auto iVar1 = static_cast<int>(param_2[6]);
        int local_20 = 0;

        if (iVar1 != 0) {
            local_20 = FUN_004057f0(iVar1);
            *reinterpret_cast<std::int16_t*>(local_20 + 0x0E) =
                static_cast<std::int16_t>(*reinterpret_cast<std::int16_t*>(local_20 + 0x0E) + 1);

            std::uint32_t uVar8 = static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(iVar1 + 9));
            while (uVar8 = uVar8 - 1, -1 < static_cast<int>(uVar8)) {
                auto* const puVar2 = reinterpret_cast<std::uint32_t*>(
                    FUN_00405fd0(
                        iVar1,
                        *reinterpret_cast<std::uint32_t*>(
                            *reinterpret_cast<int*>(iVar1 + 0x10) +
                            (static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(iVar1 + 8)) +
                             (static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(iVar1 + 10)) & 1U) +
                             uVar8) * 4)));

                const auto uVar3 = FUN_004059b0(*reinterpret_cast<std::uint32_t*>(*puVar2));
                const auto iVar4 = FUN_004025a0(uVar3);
                if (iVar4 != 0) {
                    FUN_004048c0(reinterpret_cast<void*>(static_cast<std::uintptr_t>(iVar4)), 1);
                }
            }
        }

        const auto iVar4 = static_cast<int>(param_2[9]);
        if ((iVar4 == 0) || (iVar4 == 1) || (iVar4 == 5)) {
            FUN_00402f40(4, 1);
        }

        FUN_00402c90(param_2);

        int index = 0;
        for (auto* puVar2 = *reinterpret_cast<std::uint32_t**>(self + 0x70);
             puVar2 != nullptr;
             puVar2 = reinterpret_cast<std::uint32_t*>(*puVar2)) {
            if (puVar2 == param_2) {
                if (-1 < index) {
                    FUN_00404820(this_);
                    goto LAB_00404a17;
                }
                break;
            }
            index = index + 1;
        }

        index = 0;
        for (auto* puVar2 = *reinterpret_cast<std::uint32_t**>(self + 0x68);
             puVar2 != nullptr;
             puVar2 = reinterpret_cast<std::uint32_t*>(*puVar2)) {
            if (puVar2 == param_2) {
                if (-1 < index) {
                    param_2[9] = 2;
                    FUN_00407230();
                    FUN_00404bc0();
                    goto LAB_00404a17;
                }
                break;
            }
            index = index + 1;
        }

        if (FUN_00407280() < 0) {
            FUN_00405570(this_);
        }

LAB_00404a17:
        FUN_004055f0();

        if (iVar1 != 0) {
            int iVar4_2 =
                static_cast<int>((static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(iVar1 + 10)) & 1U) +
                                 static_cast<std::uint32_t>(*reinterpret_cast<std::uint8_t*>(iVar1 + 8)));

            while (iVar4_2 = iVar4_2 + -1, -1 < iVar4_2) {
                auto* const piVar5 = reinterpret_cast<int*>(
                    FUN_00405fd0(
                        iVar1,
                        *reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(iVar1 + 0x10) + iVar4_2 * 4)));

                if (piVar5 != nullptr) {
                    std::uint32_t* local_28;
                    if ((*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(piVar5) + 10) & 0x20U) == 0) {
                        local_28 = nullptr;
                    } else {
                        local_28 = reinterpret_cast<std::uint32_t*>(piVar5[3] * 0x10 + *reinterpret_cast<int*>(self + 0x154));
                    }

                    void* local_18 = nullptr;
                    std::uint32_t local_14 = 0;
                    std::uint32_t local_10 = 0;
                    void (*local_c)(void*) = nullptr;

                    if (local_28 == nullptr) {
                        FUN_004d4ad0(&local_18, &DAT_00e2f0b0, *reinterpret_cast<std::uint32_t*>(*piVar5 + 4), &DAT_00e2f0a0);
                    } else {
                        auto* puVar6 = reinterpret_cast<char*>(*local_28);
                        if (puVar6 == nullptr) {
                            puVar6 = reinterpret_cast<char*>(&DAT_0120546e);
                        }

                        FUN_004d4ad0(&local_18, "%s%s%s", puVar6, *reinterpret_cast<std::uint32_t*>(*piVar5 + 4), &DAT_00e2f0a0);

                        std::uint32_t uVar8 = 0;
                        if (local_14 != 0) {
                            do {
                                if (*reinterpret_cast<char*>(static_cast<std::uint8_t*>(local_18) + uVar8) == '/') {
                                    *reinterpret_cast<char*>(static_cast<std::uint8_t*>(local_18) + uVar8) = '\\';
                                }
                                uVar8 = uVar8 + 1;
                            } while (uVar8 < local_14);
                        }
                    }

                    const auto uVar3 = FUN_00404540(*reinterpret_cast<std::uint32_t*>(*piVar5), local_28 != nullptr);
                    const auto iVar7 = FUN_004025a0(uVar3);
                    if (iVar7 != 0) {
                        FUN_004048c0(reinterpret_cast<void*>(static_cast<std::uintptr_t>(iVar7)), param_3 | 1U);
                    }

                    if (local_18 != nullptr) {
                        local_c(local_18);
                    }
                }
            }

            *reinterpret_cast<std::int16_t*>(local_20 + 0x0E) =
                static_cast<std::int16_t>(*reinterpret_cast<std::int16_t*>(local_20 + 0x0E) - 1);

            if ((*reinterpret_cast<std::uint16_t*>(local_20 + 0x0E) & 0x7FFFU) == 0) {
                FUN_00404070();
            }
        }
    }
}