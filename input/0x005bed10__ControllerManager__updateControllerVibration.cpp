// FUNC_NAME: ControllerManager::updateControllerVibration
undefined4 __thiscall ControllerManager::updateControllerVibration(float dt)
{
  undefined4 result;
  float vd;
  char enabled;
  undefined4 in_EAX;
  int *controllerData;
  int index;
  int *pNextController;
  int i;
  int *pThis;
  float vibrationSpeed;
  float vibrationTimer;
  float threshold;
  float temp;

  controllerData = &controllerDataArray; // DAT_00f17918
  i = 0;
  vd = dt;
  do {
    index = *controllerData;
    vibrationTimer = 0.0;
    enabled = FUN_004660f0(in_EAX, 2); // CheckControllerEnabled? (param 2 = maybe player index)
    if (enabled == '\0') { // if controller is enabled
      if (((1 << ((byte)index & 0x1f) & 0x3c0U) != 0) && // Check if controller index is valid (bitmask 0x3c0)
         (((globalVibrationActiveFlag == '\0' || (currentVibrationIndex == index)) && // Only process if vibration is active or this is the active index
          (enabled = FUN_004660f0(in_EAX, 1), threshold = vibrationDecayRate, enabled != '\0')))) {
        // Update vibration timer
        vibrationSpeed = vd + (float)vibrationTimers[i];
        vibrationTimers[i] = vibrationSpeed;
        if (threshold <= vibrationSpeed) { // If timer exceeds decay threshold
          temp = vibrationSpeedLowerThreshold;
          if (vibrationSpeed < vibrationDurationThreshold) {
            temp = vibrationSpeedUpperThreshold;
          }
          vibrationIntensities[i] = vibrationIntensities[i] - vd * temp; // Apply decay
        }
        else {
          vibrationIntensities[i] = vibrationIntensities[i] - vd; // Full decay
        }
        if ((float)vibrationIntensities[i] <= vibrationTimer) { // If intensity reaches zero
          vibrationIntensities[i] = vibrationIntensities[i] + vibrationResetValue; // Reset vibration
          goto LAB_005bee4d;
        }
      }
    }
    else { // controller not enabled
      enabled = FUN_005bec90(); // CheckVibrationSystemActive?
      if (enabled == '\0') { // If vibration system is not active
        vibrationIntensities[i] = defaultIntensity; // Reset intensity
        vibrationTimers[i] = vibrationTimer; // Reset timer
        if ((1 << ((byte)index & 0x1f) & 0x3c0U) != 0) {
          currentVibrationIndex = index; // Store as active index
        }
LAB_005bee4d:
        vibrationPendingFlag = 1; // Mark vibration as pending
        pThis = (int *)FUN_005bec00(); // GetControllerManager?
        do {
          if ((maxControllerIndex < 0) || (index = maxControllerIndex, pThis == (int *)0x0)) {
LAB_005beeb3:
            pNextController = (int *)0x0;
          }
          else {
            for (; (-1 < index && ((int *)controllerIndexArray[index] != pThis)); index = index + -1) {
            }
            do {
              index = index + -1;
              if (index < 0) goto LAB_005beeb3;
            } while (controllerIndexArray[index] == 0);
            pNextController = (int *)controllerIndexArray[index];
          }
          index = (**(code **)(*pThis + 0x20))(*controllerData); // Call vtable method at +0x20
          vibrationState = 0x12; // VIBRATION_STATE_PENDING
          if (index != 1) {
            vibrationActiveIndex = 0;
          }
          if (index == 0) { // Error or success?
            vibrationState = 0x12;
            return 1;
          }
          if (index == 2) { // Already vibrating?
            if ((1 << ((byte)*controllerData & 0x1f) & 0x3c0U) == 0) {
              vibrationState = 0x12;
              return 1;
            }
            vibrationIntensities[i] = vibrationResetValue;
            return 1;
          }
          if (index == 3) { // Vibration complete?
            vibrationTimers[i] = 0;
            return 1;
          }
          vd = dt;
        } while ((pNextController != (int *)0x0) && // Iterate through controllers
                (enabled = (**(code **)(*pNextController + 0x10))(), pThis = pNextController, enabled == '\0'));
      }
    }
    i = i + 1;
    controllerData = controllerData + 1;
    index = vibrationActiveIndex;
    if (0xf < i) { // Process up to 16 controllers
joined_r0x005bef24:
      do {
        if (index == 0) {
          return 0; // No pending vibration
        }
        result = vibrationQueue[index]; // Get next in queue
        vibrationActiveIndex = index + -1;
        pThis = (int *)FUN_005bec00();
        index = extraout_ECX;
        while ((pThis != (int *)0x0 && // Process pending vibration
               (enabled = (**(code **)(*pThis + 0x10))(), index = vibrationActiveIndex, enabled == '\0'))) {
          i = (**(code **)(*pThis + 0x20))(result);
          if ((i == 0) || ((i == 2 || (i == 3)))) {
            return 1; // Vibration successfully handled
          }
          i = maxControllerIndex;
          index = vibrationActiveIndex;
          if (maxControllerIndex < 0) break;
          do {
            if ((int *)controllerIndexArray[i] == pThis) break;
            i = i + -1;
          } while (-1 < i);
          do {
            i = i + -1;
            if (i < 0) goto joined_r0x005bef24;
          } while (controllerIndexArray[i] == 0);
          pThis = (int *)controllerIndexArray[i];
        }
      } while( true );
    }
  } while( true );
}