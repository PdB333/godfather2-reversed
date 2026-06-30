// FUNC_NAME: SystemClock::initialize
void __thiscall SystemClock::initialize(DWORD arg1, DWORD arg2)
{
    TIMECAPS timeCaps;
    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);
    DWORD currentTime = timeGetTime();
    timeEndPeriod(timeCaps.wPeriodMin);
    this->startTime = currentTime; // +0x22c
    FUN_0064f9b0(arg1, arg2);
}