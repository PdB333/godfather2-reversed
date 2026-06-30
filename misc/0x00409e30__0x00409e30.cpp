extern "C" void FUN_00409e30()
{
    auto* self = reinterpret_cast<std::uint32_t*>(in_EAX);

    self[1] = 1;
    self[2] = 0;
    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f1d0);
    self[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f1bc);
    self[3] = reinterpret_cast<std::uint32_t>(&PTR_LAB_00e2f1cc);
    self[4] = 0;

    DAT_01223390 = self;

    if (DAT_01206940 != 0)
    {
        _DAT_01206944 = _DAT_01206944 + 1;

        const int result = FUN_00407da0();
        if (result == 0)
        {
            FUN_004084d0(&DAT_01206940, 0xffff);
        }
        else
        {
            const std::uint16_t uVar1 = *reinterpret_cast<std::uint16_t*>(result + 0x14);

            *reinterpret_cast<std::uint16_t*>(result + 0x14) =
                static_cast<std::uint16_t>(
                    (
                        (
                            static_cast<std::uint32_t>(
                                static_cast<int16_t>(
                                    static_cast<std::int32_t>(
                                        static_cast<std::uint32_t>(uVar1) * 2
                                    ) >> 1
                                )
                            ) + 1U
                        ) ^ uVar1
                    ) & 0x7fff
                ) ^ uVar1;
        }
    }

    TIMECAPS caps{};
    timeGetDevCaps(&caps, 8);
    timeBeginPeriod(caps.wPeriodMin);

    const DWORD tick = timeGetTime();

    timeEndPeriod(caps.wPeriodMin);

    self[4] = tick;
    self[5] = tick;
    self[6] = 0;
}