// FUNC_NAME: Performance::initPerformanceCounter
undefined * Performance::initPerformanceCounter(void)

{
  BOOL BVar1;
  LARGE_INTEGER local_8;

  BVar1 = QueryPerformanceFrequency(&local_8);
  _DAT_01223370 = BVar1 != 0;
  _DAT_01223368 = _DAT_00e44570 / (double)(longlong)local_8;
  // _DAT_00e44570 likely a constant time divisor (e.g., 1000.0 for ms, or 1000000.0 for us)
  // _DAT_01223368 is the initial counter value (tick frequency divisor)
  // _DAT_01223370 indicates whether QueryPerformanceFrequency succeeded
  return &_DAT_01223368;
}