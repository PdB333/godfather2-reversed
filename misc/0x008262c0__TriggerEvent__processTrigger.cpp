// FUNC_NAME: TriggerEvent::processTrigger
void __thiscall TriggerEvent::processTrigger(int thisPtr, int *triggerData)
{
  uint currentTime, startTime, endTime;
  int hours, minutes, seconds;
  uint currentTimeComputed;
  int *callbackPtr;

  // Validate the trigger data structure
  validateTriggerData(triggerData);

  // Check if the trigger ID matches the expected ID
  if (*triggerData != *(int *)(thisPtr + 0x1c)) {
    return;
  }

  // If developer mode is active, compute current time in a specific unit (e.g., centiseconds)
  if (DAT_0112a53c != 0) {
    getCurrentTimeComponents(&hours, &minutes, &seconds);
    startTime = *(uint *)(thisPtr + 0x14);
    endTime = *(uint *)(thisPtr + 0x18);
    currentTimeComputed = (hours * 100 + minutes) * 100 + seconds;

    // Check if current time falls within the trigger window
    if (startTime < endTime) {
      if (startTime <= currentTimeComputed && currentTimeComputed <= endTime) {
        // In range, use the in-range callback
        callbackPtr = *(int **)(thisPtr + 0x24);
        if (callbackPtr != nullptr) {
          int extraData = triggerData[1];
          goto executeCallback;
        }
      }
    } else {
      // Wrapping case (e.g., overnight interval)
      if (currentTimeComputed <= endTime || startTime <= currentTimeComputed) {
        callbackPtr = *(int **)(thisPtr + 0x24);
        if (callbackPtr != nullptr) {
          int extraData = triggerData[1];
          goto executeCallback;
        }
      }
    }
  }

  // Default path: use the default callback pointer
  callbackPtr = *(int **)(thisPtr + 0x2c);
  if (callbackPtr == nullptr) {
    return;
  }
  int extraData = triggerData[1];

executeCallback:
  // Clear the low byte of seconds (likely to avoid sub-second precision)
  seconds = seconds & 0xffffff00;
  executeCallback(callbackPtr, 0);
  return;
}