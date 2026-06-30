// FUNC_NAME: getHighResTimeMs
DWORD getHighResTimeMs(void)
{
    TIMECAPS timeCaps;
    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);
    DWORD currentTime = timeGetTime();
    timeEndPeriod(timeCaps.wPeriodMin);
    return currentTime;
}