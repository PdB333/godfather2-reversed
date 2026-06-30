// FUNC_NAME: AudioManager::setAuxSendVolume
undefined1 __thiscall AudioManager::setAuxSendVolume(int this, float param_2, float param_3)
{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  undefined1 uVar8;
  undefined4 *puVar9;
  undefined1 local_9;
  
  uVar8 = 0;
  local_9 = 0;
  iVar2 = 0;
  pfVar7 = (float *)(this + 0x82ac); // +0x82ac: audio channel array start (10 channels, 0x5c bytes each)
  while (((int)pfVar7[1] < 0 || (*pfVar7 != param_2))) {
    iVar2 = iVar2 + 1;
    pfVar7 = pfVar7 + 0x5c;
    if (9 < iVar2) {
      return 0;
    }
  }
  if (-1 < iVar2) {
    iVar2 = iVar2 * 0x170 + 0x8210 + this; // +0x8210: audio channel data array (0x170 bytes per channel)
    FUN_00ab4db0(&DAT_00e2aea0); // lock mutex
    if (*(int *)(*(int *)(iVar2 + 0x9c) * 0x10 + 0x81c4 + this) != 0) { // +0x9c: channel index, +0x81c4: channel active flags
      puVar9 = &param_2;
      uVar3 = FUN_004dafd0("AuxSend1",puVar9); // get audio bus "AuxSend1"
      iVar4 = FUN_005e9d90(uVar3,puVar9); // check if bus exists
      puVar9 = &param_2;
      uVar3 = FUN_004dafd0("AuxSend3",puVar9); // get audio bus "AuxSend3"
      iVar5 = FUN_005e9d90(uVar3,puVar9);
      puVar9 = &param_2;
      uVar3 = FUN_004dafd0("SendToMaster",puVar9); // get audio bus "SendToMaster"
      iVar6 = FUN_005e9d90(uVar3,puVar9);
      uVar8 = local_9;
      if (((DAT_00e2b05c <= *(float *)(iVar2 + 0x134)) && (iVar5 != 0)) && (iVar6 != 0)) { // +0x134: some volume threshold
        *(float *)(iVar2 + 0x90) = param_3; // +0x90: aux send volume
        param_2 = *(float *)(iVar2 + 0x98) * param_3; // +0x98: channel volume multiplier
        FUN_00c9eac0(); // begin audio parameter update
        if (iVar4 != 0) {
          fVar1 = param_2;
          if (*(char *)(this + 0x9089) == '\0') { // +0x9089: mute flag
            fVar1 = 0.0;
          }
          FUN_00ca4e90(0,fVar1); // set audio parameter (bus 0, value)
        }
        FUN_00ca4e90(0,param_2); // set audio parameter for master
        FUN_00ca4e90(0,*(undefined4 *)(iVar2 + 0x90)); // set aux send volume
        FUN_00c9eae0(); // end audio parameter update
        local_9 = 1;
        uVar8 = local_9;
      }
    }
    FUN_00ab4e70(); // unlock mutex
  }
  return uVar8;
}