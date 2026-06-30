// FUNC_NAME: AudioManager::updateAuxVolume
undefined1 AudioManager__updateAuxVolume(int this, float auxVolume, float param3)

{
  int iVar1;
  float fVar2;
  bool bVar3;
  char cVar4;
  ushort in_AX;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  float fVar8;
  undefined4 *puVar9;
  undefined1 local_11;
  int local_8;
  
  local_11 = 1;
  // Check if aux channel index is valid (0-127)
  if (0x7f < in_AX) {
    return 0;
  }
  // Calculate offset into aux channel data array (0xF8 bytes per channel, +0x5A0 base offset)
  int channelOffset = (uint)in_AX * 0xf8 + 0x5a0 + this;  // +0x5A0: aux channel data start
  // Clamp auxVolume to valid range [0.0, DAT_00e2b1a4]
  if (0.0 <= auxVolume) {
    fVar8 = DAT_00e2b1a4;
    if (auxVolume <= DAT_00e2b1a4) goto LAB_005ec162;
  }
  else {
    fVar8 = 0.0;
  }
  auxVolume = fVar8;
LAB_005ec162:
  // Normalize param3 (angle) into range [0, DAT_00e2af34]
  for (fVar8 = DAT_011274f0 * param3 * DAT_00e2af34; fVar8 < 0.0; fVar8 = fVar8 + DAT_00e2af34) {
  }
  for (; DAT_00e2af34 < fVar8; fVar8 = fVar8 - DAT_00e2af34) {
  }
  // Check if volume changed
  bVar3 = auxVolume != *(float *)(channelOffset + 0x10);  // +0x10: current aux volume
  // Check if angle changed, encode flag in param3
  param3 = (float)CONCAT31(param3._1_3_,1);
  if (*(float *)(channelOffset + 8) == fVar8) {  // +0x8: current angle
    // Set bit 8 to indicate angle match
    param3 = (float)((uint)param3._1_3_ << 8);
  }
  int isActive = 0;
  iVar5 = FUN_005dc670(*(undefined4 *)(channelOffset + 0xf0));  // +0xF0: channel sound handle
  if (iVar5 != 0) {
    isActive = *(int *)(iVar5 + 0x274);  // +0x274: sound active flag
  }
  // If volume changed, angle changed, or sound is active/starting
  if (((bVar3) || (param3._0_1_ != '\0')) || (isActive != 0)) {
    if ((DAT_01143360 != 0) && (*(int *)(this + 0x56c) != 0)) {  // +0x56C: audio system enabled
      float currentVolume = *(float *)(channelOffset + 0x14);  // +0x14: current volume
      int auxSendChanged = 0;
      int sendToMasterChanged = 0;
      int local_8 = 0;
      if (param3._0_1_ != '\0') {
        auxSendChanged = FUN_005e9d10();  // Process aux send parameter change
      }
      if (bVar3) {
        // Update send levels to aux 3 bus and master
        puVar9 = &param3;
        uVar6 = FUN_004dafd0("AuxSend3",puVar9);  // Get AuxSend3 parameter ID
        sendToMasterChanged = FUN_005e9d90(uVar6,puVar9);  // Set AuxSend3 parameter
        puVar9 = &param3;
        uVar6 = FUN_004dafd0("SendToMaster",puVar9);  // Get SendToMaster parameter ID
        local_8 = FUN_005e9d90(uVar6,puVar9);  // Set SendToMaster parameter
      }
      FUN_00c9eac0();  // Begin audio parameter update batch
      if (auxSendChanged != 0) {
        FUN_00ca4e90(0,fVar8);  // Update aux send angle
      }
      if (sendToMasterChanged != 0) {
        FUN_00ca4e90(0,currentVolume * auxVolume);  // Update send level (volume * position)
      }
      if (local_8 != 0) {
        FUN_00ca4e90(0,auxVolume);  // Update master send volume
      }
      FUN_00c9eae0();  // End audio parameter update batch
      cVar4 = FUN_005ebfa0(this,*(undefined4 *)(channelOffset + 0xf0),channelOffset + 0xbc);  // +0xBC: sound play state
      if (cVar4 == '\0') {
        local_11 = 0;  // Failed to update sound
      }
    }
    // Store updated values
    *(float *)(channelOffset + 0x10) = auxVolume;  // +0x10: current aux volume
    *(float *)(channelOffset + 8) = fVar8;  // +0x8: current angle
  }
  return local_11;
}