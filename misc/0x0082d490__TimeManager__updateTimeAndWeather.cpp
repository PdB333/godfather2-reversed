// FUNC_NAME: TimeManager::updateTimeAndWeather
void __thiscall TimeManager::updateTimeAndWeather(int this, int *timeModifiers)
{
  int globalTimeData;
  uint i;
  float timeDelta;
  undefined4 weatherData1;
  undefined4 weatherData2;
  undefined4 weatherData3;
  int hours;
  int minutes;
  int seconds;
  float currentTime;
  float targetTime;
  undefined4 weatherInterp1;
  undefined4 weatherInterp2;
  undefined4 weatherInterp3;
  undefined1 currentWeather[16];
  undefined1 targetWeather[16];
  
  globalTimeData = DAT_0112db9c; // Global time/weather state pointer
  FUN_008334a0(); // Likely getCurrentTimeOfDay
  currentWeather = (undefined1 [16])0x0;
  targetWeather = (undefined1 [16])0x0;
  FUN_009cbee0(); // getCurrentWeather
  FUN_009cc120(); // getTargetWeather
  timeDelta = _DAT_00d5780c; // Base time step (e.g., 0.016f for 60fps)
  
  // Apply time modifiers from param_2 (array of {entity, timeScale} pairs)
  for (i = (uint)(timeModifiers != (int *)0x0); i != 0; i = i - 1) {
    if (*(int *)(*timeModifiers + 0xc) == *(int *)(this + 0xc)) {
      timeDelta = timeDelta - (float)timeModifiers[1];
      FUN_009cc170(*timeModifiers + 0x30, timeModifiers[1]); // applyTimeScaleModifier
    }
  }
  FUN_009cc170(this + 0x30, timeDelta); // setTimeScale
  
  // Interpolate weather based on time progression
  if (targetTime == currentTime) {
    *(float *)(globalTimeData + 0x20) = currentTime;
    *(undefined4 *)(globalTimeData + 0x24) = 0;
  }
  else if (currentTime <= targetTime) {
    *(float *)(globalTimeData + 0x20) = currentTime;
    *(float *)(globalTimeData + 0x24) = _DAT_00d5780c / (targetTime - currentTime);
  }
  else {
    *(float *)(globalTimeData + 0x20) = targetTime;
    *(float *)(globalTimeData + 0x24) = _DAT_00d5780c / (currentTime - targetTime);
  }
  
  // Store weather interpolation data
  *(undefined4 *)(globalTimeData + 0x28) = weatherInterp1;
  *(undefined4 *)(globalTimeData + 0x2c) = weatherInterp2;
  *(undefined4 *)(globalTimeData + 0x30) = weatherInterp3;
  
  // Store current weather (4 floats)
  *(undefined4 *)(globalTimeData + 0x40) = currentWeather._0_4_;
  *(undefined4 *)(globalTimeData + 0x44) = currentWeather._4_4_;
  *(undefined4 *)(globalTimeData + 0x48) = currentWeather._8_4_;
  *(undefined4 *)(globalTimeData + 0x4c) = currentWeather._12_4_;
  
  // Store target weather (4 floats)
  *(undefined4 *)(globalTimeData + 0x50) = targetWeather._0_4_;
  *(undefined4 *)(globalTimeData + 0x54) = targetWeather._4_4_;
  *(undefined4 *)(globalTimeData + 0x58) = targetWeather._8_4_;
  *(undefined4 *)(globalTimeData + 0x5c) = targetWeather._12_4_;
  
  // Store total elapsed time in seconds
  *(int *)(globalTimeData + 0x1c) = seconds + (minutes + hours * 0x3c) * 0x3c;
  
  // Store time components if they changed
  if ((undefined4 *)(globalTimeData + 4) != &weatherData1) {
    *(undefined4 *)(globalTimeData + 4) = weatherData1;
    *(undefined4 *)(globalTimeData + 8) = weatherData2;
    *(undefined4 *)(globalTimeData + 0xc) = weatherData3;
    *(int *)(globalTimeData + 0x10) = hours;
    *(int *)(globalTimeData + 0x14) = minutes;
    *(int *)(globalTimeData + 0x18) = seconds;
  }
  return;
}