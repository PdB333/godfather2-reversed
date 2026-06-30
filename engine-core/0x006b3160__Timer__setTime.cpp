// FUNC_NAME: Timer::setTime
void __thiscall Timer::setTime(int this, int newTime)
{
  int timeDelta = newTime - *(int *)(this + 0xC8); // offset 0xC8: current time storage
  if (timeDelta != 0) {
    *(int *)(this + 0xC8) = newTime;
    // Callback with pointer from offset 0x40 (some manager), this object, and time difference
    FUN_008c7800(*(int *)(this + 0x40), this, timeDelta);
  }
}