//FUNC_NAME: AudioSystem::computeSoundParameters
undefined4 __thiscall AudioSystem::computeSoundParameters(int thisPtr, float *outSoundParams, undefined4 *outColor)
{
  float *pfVar1;
  undefined4 uVar2;
  char soundType;
  byte flags;
  int *soundDataPtr;
  int iVar6;
  undefined4 uVar7;
  int fsOffset;
  float fVar8;
  float fVar9;
  float fVar11;
  double dVar10;
  float fVar12;
  float fVar13;
  float fVar14;
  byte local_79;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;

  // Get base sound intensity from some object (likely the listener or source)
  fVar13 = *(float *)(*(int *)(thisPtr + 4) + 0x8c); // +0x8c: some intensity value
  iVar6 = *(int *)(*(int *)(thisPtr + 4) + 0x10) + 0x30 + *(short *)(thisPtr + 0xe) * 0x24; // Compute index into an array
  fVar8 = (fVar13 - *(float *)(iVar6 + 0x18)) * *(float *)(iVar6 + 0x14);
  if (0.0 < fVar8) {
    if (DAT_00e2b1a4 <= fVar8) {
      fVar8 = DAT_00e2b1a4;
    }
  }
  else {
    fVar8 = 0.0;
  }
  fVar13 = (fVar13 - *(float *)(iVar6 + 0x20)) * *(float *)(iVar6 + 0x1c);
  if (0.0 < fVar13) {
    if (DAT_00e2b1a4 <= fVar13) {
      fVar13 = DAT_00e2b1a4;
    }
  }
  else {
    fVar13 = 0.0;
  }
  soundDataPtr = (int *)(*(int *)(thisPtr + 4) + 0x20); // +0x20: pointer to sound data list
  fVar13 = fVar13 * fVar8 * *(float *)(thisPtr + 0x30); // Multiply by a global volume factor
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_79 = 0;
  if (*soundDataPtr != 0) {
    soundType = *(char *)(*(int *)(thisPtr + 0x24) + 0x10); // +0x10: sound type identifier
    uVar7 = CONCAT31((int3)((uint)*(int *)(thisPtr + 0x24) >> 8), soundType);
    if (soundType == '\b') { // Type 8 (e.g., explosion)
      iVar6 = *soundDataPtr;
      if (iVar6 != 0) {
        *(int *)(iVar6 + 4) = *(int *)(iVar6 + 4) + 1; // Increment reference count
      }
      iVar6 = FUN_004e88c0(iVar6); // Get sound data for type 8
      if (iVar6 != 0) {
        flags = *(byte *)(iVar6 + 0x28);
        local_74 = *(undefined4 *)(iVar6 + 0x20);
        fVar8 = *(float *)(iVar6 + 0x10);
        fVar9 = *(float *)(iVar6 + 0x14);
        fVar11 = *(float *)(iVar6 + 0x18);
        fVar12 = *(float *)(iVar6 + 0x1c);
        local_79 = (byte)(*(uint *)(iVar6 + 0x28) >> 1) & 1;
        local_70 = *(undefined4 *)(iVar6 + 0x24);
LAB_004e6490:
        if ((flags & 1) != 0) {
          soundType = *(char *)(*(int *)(thisPtr + 0x24) + 0x10);
          if ((((soundType == '\b') || (soundType == '\x02')) || (soundType == '\r')) ||
             (fVar14 = DAT_00e2b1a4, soundType == '\v')) {
            *outSoundParams = fVar8;
            outSoundParams[1] = fVar9;
            outSoundParams[2] = fVar11;
            outSoundParams[3] = fVar12 * fVar13;
            fVar14 = DAT_00e2b1a4;
          }
          goto LAB_004e6514;
        }
      }
    }
    else if (soundType == '\x02') { // Type 2 (e.g., gunshot)
      iVar6 = *soundDataPtr;
      if (iVar6 != 0) {
        *(int *)(iVar6 + 4) = *(int *)(iVar6 + 4) + 1;
      }
      iVar6 = FUN_004e8920(iVar6); // Get sound data for type 2
      if (iVar6 != 0) {
        local_6c = *(undefined4 *)(iVar6 + 0x50);
        fVar8 = *(float *)(iVar6 + 0x10);
        fVar9 = *(float *)(iVar6 + 0x14);
        fVar11 = *(float *)(iVar6 + 0x18);
        fVar12 = *(float *)(iVar6 + 0x1c);
        flags = *(byte *)(iVar6 + 0x5c);
        goto LAB_004e6490;
      }
    }
    else if (soundType == '\r') { // Type 13 (e.g., dialog)
      iVar6 = *soundDataPtr;
      if (iVar6 != 0) {
        *(int *)(iVar6 + 4) = *(int *)(iVar6 + 4) + 1;
      }
      iVar6 = FUN_004e8980(iVar6); // Get sound data for type 13
      if (iVar6 != 0) {
        fVar8 = *(float *)(iVar6 + 0x10);
        fVar9 = *(float *)(iVar6 + 0x14);
        fVar11 = *(float *)(iVar6 + 0x18);
        fVar12 = *(float *)(iVar6 + 0x1c);
        flags = *(byte *)(iVar6 + 0x20);
        goto LAB_004e6490;
      }
    }
    else if (soundType == '\v') { // Type 11 (e.g., ambient)
      FUN_00414e30(soundDataPtr); // Release or reset sound data
      iVar6 = FUN_004e89e0(uVar7); // Get sound data for type 11
      if (iVar6 != 0) {
        fVar8 = *(float *)(iVar6 + 8);
        fVar12 = *(float *)(iVar6 + 0xc);
        flags = *(byte *)(iVar6 + 0x10);
        fVar11 = 0.0;
        fVar9 = 0.0;
        goto LAB_004e6490;
      }
    }
  }
  fVar14 = DAT_00e2b1a4;
  iVar6 = *(int *)(thisPtr + 0x24);
  fVar8 = *(float *)(iVar6 + 0x20);
  fVar9 = *(float *)(iVar6 + 0x24);
  fVar11 = *(float *)(thisPtr + 0x2c);
  *outSoundParams = *(float *)(iVar6 + 0x1c);
  outSoundParams[1] = fVar8;
  outSoundParams[2] = fVar9;
  outSoundParams[3] = fVar11 * fVar13;
LAB_004e6514:
  flags = *(byte *)(*(int *)(thisPtr + 0x24) + 0x12); // +0x12: some flag
  soundDataPtr = *(int **)(fsOffset + 0x2c); // FS segment offset (likely thread-local storage)
  if (flags != 0) {
    pfVar1 = (float *)(*(int *)(*soundDataPtr + 8) + 0x80 + *(int *)(thisPtr + 0x10));
    fVar8 = *pfVar1 - *(float *)(param_1 + 0x70);
    fVar11 = pfVar1[1] - *(float *)(param_1 + 0x74);
    fVar12 = pfVar1[2] - *(float *)(param_1 + 0x78);
    fVar9 = *(float *)(param_1 + 100) * fVar11 + *(float *)(param_1 + 0x68) * fVar12 +
            *(float *)(param_1 + 0x60) * fVar8;
    fVar13 = 0.0;
    if (DAT_00e2e780 < fVar9) {
      dVar10 = (double)(*(float *)(param_1 + 0x14c) * DAT_00e2cd54);
      FUN_00b99e20(); // Likely sqrt or math function
      fVar13 = (fVar9 / SQRT(fVar11 * fVar11 + fVar12 * fVar12 + fVar8 * fVar8) - (float)dVar10) /
               (DAT_00e2b1a4 - (float)dVar10);
      fVar14 = DAT_00e2b1a4;
      if (0.0 < fVar13) {
        if (DAT_00e2b1a4 <= fVar13) {
          fVar13 = DAT_00e2b1a4;
        }
      }
      else {
        fVar13 = 0.0;
      }
    }
    fVar8 = (float)flags * DAT_00e44640;
    outSoundParams[3] = (fVar8 * fVar13 + (fVar14 - fVar8)) * outSoundParams[3];
  }
  if ((*(uint *)(*(int *)(*soundDataPtr + 8) + *(int *)(thisPtr + 0x10)) & 0x80000) != 0) {
    iVar6 = *(int *)(thisPtr + 4);
    fVar8 = *(float *)(iVar6 + 0xa4);
    fVar9 = *(float *)(iVar6 + 0xa8);
    fVar11 = *(float *)(iVar6 + 0xac);
    fVar13 = outSoundParams[3];
    *outSoundParams = *(float *)(iVar6 + 0xa0) * *outSoundParams;
    outSoundParams[1] = fVar8 * outSoundParams[1];
    outSoundParams[2] = fVar9 * outSoundParams[2];
    outSoundParams[3] = fVar11 * outSoundParams[3];
    outSoundParams[3] = fVar13;
  }
  if (DAT_00e2af44 < outSoundParams[3] || DAT_00e2af44 == outSoundParams[3]) {
    if (local_79 == 0) {
      iVar6 = *(int *)(thisPtr + 0x24);
      uVar7 = *(undefined4 *)(iVar6 + 0x44);
      uVar2 = *(undefined4 *)(iVar6 + 0x48);
      *outColor = *(undefined4 *)(iVar6 + 0x40);
      outColor[1] = uVar7;
      outColor[2] = uVar2;
      outColor[3] = 0;
    }
    else {
      soundType = *(char *)(*(int *)(thisPtr + 0x24) + 0x10);
      if ((soundType == '\b') || (soundType == '\x02')) {
        outColor[1] = local_74;
        outColor[2] = local_70;
        *outColor = 0;
        outColor[3] = local_6c;
        return 1;
      }
    }
    return 1;
  }
  return 0;
}