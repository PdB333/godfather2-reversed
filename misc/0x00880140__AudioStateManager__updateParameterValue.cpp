// FUNC_NAME: AudioStateManager::updateParameterValue
float10 __thiscall AudioStateManager::updateParameterValue(int this, int *param_2)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float local_8;
  
  local_8 = 0.0;
  if ((param_2 != (int *)0x0) &&
     (fVar5 = (float10)(**(code **)(*param_2 + 0x1a8))(), (float10)DAT_00d5779c < fVar5)) {
    uVar1 = (**(code **)(*param_2 + 0x220))(); // Some count getter
    fVar6 = 0.0;
    fVar9 = 0.0;
    uVar4 = 0;
    if (3 < (int)uVar1) {
      puVar2 = (uint *)(*(int *)(param_2[0xd8] + 0x48) + 0x168); // +0x168 offset in struct
      iVar3 = (uVar1 - 4 >> 2) + 1;
      uVar4 = iVar3 * 4;
      do {
        fVar8 = (float)(puVar2[-0x30] & DAT_00e44680); // Bitmasked float
        fVar7 = fVar8;
        if ((fVar8 <= fVar6) && (fVar7 = fVar6, fVar9 < fVar8)) {
          fVar9 = fVar8;
        }
        fVar8 = (float)(*puVar2 & DAT_00e44680);
        fVar6 = fVar8;
        if ((fVar8 <= fVar7) && (fVar6 = fVar7, fVar9 < fVar8)) {
          fVar9 = fVar8;
        }
        fVar8 = (float)(puVar2[0x30] & DAT_00e44680);
        fVar7 = fVar8;
        if ((fVar8 <= fVar6) && (fVar7 = fVar6, fVar9 < fVar8)) {
          fVar9 = fVar8;
        }
        fVar8 = (float)(puVar2[0x60] & DAT_00e44680);
        fVar6 = fVar8;
        if ((fVar8 <= fVar7) && (fVar6 = fVar7, fVar9 < fVar8)) {
          fVar9 = fVar8;
        }
        puVar2 = puVar2 + 0xc0; // stride 0xc0 = 192 bytes per entry
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if (uVar4 < uVar1) {
      puVar2 = (uint *)(*(int *)(param_2[0xd8] + 0x48) + 0xa8 + uVar4 * 0xc0);
      iVar3 = uVar1 - uVar4;
      fVar7 = fVar6;
      do {
        fVar8 = (float)(*puVar2 & DAT_00e44680);
        fVar6 = fVar8;
        if ((fVar8 <= fVar7) && (fVar6 = fVar7, fVar9 < fVar8)) {
          fVar9 = fVar8;
        }
        puVar2 = puVar2 + 0x30;
        iVar3 = iVar3 + -1;
        fVar7 = fVar6;
      } while (iVar3 != 0);
    }
    fVar7 = (float)param_2[0x1e6]; // min threshold
    fVar6 = (fVar9 + fVar6) * _DAT_00d5c458; // scale factor
    fVar9 = (float)param_2[0x1e7] - fVar7; // max - min
    if ((fVar6 < fVar7) || (fVar9 < DAT_00e44598)) {
      local_8 = 0.0;
    }
    else {
      local_8 = _DAT_00d5780c; // 1.0
      if (fVar6 <= (float)param_2[0x1e7]) {
        local_8 = (fVar6 - fVar7) / fVar9; // normalize between 0 and 1
      }
    }
  }
  fVar6 = 0.0;
  if (local_8 <= DAT_00e44598) {
    *(undefined4 *)(this + 0x13c) = DAT_00d5ccf8; // reset state/flag
  }
  else if (DAT_00e44564 <= *(float *)(this + 0x13c)) {
    fVar6 = DAT_01205214 - *(float *)(this + 0x13c); // decay
  }
  else {
    *(float *)(this + 0x13c) = DAT_01205214; // set state/flag to 1.0
    fVar6 = 0.0;
  }
  param_2 = (int *)DAT_00d5ef6c; // default curve
  if ((fVar6 < _DAT_00d5cf70) && (0.0 <= *(float *)(this + 0x13c))) {
    param_2 = (int *)DAT_00d58cbc; // alternative curve
  }
  fVar5 = (float10)FUN_004b9c30(local_8,*(undefined4 *)(this + 0x138),param_2); // apply curve
  *(float *)(this + 0x138) = (float)fVar5;
  fVar6 = _DAT_00d5780c; // 1.0
  if (((float10)1 < fVar5) || (fVar6 = 0.0, (float)fVar5 < 0.0)) {
    *(float *)(this + 0x138) = fVar6; // clamp to [0,1]
  }
  return (float10)*(float *)(this + 0x138);
}