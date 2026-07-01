// FUNC_NAME: VehicleEngine::updateThrottle
void __thiscall VehicleEngine::updateThrottle(float param_1, float param_2)
{
  float *pfVar1;
  float fVar2;
  float *pfVar3;
  float10 fVar4;
  float fVar5;
  float local_4;
  
  local_4 = param_1;
  fVar4 = (float10)FUN_00799230(); // getCurrentTime() or similar
  fVar4 = (float10)FUN_006d6350((float)(fVar4 - (float10)*(float *)((int)param_1 + 0x8c))); // delta time since last update
  local_4 = DAT_00d5ccf8; // minThrottle global
  fVar2 = _DAT_00d5780c; // maxThrottle global
  fVar5 = (float)fVar4;
  if (DAT_00e44598 < param_2) { // if some threshold < param_2
    fVar5 = fVar5 / param_2; // normalize by param_2
  }
  fVar5 = (fVar5 / DAT_00e52fec) * DAT_00d5eee4; // scale by some factors
  pfVar1 = (float *)((int)param_1 + 0x78); // +0x78: currentThrottle
  *pfVar1 = fVar5;
  param_2 = fVar2;
  if (fVar5 <= fVar2) {
    pfVar3 = &local_4;
    if (local_4 <= fVar5) {
      pfVar3 = pfVar1;
    }
  }
  else {
    pfVar3 = &param_2;
  }
  param_2 = *pfVar3;
  *pfVar1 = param_2; // clamp throttle between min and max
  FUN_007ac530(param_2); // applyThrottle(param_2)
  return;
}