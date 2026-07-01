// Xbox PDB: EARS_Modules_TargetingReticuleManager_ShowChaseCamReticule
// FUNC_NAME: ChaseCamera::activateChaseMode
void __fastcall ChaseCamera::activateChaseMode(int this)
{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined1 local_20 [28];
  
  // Check if chase mode is already active (bit 1 of flags at +0x10)
  if ((*(uint *)(this + 0x10) >> 1 & 1) == 0) {
    FUN_0081dce0(); // ChaseCamera::resetTargetHistory
    iVar5 = FUN_004262f0(0); // Get current game time
    
    // Build chase camera parameters structure
    local_40 = *(undefined4 *)(this + 0x108); // +0x108: target offset X
    local_3c = *(undefined4 *)(this + 0x10c); // +0x10c: target offset Y
    local_38 = *(undefined4 *)(this + 0x110); // +0x110: target offset Z
    local_24 = &local_40;
    local_34 = _DAT_00d5780c; // Global chase camera config
    local_28 = 0xffffffff; // -1 = no specific target
    local_30 = 5; // Chase mode ID
    local_2c = iVar5; // Start time
    
    FUN_004eacb0("hud_targeting_chase"); // UI::showHudElement
    
    // Allocate chase camera command
    piVar6 = (int *)FUN_004df3c0(&local_44, local_20, iVar5 + 0x40, 0x1ff, 0, &local_30);
    piVar1 = (int *)(this + 0xe4); // +0xe4: current chase command pointer
    
    // Free old command if exists
    if (*(int *)(this + 0xe4) != 0) {
      *(undefined4 *)(*(int *)(this + 0xe4) + 8) = 0;
      *piVar1 = 0;
    }
    
    // Store new command
    iVar5 = *piVar6;
    *piVar1 = iVar5;
    if (iVar5 != 0) {
      *(int **)(iVar5 + 8) = piVar1;
      *piVar6 = 0;
    }
    if (local_44 != 0) {
      *(undefined4 *)(local_44 + 8) = 0;
    }
    
    // Set camera position from target
    FUN_004df830(*(undefined4 *)(this + 0xf8)); // ChaseCamera::setCameraPosition
    iVar5 = *(int *)(this + 0xf8); // +0xf8: camera transform
    uVar2 = *(undefined4 *)(this + 0x24); // +0x24: target position X
    uVar3 = *(undefined4 *)(this + 0x28); // +0x28: target position Y
    uVar4 = *(undefined4 *)(this + 0x2c); // +0x2c: target position Z
    *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(this + 0x20); // +0x20: camera offset X
    *(undefined4 *)(iVar5 + 0x14) = uVar2;
    *(undefined4 *)(iVar5 + 0x18) = uVar3;
    *(undefined4 *)(iVar5 + 0x1c) = uVar4;
    
    // Set chase mode active flag
    *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 2;
  }
  return;
}