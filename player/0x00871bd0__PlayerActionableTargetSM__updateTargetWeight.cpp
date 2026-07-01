// FUNC_NAME: PlayerActionableTargetSM::updateTargetWeight
float __thiscall PlayerActionableTargetSM::updateTargetWeight(int thisPtr, float param_2)
{
  char cVar1;
  int iVar2;
  float *pfVar3;
  float unaff_ESI;
  float10 fVar4;
  float fVar5;
  double dVar6;
  float local_1c;
  float local_18;

  iVar2 = FUN_00471610(); // likely InputManager::getInstance or similar
  if ((DAT_00d5ef84 <= (float)((uint)*(float *)(iVar2 + 0x20) & DAT_00e44680)) ||
     (DAT_00d5ef84 <= (float)(*(uint *)(iVar2 + 0x28) & DAT_00e44680))) {
    dVar6 = (double)*(float *)(iVar2 + 0x20);
    FUN_00b9a9fa(); // likely some audio or camera function
    fVar5 = (float)dVar6;
  }
  else {
    fVar5 = 0.0;
  }
  fVar4 = (float10)FUN_004a1580(fVar5 - param_2); // likely fabs or clamp
  local_18 = (float)fVar4;
  pfVar3 = &local_1c;
  local_1c = 0.0;
  cVar1 = (**(code **)(**(int **)(thisPtr + 4) + 0x10))(0xfb67a6e2); // vtable call, likely getInputDevice or similar
  fVar5 = *(float *)(*(int *)(*(int *)((-(uint)(cVar1 != '\0') & (uint)pfVar3) + 4) + 0x380) + 8) *
          DAT_00e44748 * DAT_00e445c8; // some scaling factors
  local_1c = DAT_00e44564 - fVar5;
  if (fVar5 < unaff_ESI) {
    return ((float10)1 / (float10)fVar5) * (float10)fVar5;
  }
  pfVar3 = &local_1c;
  if (DAT_00e44564 - fVar5 <= unaff_ESI) {
    pfVar3 = (float *)&stack0xffffffe0;
  }
  return ((float10)1 / (float10)fVar5) * (float10)*pfVar3;
}