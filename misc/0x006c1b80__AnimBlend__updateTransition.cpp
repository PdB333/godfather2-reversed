// FUNC_NAME: AnimBlend::updateTransition
undefined4 __thiscall AnimBlend::updateTransition(int thisPtr, char param_bIsForward, char param_bForce, float param_unknownFloat)
{
  bool bIsActive;
  bool bForceFlag;
  char cTemp;
  int iTimeSource;
  float10 f10Temp;
  float fBlendTime;
  double dTimeDelta;
  undefined8 localTimeDouble;
  undefined4 timeUpper;
  float localQuat[4]; // m_quaternion at +0x10 (4 floats)
  undefined4 quatCopy[4];
  
  // Check if either forward or force flag is set
  bForceFlag = (param_bIsForward != '\0') || (param_bForce != '\0');
  
  // Get current game time (likely a double from some timer)
  iTimeSource = FUN_00471610(); // e.g., TimeManager::getCurrentTime
  localTimeDouble = *(undefined8 *)(iTimeSource + 0x20);
  timeUpper = *(undefined4 *)(iTimeSource + 0x28);
  dTimeDelta = (double)(DAT_00e44564 - (float)localTimeDouble); // Compute time delta from global?
  FUN_00b9a9fa(); // Possibly a timing sync function
  fBlendTime = (float)dTimeDelta;
  
  // If m_flagAddDelta (0x3a) is set, add a global delta to the blend time
  if (*(char *)(thisPtr + 0x3a) != '\0') {
    f10Temp = (float10)FUN_004a1580(fBlendTime + DAT_00d5eeec);
    fBlendTime = (float)f10Temp;
  }
  
  // Save current quaternion (4 floats at +0x10)
  localQuat[0] = *(float *)(thisPtr + 0x10);
  quatCopy[0] = *(undefined4 *)(thisPtr + 0x14);
  quatCopy[1] = *(undefined4 *)(thisPtr + 0x18);
  quatCopy[2] = *(undefined4 *)(thisPtr + 0x1c);
  
  // Compute difference between saved and new time (localQuat[0] - fBlendTime)
  f10Temp = (float10)FUN_004a1580(localQuat[0] - fBlendTime);
  
  // Check another condition via FUN_00410eb0 (possibly input or state check)
  bIsActive = false;
  cTemp = FUN_00410eb0(); // e.g., GameState::isPaused
  if (cTemp == '\0') {
    if (param_unknownFloat != 0.0) {
      bIsActive = true;
    }
  }
  
  // Branch based on bForceFlag (forward/backward toggle)
  if (bForceFlag) {
    // Transition forward: if flag already set, skip; else set flag and possibly snap to target
    if (*(char *)(thisPtr + 0x3a) != '\0') goto LAB_006c1dc3;
    *(undefined1 *)(thisPtr + 0x3a) = 1;
    
    if (param_bIsForward != '\0') {
      // Check condition: m_prevTime (at +0x64) equals global DAT_00d5eea0 and |f10Temp| < threshold
      if ((*(float *)(thisPtr + 100) == DAT_00d5eea0) &&
          ((float)ABS(f10Temp) < DAT_00e50e5c * DAT_00e445c8)) {
        // Snap to target time
        f10Temp = (float10)FUN_004a1580(fBlendTime + DAT_00d5eeec);
        localQuat[0] = (float)f10Temp;
        // Zero out the rest of the quaternion (or vector)
        quatCopy[0] = 0;
        quatCopy[1] = 0;
        quatCopy[2] = 0;
        FUN_006daa50(); // Possibly apply/update animation
        goto LAB_006c1d87;
      }
    }
  } else {
    // Transition backward: if flag not set, skip; else clear flag and possibly snap
    if (*(char *)(thisPtr + 0x3a) == '\0') goto LAB_006c1dc3;
    *(undefined1 *)(thisPtr + 0x3a) = 0;
    
    if (*(char *)(thisPtr + 0x3b) != '\0') {
      // Similar condition for snapping back
      if (((*(float *)(thisPtr + 100) == DAT_00d5eea0) &&
          ((float)ABS(f10Temp) < DAT_00e50e5c * DAT_00e445c8)) && (!bIsActive)) {
        f10Temp = (float10)FUN_004a1580(fBlendTime + DAT_00d5eeec);
        localQuat[0] = (float)f10Temp;
        quatCopy[0] = 0;
        quatCopy[1] = 0;
        quatCopy[2] = 0;
        FUN_006daa50();
        goto LAB_006c1d87;
      }
    }
  }
  
  // Default: reset m_prevTime to 0
  *(undefined4 *)(thisPtr + 100) = 0;
  
LAB_006c1dc3:
  // Save the forward flag and return 0 (failure to transition)
  *(char *)(thisPtr + 0x3b) = param_bIsForward;
  return 0;
  
LAB_006c1d87:
  // Save new quaternion and update state
  *(float *)(thisPtr + 0x10) = localQuat[0];
  *(undefined4 *)(thisPtr + 0x14) = quatCopy[0];
  *(undefined4 *)(thisPtr + 0x18) = quatCopy[1];
  *(undefined4 *)(thisPtr + 0x1c) = quatCopy[2];
  FUN_006c0810(&localTimeDouble); // Possibly update a reference time
  *(char *)(thisPtr + 0x3b) = param_bIsForward;
  *(undefined1 *)(thisPtr + 0x38) = 1; // m_flagComplete? (0x38)
  *(undefined4 *)(thisPtr + 0x34) = 0; // m_timer? (0x34)
  *(undefined1 *)(thisPtr + 0x30) = 1; // m_flagActive? (0x30)
  return 1; // success
}