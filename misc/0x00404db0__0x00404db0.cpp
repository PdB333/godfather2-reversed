extern "C" std::uint32_t FUN_00404db0(
    int param_1,
    int param_2,
    std::uint32_t param_3,
    unsigned long long param_4)
{
    int* piVar1;
    int iVar2;
    std::uint32_t uVar3;
    std::uint32_t uVar4;
    code* pcVar5;
    std::uint32_t uVar6;
    unsigned long long uVar7;
    LARGE_INTEGER local_30;
    LARGE_INTEGER local_28;
    std::uint32_t local_20;
    int local_1c;
    int local_18;
    std::uint32_t uStack_14;
    std::uint32_t local_10;
    std::uint32_t uStack_c;
    LARGE_INTEGER local_8;

    pcVar5 = QueryPerformanceCounter_exref;
    QueryPerformanceCounter(&local_30);

    piVar1 = *reinterpret_cast<int**>(DAT_012234a8 + 0x4c);
    if (piVar1 != nullptr)
    {
        do
        {
            if (piVar1[0x2b] == *reinterpret_cast<int*>(param_2 + 0x28))
            {
                if (piVar1[0x2c] < 1)
                {
                    return 0;
                }

                if ((3 < piVar1[0x2c]) && (*reinterpret_cast<int*>(param_2 + 0x30) == 0))
                {
                    QueryPerformanceCounter(&local_28);

                    uVar7 = __allmul(
                        local_28.u.LowPart - *reinterpret_cast<std::uint32_t*>(param_1 + 0x90),
                        (local_28.u.HighPart - *reinterpret_cast<int*>(param_1 + 0x94)) -
                            static_cast<std::uint32_t>(
                                local_28.u.LowPart <
                                *reinterpret_cast<std::uint32_t*>(param_1 + 0x90)),
                        1000,
                        0);

                    iVar2 = __aulldiv(uVar7, DAT_01163ec0, DAT_01163ec4);
                    *reinterpret_cast<int*>(param_2 + 0x30) =
                        iVar2 + *reinterpret_cast<int*>(param_1 + 0x98);
                }

                *reinterpret_cast<int*>(param_1 + 0x84) = param_2;

                if (*reinterpret_cast<int*>(param_2 + 0x20) == 0)
                {
                    *reinterpret_cast<int*>(param_1 + 0x40) =
                        *reinterpret_cast<int*>(param_1 + 0x40) + 1;
                    *reinterpret_cast<std::uint32_t*>(param_2 + 0x20) =
                        *reinterpret_cast<std::uint32_t*>(param_1 + 0x40);
                }

                uVar6 = static_cast<std::uint32_t>(param_4);
                goto LAB_00404e90;
            }

            piVar1 = reinterpret_cast<int*>(*piVar1);
        } while (piVar1 != nullptr);
    }

    return 0;

LAB_00404e90:
    param_4 = (param_4 & 0xffffffff00000000ULL) | 0xffffffffULL;
    if ((uVar6 != 0) || (static_cast<std::uint32_t>(param_4 >> 32) != 0))
    {
        pcVar5(&local_20);

        uVar4 = local_20 - local_30.u.LowPart;
        uVar3 =
            (local_1c - local_30.u.HighPart) - static_cast<std::uint32_t>(local_20 < local_30.u.LowPart);

        if ((static_cast<std::uint32_t>(param_4 >> 32) < uVar3) ||
            ((static_cast<std::uint32_t>(param_4 >> 32) <= uVar3) && (uVar6 <= uVar4)))
        {
            local_18 = 1;
            uVar6 = 0;
        }
        else
        {
            local_18 = static_cast<int>(uVar6 - uVar4);
            uVar6 =
                (static_cast<std::uint32_t>(param_4 >> 32) - uVar3) -
                static_cast<std::uint32_t>(uVar6 < uVar4);
        }

        uStack_14 = uVar6 & 0x7fffffff;
        uStack_c = uVar6 & 0x80000000;
        local_10 = 0;

        param_4 =
            (param_4 & 0xffffffff00000000ULL) |
            static_cast<std::uint32_t>(
                static_cast<long long>(
                    ROUND(
                        (-(long double)(
                              static_cast<long long>(
                                  (static_cast<unsigned long long>(uVar6 & 0x80000000) << 0x20))) +
                         static_cast<long double>(
                             (static_cast<unsigned long long>(uVar6) << 32 |
                              static_cast<std::uint32_t>(local_18)) &
                             0x7fffffffffffffffULL)) *
                        static_cast<long double>(_DAT_01163ed0))));
    }

    uVar6 = FUN_004d1010(DAT_012234a8, param_3, static_cast<std::uint32_t>(param_4));
    if ((((uVar6 & 9) != 0) || (*reinterpret_cast<int*>(param_2 + 0x30) == 0)) ||
        (((uVar6 & 2) == 0) &&
         (((uVar6 & 4) == 0) || (static_cast<char>(param_3) != '\0'))))
    {
        goto LAB_00404fb3;
    }

    QueryPerformanceCounter(&local_8);

    uVar7 = __allmul(
        local_8.u.LowPart - *reinterpret_cast<std::uint32_t*>(param_1 + 0x90),
        (local_8.u.HighPart - *reinterpret_cast<int*>(param_1 + 0x94)) -
            static_cast<std::uint32_t>(
                local_8.u.LowPart < *reinterpret_cast<std::uint32_t*>(param_1 + 0x90)),
        1000,
        0);

    uVar3 = __aulldiv(uVar7, DAT_01163ec0, DAT_01163ec4);
    if (uVar3 < *reinterpret_cast<std::uint32_t*>(param_2 + 0x30))
    {
        goto LAB_00404fb3;
    }

    uVar6 = 0;
    param_4 = 0;
    pcVar5 = QueryPerformanceCounter_exref;
    goto LAB_00404e90;

LAB_00404fb3:
    if (*reinterpret_cast<char*>(param_1 + 0x8a) != '\0')
    {
        *reinterpret_cast<std::uint32_t*>(param_2 + 0x50) =
            *reinterpret_cast<std::uint32_t*>(param_2 + 0x50) | 0x200;
        *reinterpret_cast<std::uint8_t*>(param_1 + 0x8a) = 0;
    }

    *reinterpret_cast<int*>(param_1 + 0x84) = 0;
    return uVar6;
}