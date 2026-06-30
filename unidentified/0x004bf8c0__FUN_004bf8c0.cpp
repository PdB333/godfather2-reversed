extern "C" bool __fastcall FUN_004bf8c0(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    if (DAT_0110ae74 != 0) {
        return true;
    }

    TIMECAPS timeCaps{};
    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);

    const DWORD currentTime = timeGetTime();

    timeEndPeriod(timeCaps.wPeriodMin);

    auto& lastTime = *reinterpret_cast<std::uint32_t*>(self + 0x22c);

    if (currentTime < lastTime) {
        lastTime = 0;
    }

    return lastTime + 1000U < currentTime;
}