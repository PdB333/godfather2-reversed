// FUNC_NAME: AudioManager::updateSpatialAudioProximity
undefined1 FUN_006c0050(float *position, char param_2, char param_3)
{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  double dVar11;
  float fVar12;
  undefined1 local_51;
  float local_50;
  float local_4c;
  float local_28;
  float local_24;
  float local_20;
  undefined1 local_1c [4];
  float local_18;
  
  iVar4 = DAT_012233a0;
  local_51 = 0;
  if ((*(char *)(DAT_01223394 + 0x10) != '\0') && (*(char *)(DAT_01223394 + 0x54) != '\0')) {
    if (*(float *)(DAT_01223394 + 0x5c) <= *(float *)(DAT_01223394 + 0x70)) {
      if (*(int *)(DAT_01223394 + 0x58) == 0) {
        return 1;
      }
    }
    else {
      fVar9 = *(float *)(DAT_01223394 + 0x70) / *(float *)(DAT_01223394 + 0x5c);
      if (*(int *)(DAT_01223394 + 0x58) != 0) {
        fVar9 = _DAT_00d5780c - fVar9;
      }
      if (_DAT_00d5780c <= fVar9) {
        return 1;
      }
    }
  }
  if ((DAT_0122339c == 0) || (DAT_012233a0 == 0)) {
    return 0;
  }
  uVar6 = FUN_0043ff40();  // getAudioObjectCount
  uVar7 = 0;
  if (uVar6 == 0) {
    return 0;
  }
  do {
    iVar2 = *(int *)(*(int *)(iVar4 + 4) + uVar7 * 4);
    if ((iVar2 != 0) && (iVar2 != 0x1f30)) {
      uVar3 = *(undefined4 *)(iVar2 + 0x564);  // object audio handle +0x564
      cVar5 = FUN_00424f20(uVar3);  // isAudioHandleValid
      if (cVar5 != '\0') {
        FUN_00424fb0(&local_28,uVar3);  // getObjectPosition
        fVar9 = *position - local_28;
        fVar12 = position[2] - local_20;
        fVar10 = fVar9 * fVar9 + fVar12 * fVar12;
        if ((fVar10 < (position[1] - local_24) * (position[1] - local_24)) && (fVar10 < DAT_00d5e288))
        {
          return local_51;
        }
        FUN_00425060(local_1c,uVar3);  // getAudioCone
        local_50 = local_18;
        local_4c = DAT_00d5ee64;
        if (param_3 == '\0') {
          local_4c = 0.0;
        }
        if (param_2 != '\0') {
          fVar8 = (float10)FUN_004251e0(uVar3);  // getAudioDistance
          fVar10 = (float)((uint)(float)fVar8 & DAT_00e44680);
          if (_DAT_00d5ca1c < fVar10) {
            if (DAT_00e446f4 < fVar10) {
              fVar10 = DAT_00e446f4;
            }
            local_4c = fVar10 * _DAT_00d5ee60 + local_4c;
            if (0.0 <= (float)fVar8) {
              local_50 = _DAT_00d5c458 * local_4c + local_50;
            }
            else {
              local_50 = DAT_00e44718 * local_4c + local_50;
            }
          }
        }
        if (local_50 != _DAT_0112a6cc) {
          dVar11 = (double)local_50;
          _DAT_0112a6cc = local_50;
          FUN_00b99fcb();  // updateLeftChannel
          DAT_0112a6c8 = (float)dVar11;
          dVar11 = (double)local_50;
          FUN_00b99e20();  // updateRightChannel
          DAT_00e50dd0 = (float)dVar11;
        }
        fVar10 = DAT_00e50dd0 * fVar12 + DAT_0112a6c8 * fVar9;
        if (0.0 < fVar10) {
          fVar8 = (float10)FUN_00425130(uVar3);  // getAudioVolume
          fVar1 = (float)(fVar8 + (float10)local_4c);
          if (fVar8 + (float10)local_4c != (float10)_DAT_00e50dcc) {
            dVar11 = (double)(fVar1 * _DAT_00d5c458);
            _DAT_00e50dcc = fVar1;
            FUN_00b99e20();  // updateRightChannel
            DAT_0112a6c4 = (float)dVar11 * (float)dVar11;
          }
          if (DAT_0112a6c4 <= (fVar10 * fVar10) / (fVar9 * fVar9 + fVar12 * fVar12)) {
            return 0;
          }
        }
        local_51 = 1;
      }
    }
    uVar7 = uVar7 + 1;
    if (uVar6 <= uVar7) {
      return local_51;
    }
  } while( true );
}