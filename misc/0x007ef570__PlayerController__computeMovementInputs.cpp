// FUNC_NAME: PlayerController::computeMovementInputs
void __thiscall PlayerController::computeMovementInputs(int thisPtr, undefined4 *outFlags, float *outX, float *outY, float deltaTime, int playerData)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  
  fVar1 = *(float *)(playerData + 0x124); // +0x124: some input axis value
  fVar2 = *(float *)(playerData + 0x30);  // +0x30: sensitivity multiplier
  fVar7 = (float10)FUN_007f3200(DAT_01205228); // get random or time-based value
  fVar6 = DAT_00e445c8; // global frame delta or smoothing factor
  fVar8 = *(float *)(playerData + 300) - // +0x12C: some target value
          (*(float *)(playerData + 300) - *(float *)(playerData + 0x130)) * DAT_00d7007c * (float)fVar7; // +0x130: current value, interpolate with random factor
  if ((*(char *)(thisPtr + 0x5e2) == '\0') && (*(char *)(thisPtr + 0x5e0) == '\0')) {
    fVar8 = 0.0; // if certain flags are clear, zero out the interpolated value
  }
  fVar3 = *(float *)(playerData + 0x2c); // +0x2C: another input axis
  fVar4 = *(float *)(playerData + 0x34); // +0x34: vertical axis or acceleration
  *outFlags = 0;
  *outX = 0.0;
  *outY = 0.0;
  fVar9 = _DAT_00d5780c; // global gravity or movement modifier
  fVar5 = DAT_00d5779c; // threshold value
  *outX = (float)((uint)(fVar1 * deltaTime) & DAT_00e44680) * fVar2 * fVar6 + *outX +
             fVar3 * fVar6; // compute horizontal movement with bitwise mask trick
  if (*(float *)(thisPtr + 0xf8) < fVar5) { // +0xF8: some player state value
    fVar9 = *(float *)(thisPtr + 0xf8) * _DAT_00d5cf70 * DAT_00d5842c + DAT_00d5c454; // compute modified gravity
  }
  *outY = (fVar4 * deltaTime + fVar8) * fVar9; // compute vertical movement with gravity
  return;
}