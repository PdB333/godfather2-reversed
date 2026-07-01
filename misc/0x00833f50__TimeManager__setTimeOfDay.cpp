// FUNC_NAME: TimeManager::setTimeOfDay
void __thiscall TimeManager::setTimeOfDay(int this, undefined4 *timeData)
{
  int totalSeconds;
  float totalSecondsFloat;
  
  if ((undefined4 *)(this + 0x1c) != timeData) {
    *(undefined4 *)(this + 0x1c) = *timeData;           // +0x1c: hours
    *(undefined4 *)(this + 0x20) = timeData[1];         // +0x20: minutes
    *(undefined4 *)(this + 0x24) = timeData[2];         // +0x24: seconds
    *(undefined4 *)(this + 0x28) = timeData[3];         // +0x28: day
    *(undefined4 *)(this + 0x2c) = timeData[4];         // +0x2c: month
    *(undefined4 *)(this + 0x30) = timeData[5];         // +0x30: year
  }
  // Convert to total seconds for time-of-day tracking
  totalSeconds = timeData[5] + (timeData[4] + timeData[3] * 0x3c) * 0x3c;
  totalSecondsFloat = (float)totalSeconds;
  if (totalSeconds < 0) {
    totalSecondsFloat = totalSecondsFloat + DAT_00e44578; // +0x4.5F3759DF-like constant for negative handling
  }
  *(float *)(this + 0x50) = totalSecondsFloat;          // +0x50: totalTimeInSeconds
  return;
}