// FUNC_NAME: GodfatherGameManager::processMissionEvent
void __thiscall GodfatherGameManager::processMissionEvent(int this, int missionData, int param3)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uStack_20;
  undefined1 auStack_1c [4];
  int aiStack_18 [2];
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Check if mission is already completed (bit 30 of flags at +0xDC)
  if ((*(uint *)(this + 0xdc) >> 0x1e & 1) != 0) {
    return;
  }
  // Initialize magic constants for hash/ID lookup
  local_10 = 0xbadbadba;
  local_c = 0xbeefbeef;
  local_8 = 0xeac15a55;
  local_4 = 0x91100911;
  FUN_00810960(missionData, &local_10);  // Initialize mission data from param2
  piVar2 = (int *)FUN_00446100(&local_10, 0);  // Get mission object from hash
  iVar4 = 0;
  if (piVar2 != (int *)0x0) {
    missionData = 0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0xd7e44d6a, &missionData);  // Query mission state
    if (cVar1 == '\0') {
      iVar4 = 0;
    }
    else {
      iVar4 = missionData;
      if (missionData != 0) {
        // Copy mission state data (4 dwords at +0x7C)
        local_10 = *(undefined4 *)(missionData + 0x7c);
        local_c = *(undefined4 *)(missionData + 0x80);
        local_8 = *(undefined4 *)(missionData + 0x84);
        local_4 = *(undefined4 *)(missionData + 0x88);
      }
    }
  }
  // Check if mission is already active and not forced
  if ((((char)param3 == '\0') && ((*(byte *)(this + 0xdc) & 1) != 0)) &&
     (iVar3 = FUN_00810920(&local_10), iVar3 != 0)) {
    return;
  }
  iVar3 = FUN_008eadd0(&local_10);  // Check if mission is valid
  if (iVar3 != 0) {
    *(uint *)(this + 0xdc) = *(uint *)(this + 0xdc) | 0x40000000;  // Set bit 30 (mission active)
    iVar3 = this;
    if (iVar4 != 0) {
      FUN_00792560(iVar4);  // Initialize mission state
      FUN_007906c0(this);   // Setup mission
      iVar3 = iVar4;
    }
    cVar1 = FUN_008f0bb0(&local_10, 0xffffffff, iVar3, 0);  // Start mission
    if (cVar1 != '\0') {
      return;
    }
    *(uint *)(this + 0xdc) = *(uint *)(this + 0xdc) & 0xbfffffff;  // Clear bit 30
    return;
  }
  missionData = 0;
  iVar4 = FUN_004461c0(&local_10, 0);  // Get mission instance
  if (iVar4 == 0) {
    return;
  }
  iVar4 = FUN_0043aaf0();  // Get current player
  if ((iVar4 != 0) && (cVar1 = FUN_00852d60(iVar4), cVar1 != '\0')) {  // Check if player is valid
    uVar8 = 0;
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = FUN_00445f00(this);  // Get mission ID
    missionData = FUN_00856780(&local_10, uVar5, uVar6, uVar7, uVar8);  // Create mission event
    iVar4 = missionData;
    if (missionData != 0) goto LAB_00810e9b;
  }
  param3 = 0;
  param3 = FUN_00446130(&local_10, 0);  // Get mission objective
  uStack_20 = 0;
  cVar1 = FUN_0080f5d0(param3, 0x647df06b, &uStack_20);  // Check objective type
  if (cVar1 != '\0') {
    *(uint *)(this + 0xdc) = *(uint *)(this + 0xdc) | 0x20000000;  // Set bit 29
    FUN_008cff70(this, &param3);  // Process objective
  }
  if (param3 == 0) {
    return;
  }
  FUN_00475660(param3, 0x38523fc3, &missionData);  // Get mission event data
  iVar4 = missionData;
  if (missionData == 0) {
    return;
  }
LAB_00810e9b:
  // Link mission event to game manager
  param3 = *(undefined4 *)(this + 0x18);
  missionData = *(undefined4 *)(iVar4 + 0x18);
  piVar2 = (int *)(this + 0xe4);
  uVar5 = FUN_00810c50(&missionData, this + 0x20, &param3, piVar2);  // Link event chain
  *(undefined4 *)(iVar4 + 0x18) = uVar5;
  *piVar2 = *piVar2 + 1;  // Increment event count
  FUN_008109d0(iVar4);  // Initialize event
  FUN_0045ca00(iVar4);  // Register event
  FUN_0045c400(this + 0x7c, auStack_1c, 0);  // Update mission state
  if ((*(uint *)(this + 0xdc) >> 1 & 1) != 0) {  // Check bit 1
    FUN_00810900(iVar4);  // Process event
  }
  if (aiStack_18[0] != 0) {
    FUN_004daf90(aiStack_18);  // Cleanup
  }
  return;
}