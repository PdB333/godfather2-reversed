extern "C" void FUN_0040a600()
{
    DAT_012067e8 = DAT_01206a30 * DAT_00e2e210;

    TIMECAPS timeCaps{};
    timeCaps.wPeriodMin = static_cast<UINT>(std::llround(DAT_01206a30));

    DAT_0110ae80 = DAT_00e2b1a4;
    DAT_012067f8 = DAT_01206a30 * DAT_00e3ac54;

    DAT_01205208 = 0;
    DAT_01205210 = 0;
    DAT_01205214 = 0;
    DAT_01205220 = 0;
    DAT_01206804 = timeCaps.wPeriodMin;
    DAT_01205224 = 0;
    DAT_01205230 = 0;
    DAT_01205234 = 0;
    DAT_01205228 = 0;

    if (DAT_0110ae75 == '\0') {
        timeCaps.wPeriodMin =
            static_cast<UINT>(std::llround(DAT_00e2dd14 * DAT_01206a30 + DAT_00e2cd54));
        DAT_012067ec = timeCaps.wPeriodMin;
    } else {
        DAT_0110ae7c = 5;
    }

    DAT_012067fc = DAT_01206a30;

    timeCaps.wPeriodMin =
        static_cast<UINT>(std::llround(DAT_00e445ac * DAT_01206a30 + 1.0));
    DAT_012067f0 = timeCaps.wPeriodMin;

    timeCaps.wPeriodMin =
        static_cast<UINT>(std::llround(DAT_01206a30 + DAT_01206a30 + 1.0));
    DAT_012067f4 = timeCaps.wPeriodMin;

    DAT_01206800 = DAT_012067e8;

    if (DAT_01223390 == 0) {
        if (FUN_009c8e50(0x1c) != 0) {
            FUN_00409e30();
        }
    }

    const auto timerState = reinterpret_cast<std::uint8_t*>(DAT_01223390);

    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);

    const DWORD currentTime = timeGetTime();

    timeEndPeriod(timeCaps.wPeriodMin);

    *reinterpret_cast<DWORD*>(timerState + 0x10) = currentTime;
    *reinterpret_cast<DWORD*>(timerState + 0x14) = currentTime;
    *reinterpret_cast<std::uint32_t*>(timerState + 0x18) = 0;
}