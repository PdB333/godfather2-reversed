extern "C" std::uint32_t* FUN_0065ceb0(std::uint32_t* param_1, std::uint32_t param_2)
{
    const std::uint32_t uVar1 = DAT_01205a64;

    param_1[1] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e434c0);
    DAT_0122355c = param_1;
    param_1[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e43440);
    param_1[1] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e434bc);
    param_1[2] = uVar1;

    InitializeCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(param_1 + 3));
    InitializeCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(param_1 + 9));

    std::uint32_t uVar2 = 4;
    do {
        uVar2 = uVar2 >> 2;
    } while (uVar2 != 0);

    FUN_0065df10();
    FUN_0065df10();

    param_1[0x1b] = param_2;

    {
        using Fn = void (*)();
        auto** vtable = *reinterpret_cast<void***>(param_1[2]);
        Fn fn = reinterpret_cast<Fn>(vtable[2]); // 0x8 / 4
        fn();
    }

    *reinterpret_cast<std::uint16_t*>(
        reinterpret_cast<std::uint8_t*>(param_1) + 0x76) = 0;
    *reinterpret_cast<std::uint16_t*>(param_1 + 0x1d) = 0;
    param_1[0x1c] = 0;

    FUN_0065d080(param_1);

    auto* piVar3 = reinterpret_cast<std::int32_t*>(FUN_00ad8d40());
    if (piVar3 != nullptr) {
        using AcquireFn = std::int32_t* (*)();
        using AttachFn = void (*)(std::uint32_t*);

        auto** vtable_mgr = *reinterpret_cast<void***>(piVar3);
        auto* acquired = reinterpret_cast<AcquireFn>(vtable_mgr[0x34 / 4])();

        auto** vtable_acq = *reinterpret_cast<void***>(acquired);
        reinterpret_cast<AttachFn>(vtable_acq[1])(param_1);

        return param_1;
    }

    reinterpret_cast<void (*)(std::uint32_t*)>(iRam00000000 + 4)(param_1);
    return param_1;
}