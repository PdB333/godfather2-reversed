extern "C" void __cdecl FUN_0040d450(std::uint32_t param_1, std::uint32_t param_2)
{
    if (DAT_0110accb != '\0') {
        float fVar1 = static_cast<float>(static_cast<std::int32_t>(in_EAX));
        if (static_cast<std::int32_t>(in_EAX) < 0) {
            fVar1 = fVar1 + DAT_00e44578;
        }
        fVar1 = (fVar1 / DAT_0110ae4c) * DAT_00e2e230;

        LARGE_INTEGER local_28{};
        local_28.LowPart = in_EAX;
        QueryPerformanceCounter(&local_28);

        std::int32_t iVar2;
        std::uint32_t uVar3;
        if ((static_cast<std::uint32_t>(local_28.HighPart) < param_2) ||
            ((static_cast<std::uint32_t>(local_28.HighPart) <= param_2) &&
             (static_cast<std::uint32_t>(local_28.LowPart) <= param_1))) {
            iVar2 = static_cast<std::int32_t>(~(param_1 - static_cast<std::uint32_t>(local_28.LowPart)) + 1);
            uVar3 = ~((param_2 - static_cast<std::uint32_t>(local_28.HighPart)) -
                      static_cast<std::uint32_t>(param_1 < static_cast<std::uint32_t>(local_28.LowPart))) +
                    static_cast<std::uint32_t>(0xfffffffeu <
                                               ~(param_1 - static_cast<std::uint32_t>(local_28.LowPart)));
        } else {
            iVar2 = local_28.LowPart - static_cast<std::int32_t>(param_1);
            uVar3 = (static_cast<std::uint32_t>(local_28.HighPart) - param_2) -
                    static_cast<std::uint32_t>(static_cast<std::uint32_t>(local_28.LowPart) < param_1);
        }

        local_28.LowPart = static_cast<LONG>(fVar1 - DAT_00e2b1a4);
        local_28.HighPart = static_cast<LONG>(uVar3 & 0x80000000u);

        const float fStack_30_initial = static_cast<float>(
            ((-static_cast<long double>(static_cast<long long>(
                   (static_cast<unsigned long long>(uVar3 & 0x80000000u)) << 32))) +
             static_cast<long double>(
                 ((static_cast<unsigned long long>(uVar3) << 32) |
                  static_cast<std::uint32_t>(iVar2)) &
                 0x7fffffffffffffffULL)) *
            static_cast<long double>(_DAT_01163ecc));

        float fStack_30 = fStack_30_initial;

        if (fStack_30 < static_cast<float>(local_28.LowPart)) {
            LARGE_INTEGER LStack_20{};
            std::int32_t iStack_18;
            std::uint32_t uStack_14;
            LARGE_INTEGER LStack_10{};

            do {
                Sleep(0);
                QueryPerformanceCounter(&LStack_20);

                if ((static_cast<std::uint32_t>(LStack_20.HighPart) < param_2) ||
                    ((static_cast<std::uint32_t>(LStack_20.HighPart) <= param_2) &&
                     (static_cast<std::uint32_t>(LStack_20.LowPart) <= param_1))) {
                    iStack_18 =
                        static_cast<std::int32_t>(~(param_1 - static_cast<std::uint32_t>(LStack_20.LowPart)) + 1);
                    uVar3 = ~((param_2 - static_cast<std::uint32_t>(LStack_20.HighPart)) -
                              static_cast<std::uint32_t>(param_1 < static_cast<std::uint32_t>(LStack_20.LowPart))) +
                            static_cast<std::uint32_t>(0xfffffffeu <
                                                       ~(param_1 - static_cast<std::uint32_t>(LStack_20.LowPart)));
                } else {
                    iStack_18 = LStack_20.LowPart - static_cast<std::int32_t>(param_1);
                    uVar3 = (static_cast<std::uint32_t>(LStack_20.HighPart) - param_2) -
                            static_cast<std::uint32_t>(static_cast<std::uint32_t>(LStack_20.LowPart) < param_1);
                }

                uStack_14 = uVar3 & 0x7fffffffu;
                LStack_10.HighPart = static_cast<LONG>(uVar3 & 0x80000000u);
                LStack_10.LowPart = 0;

                const long double fVar4 =
                    ((-static_cast<long double>(static_cast<long long>(
                           (static_cast<unsigned long long>(uVar3 & 0x80000000u)) << 32))) +
                     static_cast<long double>(
                         ((static_cast<unsigned long long>(uVar3) << 32) |
                          static_cast<std::uint32_t>(iStack_18)) &
                         0x7fffffffffffffffULL)) *
                    static_cast<long double>(_DAT_01163ecc);

                fStack_30 = static_cast<float>(fVar4);
                if (!(fVar4 < static_cast<long double>(static_cast<float>(local_28.LowPart)))) {
                    break;
                }
            } while (true);
        }

        if (fStack_30 < fVar1) {
            LARGE_INTEGER LStack_10{};
            LARGE_INTEGER LStack_20{};
            std::int32_t iStack_18;
            std::uint32_t uStack_14;

            do {
                QueryPerformanceCounter(&LStack_10);

                if ((static_cast<std::uint32_t>(LStack_10.HighPart) < param_2) ||
                    ((static_cast<std::uint32_t>(LStack_10.HighPart) <= param_2) &&
                     (static_cast<std::uint32_t>(LStack_10.LowPart) <= param_1))) {
                    iStack_18 =
                        static_cast<std::int32_t>(~(param_1 - static_cast<std::uint32_t>(LStack_10.LowPart)) + 1);
                    uVar3 = ~((param_2 - static_cast<std::uint32_t>(LStack_10.HighPart)) -
                              static_cast<std::uint32_t>(param_1 < static_cast<std::uint32_t>(LStack_10.LowPart))) +
                            static_cast<std::uint32_t>(0xfffffffeu <
                                                       ~(param_1 - static_cast<std::uint32_t>(LStack_10.LowPart)));
                } else {
                    iStack_18 = LStack_10.LowPart - static_cast<std::int32_t>(param_1);
                    uVar3 = (static_cast<std::uint32_t>(LStack_10.HighPart) - param_2) -
                            static_cast<std::uint32_t>(static_cast<std::uint32_t>(LStack_10.LowPart) < param_1);
                }

                uStack_14 = uVar3 & 0x7fffffffu;
                LStack_20.HighPart = static_cast<LONG>(uVar3 & 0x80000000u);
                LStack_20.LowPart = 0;
            } while (((-static_cast<long double>(static_cast<long long>(
                            (static_cast<unsigned long long>(uVar3 & 0x80000000u)) << 32))) +
                      static_cast<long double>(
                          ((static_cast<unsigned long long>(uVar3) << 32) |
                           static_cast<std::uint32_t>(iStack_18)) &
                          0x7fffffffffffffffULL)) *
                         static_cast<long double>(_DAT_01163ecc) <
                     static_cast<long double>(fVar1));
        }
    }
}