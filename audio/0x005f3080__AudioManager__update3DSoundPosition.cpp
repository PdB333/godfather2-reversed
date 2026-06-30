// FUNC_NAME: AudioManager::update3DSoundPosition
void AudioManager::update3DSoundPosition(int param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  float local_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  if (param_1 != 0) {
    piVar1 = *(int **)(param_1 + 0x2c); // +0x2c: soundInstance pointer
    local_c = DAT_00e2b1a4; // default volume
    local_8 = DAT_00e2b1a4; // default pan
    local_4 = 96000; // default pitch (96000 = 1.0 in fixed point)
    if ((piVar1 != (int *)0x0) && (*(int *)(param_1 + 0x30) != 0)) { // +0x30: sound handle
      if (*piVar1 != 0) {
        iVar2 = piVar1[0x17]; // +0x5c: sound bank index
        local_18 = 0.0;
        local_14 = DAT_00e2b1a4;
        local_10 = 96000;
        if ((*(byte *)(piVar1 + 0x1c) & 4) == 0) { // +0x70: flags, bit 2 = use 3D position
          cVar3 = FUN_005dcb60(DAT_01223508,iVar2); // getSoundVolume
        }
        else {
          cVar3 = FUN_005dcac0(DAT_01223508,&local_18,&local_14,piVar1[0x1b]); // getSound3DInfo
        }
        if (cVar3 != '\\0') {
          local_c = local_18;
          local_8 = local_14;
        }
        cVar3 = FUN_005de7e0(DAT_01223508,iVar2,&local_10); // getSoundPitch
        if (cVar3 != '\\0') {
          local_4 = local_10;
        }
      }
      local_c = *(float *)(param_1 + 0x4c) * local_c; // +0x4c: volume multiplier
      (**(code **)(param_1 + 0x34))(piVar1,param_1,&local_c); // +0x34: applySoundUpdate callback
    }
  }
  return;
}