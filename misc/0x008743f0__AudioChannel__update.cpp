// FUNC_NAME: AudioChannel::update
void __fastcall AudioChannel::update(int this)
{
  float fVar1;
  float fVar2;
  int iVar4;
  int *piVar5;
  float fVar6;
  float local_4;
  
  if (*(char *)(this + 5) == '\0') {
LAB_0087444d:
    iVar4 = *(int *)(this + 0x104); // +0x104: pActiveSound1
    if (iVar4 != 0) {
      FUN_005e6820(iVar4,0,0); // soundStop
      FUN_005e6660(iVar4); // soundRelease
      *(int *)(this + 0x104) = 0;
    }
    iVar4 = *(int *)(this + 0x108); // +0x108: pActiveSound2
    if (iVar4 != 0) {
      FUN_005e6820(iVar4,0,0);
      FUN_005e6660(iVar4);
      *(int *)(this + 0x108) = 0;
    }
  }
  else if (((((*(int *)(this + 0x84) == 0) && (*(int *)(this + 0x88) == 0)) &&
            (*(int *)(this + 0x8c) == 0)) && (*(int *)(this + 0x90) == 0)) ||
          (*(int *)(this + 0x104) != 0)) {
    if (*(char *)(this + 5) == '\0') goto LAB_0087444d;
  }
  else {
    // Start new sounds from the sound data at +0x84 and +0x94
    *(int *)(this + 0x104) = FUN_00873ca0(this + 0x84); // createSoundFromData
    *(int *)(this + 0x108) = FUN_00873ca0(this + 0x94);
  }
  if (*(char *)(this + 6) == '\0') goto LAB_008744e6;
  if (DAT_01205224 <= *(uint *)(this + 8)) {
    if (*(int *)(this + 0x11c) == 0) {
      if (*(int *)(this + 0xc) < *(int *)(this + 0x20)) {
        *(int *)(this + 0x11c) = FUN_00873ca0(this + 0xe4); // createLoopSound
      }
      goto LAB_008744e6;
    }
    if (*(int *)(this + 0xc) <= *(int *)(this + 0x20)) goto LAB_008744e6;
    FUN_00873910(*(int *)(this + 0x11c)); // stopLoopSound
    *(int *)(this + 0x11c) = 0;
  }
  *(char *)(this + 6) = 0;
LAB_008744e6:
  piVar5 = (int *)(this + 0x104);
  if (*(int *)(this + 0x104) != 0) {
    iVar4 = *(int *)(this + 0x20); // +0x20: currentTime
    local_4 = *(float *)(this + 0x3c); // +0x3c: volumeEnd
    if (iVar4 < *(int *)(this + 0x30)) {
      local_4 = *(float *)(this + 0x38); // +0x38: volumeStart
    }
    else if (iVar4 < *(int *)(this + 0x34)) {
      local_4 = (float)(iVar4 - *(int *)(this + 0x30)) * *(float *)(this + 0x44) *
                *(float *)(this + 0x40) + *(float *)(this + 0x38);
    }
    FUN_005e6750(*(int *)(this + 0x104), local_4); // setSoundVolume
    FUN_005e6700(*piVar5, *(float *)(this + 0x48) * *(float *)(this + 0x24) +
                         *(float *)(this + 0x4c)); // setSoundPitch
  }
  if (*(float *)(this + 0x50) < *(float *)(this + 0x28) ||
      *(float *)(this + 0x50) == *(float *)(this + 0x28)) {
    if (*(int *)(this + 0x118) == 0) {
      *(int *)(this + 0x118) = FUN_00873ca0(this + 0xd4); // createCrossfadeSound
    }
    if (*(int *)(this + 0x118) != 0) {
      fVar6 = (*(float *)(this + 0x28) - *(float *)(this + 0x50)) * *(float *)(this + 0x70);
      fVar2 = *(float *)(this + 0x6c);
      fVar1 = *(float *)(this + 0x60);
      FUN_005e6750(*(int *)(this + 0x118),
                   *(float *)(this + 0x68) * fVar6 + *(float *)(this + 0x58));
      FUN_005e6700(*(int *)(this + 0x118), fVar2 * fVar6 + fVar1);
    }
  }
  else {
    iVar4 = *(int *)(this + 0x118);
    if (iVar4 != 0) {
      FUN_005e6820(iVar4, 0, 0);
      FUN_005e6660(iVar4);
      *(int *)(this + 0x118) = 0;
    }
  }
  fVar2 = *(float *)(this + 0x28);
  if (((((*(float *)(this + 0x78) <= fVar2) && (fVar2 <= *(float *)(this + 0x7c))) &&
       (fVar2 < *(float *)(this + 0x80) - DAT_00d76300)) &&
      (((*(int *)(this + 0xf4) != 0 || (*(int *)(this + 0xf8) != 0)) ||
       ((*(int *)(this + 0xfc) != 0 || (*(int *)(this + 0x100) != 0)))))) &&
     (*(float *)(this + 0x74) <= DAT_01205228 && DAT_01205228 != *(float *)(this + 0x74))) {
    *(int *)(this + 0x120) = FUN_00873ca0(this + 0xf4); // createRandomSound
    *(float *)(this + 0x74) = DAT_01205228 + _DAT_00d762fc;
  }
  FUN_008742d0(2, _DAT_00d76318); // setChannelParam
  FUN_008742d0(3, _DAT_00d76314);
  FUN_008742d0(4, 0x3f800000); // 1.0f
  int uVar3 = *(int *)(this + 0x1c); // +0x1c: soundFlags
  iVar4 = 8;
  do {
    if (*piVar5 != 0) {
      FUN_005e6580(*piVar5, this + 0x10); // setSoundPosition
      FUN_005e67c0(*piVar5, uVar3); // setSoundFlags
    }
    piVar5 = piVar5 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(float *)(this + 0x80) = *(float *)(this + 0x28); // update lastPlayedTime
  return;
}