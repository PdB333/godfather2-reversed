// FUNC_NAME: PlayerCCTVariables::updateCrouchTimer
void __fastcall PlayerCCTVariables::updateCrouchTimer(int this)
{
  float fVar1;
  int local_8;
  
  fVar1 = _DAT_00d5780c; // global delta time (frame time)
  *(int *)(this + 0x23c) = DAT_01205224; // +0x23c: maxCrouchTime (initialized from data)
  if (*(float *)(this + 0x240) < fVar1) { // +0x240: remainingCrouchTime
    fVar1 = fVar1 - *(float *)(this + 0x240);
    *(float *)(this + 0x240) = fVar1;
    local_8 = (int)(longlong)ROUND(fVar1 * _DAT_00d5f51c); // convert to some unit (ticks?)
    *(int *)(this + 0x23c) = DAT_01205224 - local_8; // adjust maxCrouchTime
  }
  *(undefined1 *)(this + 0x248) = 0; // +0x248: crouchState (reset to idle)
  *(undefined4 *)(this + 600) = 0; // +0x258: some timer or flag
  *(undefined4 *)(this + 0x25c) = 0; // +0x25c: another timer/flag
  return;
}