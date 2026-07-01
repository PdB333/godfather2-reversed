// FUNC_NAME: PlayerCCTVariables::updateCrouchTimer
void __fastcall PlayerCCTVariables::updateCrouchTimer(int thisPtr)
{
  int globalsPtr;
  float randVal;
  
  globalsPtr = DAT_0112aa1c; // Game global state pointer
  if (*(float *)(thisPtr + 0x24) <= _DAT_00d577a0) { // currentCrouchTimer <= maxCrouchTime
    randVal = (float)FUN_00786660(); // randomFloat() - generates float in [0,1)
    if (randVal <= *(float *)(thisPtr + 0x20)) { // chanceToCrouch
      if ((*(uint *)(globalsPtr + 0x2c6c) >> 6 & 1) == 0) { // check bit 6 of some global flag
        *(undefined4 *)(thisPtr + 0x24) = DAT_01205228; // reset crouch timer to default value
        return;
      }
      *(undefined4 *)(thisPtr + 0x24) = DAT_00d5ccf8; // alternative timer value
    }
  }
  return;
}