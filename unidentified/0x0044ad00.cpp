// FUN_0044ad00: GameTimer::GameTimer(bool useQPC, TimerCallback callback1, TimerCallback callback2, int initialMicroseconds)
GameTimer * __thiscall GameTimer::GameTimer(GameTimer *this, uint param2, uint param3, uint param4, uint param5)
{
  LARGE_INTEGER counter;
  bool useQPC;

  DAT_01223444 = (GameTimer *)this;
  this->vtable = (GameTimerVTable *)&PTR_FUN_00e312cc;  // set vtable
  QueryPerformanceCounter(&counter);
  this->initialQpcValueLow = counter.LowPart;   // +0x08
  this->initialQpcValueHigh = counter.HighPart;  // +0x0C
  this->param5 = param5;                         // +0x10
  useQPC = DAT_01223380 != 0;                    // global flag whether to use QPC
  this->usePerformanceCounter = useQPC;          // +0x14 (bool)
  if (!useQPC) {
    param2 = 1;                                  // force start flag if no QPC
  }
  FUN_0044b2c0(param2);                          // start timer with given flag
  this->callback1 = param3;                      // +0x28 (function pointer)
  this->callback2 = param4;                      // +0x2C (function pointer)
  // SEH setup block (visual C++ exception handling)
  // local variables for try/except handler
  // ...
  FUN_00486b90(param3, param4);                  // register or bind callbacks
  // if stack cookie mismatched, call FUN_00407640 (SEH unwinder)
  if ((handlerLabel != (undefined1 *)0x0) && (stackCookie != 0x2a7ed975)) {
    FUN_00407640();
  }
  return this;
}