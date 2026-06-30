extern "C" void __fastcall FUN_00409f30(std::uint32_t* self)
{
    TIMECAPS timeCaps{};
    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);

    const DWORD currentTime = timeGetTime();

    timeEndPeriod(timeCaps.wPeriodMin);

    self[4] = currentTime;
    self[5] = currentTime;
    self[6] = 0;
}