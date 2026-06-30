// FUNC_NAME: Timer::advance
void Timer::advance(int deltaMs)
{
  if (deltaMs > 0) {
    do {
      // Accumulate elapsed time from a source timer (likely a high-precision clock)
      elapsedMs += sourceIntervalMs;
      // Call a function to get the next timer tick interval (likely returns ms to next tick)
      nextTickIntervalMs = FUN_004dd960(); // Probably Timer::getNextTickInterval or similar
      tickCount++;
      deltaMs--;
    } while (deltaMs != 0);
  }
}