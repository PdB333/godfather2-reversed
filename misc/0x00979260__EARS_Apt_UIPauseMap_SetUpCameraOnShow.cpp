// Xbox PDB: EARS_Apt_UIPauseMap_SetUpCameraOnShow
// FUNC_NAME: PlayerSM::handleTakeDamage
undefined4 __fastcall PlayerSM::handleTakeDamage(int this)
{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  uint *puVar6;
  int iVar7;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined1 local_a8 [4];
  int iStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 local_90 [12];
  undefined4 local_84;
  undefined4 local_74;
  undefined4 local_64;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check if game is not in a specific state (e.g., not in menu or loading)
  if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    FUN_0079d4f0();
  }
  local_b0 = DAT_0112dc4c;
  local_ac = 0;
  local_a8[0] = 0;
  FUN_00408a00(&local_b0,0); // Some initialization
  FUN_009ceae0(0); // Audio related
  FUN_00413950(0); // Input related
  FUN_004e9cc0(4); // Vibration/force feedback
  FUN_0088daa0(8); // Camera shake
  puVar6 = (uint *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e575a8;
  *puVar6 = *puVar6 + 4;
  *(undefined1 *)*puVar6 = 1;
  *puVar6 = *puVar6 + 4 & 0xfffffffc;
  FUN_0088d680(); // Apply camera shake
  
  if (*(int *)(this + 0x68) != 0) { // Check if there's a valid entity
    local_84 = 0;
    local_74 = 0;
    local_64 = 0;
    local_54 = _DAT_00d5780c;
    FUN_00470f80(local_90); // Get some transform/position
    FUN_0056c180(local_90,&local_ac,&local_b0,local_a8); // Calculate damage direction/force
    
    if (*(char *)(this + 0xc0) == '\0') { // First time taking damage in this state
      iVar7 = *(int *)(this + 0x68);
      uVar2 = *(undefined4 *)(iVar7 + 0x94);
      uVar3 = *(undefined4 *)(iVar7 + 0x98);
      uVar4 = *(undefined4 *)(iVar7 + 0x9c);
      *(undefined4 *)(this + 0xd0) = *(undefined4 *)(iVar7 + 0x90);
      *(undefined4 *)(this + 0xd4) = uVar2;
      *(undefined4 *)(this + 0xd8) = uVar3;
      *(undefined4 *)(this + 0xdc) = uVar4;
      iVar7 = *(int *)(this + 0x68);
      *(undefined4 *)(this + 0xd4) = local_ac;
      uVar2 = *(undefined4 *)(this + 0xd4);
      uVar3 = *(undefined4 *)(this + 0xd8);
      uVar4 = *(undefined4 *)(this + 0xdc);
      *(undefined4 *)(iVar7 + 0x90) = *(undefined4 *)(this + 0xd0);
      *(undefined4 *)(iVar7 + 0x94) = uVar2;
      *(undefined4 *)(iVar7 + 0x98) = uVar3;
      *(undefined4 *)(iVar7 + 0x9c) = uVar4;
      *(undefined4 *)(this + 0xe0) = *(undefined4 *)(*(int *)(this + 0x68) + 0xb4);
      *(undefined1 *)(this + 0xc0) = 1; // Mark as damaged
    }
    else {
      iVar7 = *(int *)(this + 0x68);
      *(undefined4 *)(this + 0xd4) = local_ac;
      uVar2 = *(undefined4 *)(this + 0xd4);
      uVar3 = *(undefined4 *)(this + 0xd8);
      uVar4 = *(undefined4 *)(this + 0xdc);
      *(undefined4 *)(iVar7 + 0x90) = *(undefined4 *)(this + 0xd0);
      *(undefined4 *)(iVar7 + 0x94) = uVar2;
      *(undefined4 *)(iVar7 + 0x98) = uVar3;
      *(undefined4 *)(iVar7 + 0x9c) = uVar4;
      *(undefined4 *)(*(int *)(this + 0x68) + 0xb4) = *(undefined4 *)(this + 0xe0);
    }
    FUN_00478670(*(undefined4 *)(*(int *)(this + 0x68) + 0xe8)); // Apply damage to health component
    iVar7 = DAT_0122339c;
    FUN_00955ef0(); // Update some state
    *(undefined1 *)(iVar7 + 0x168) = 1;
    uVar5 = FUN_009568d0(); // Check if player is dead
    *(undefined1 *)(*(int *)(this + 0x68) + 0x104) = uVar5;
    uVar2 = _DAT_00d5780c;
    if (*(int *)(this + 0x144) == *(int *)(this + 0x148)) { // Check if damage type matches
      if ((*(uint *)(this + 0x60) >> 5 & 1) != 0) { // Check if player is in a specific state (e.g., not invulnerable)
        uStack_a0 = *(undefined4 *)(this + 0x94);
        iVar7 = *(int *)(this + 0x68);
        uStack_9c = *(undefined4 *)(this + 0x98);
        uStack_98 = *(undefined4 *)(this + 0x9c);
        uStack_94 = _DAT_00d5780c;
        *(undefined4 *)(iVar7 + 0xd0) = uStack_a0;
        *(undefined4 *)(iVar7 + 0xd4) = uStack_9c;
        *(undefined4 *)(iVar7 + 0xd8) = uStack_98;
        *(undefined4 *)(iVar7 + 0xdc) = uVar2;
      }
      FUN_00424dc0(0,*(int *)(this + 0x68),*(undefined4 *)(*(int *)(this + 0x68) + 0x108),8,1); // Play hit reaction animation
      *(undefined4 *)(this + 0x70) = DAT_01205214;
      *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 8; // Set some flag
      iVar7 = FUN_004262f0(0); // Get camera manager
      uStack_50 = *(undefined4 *)(iVar7 + 0x40);
      uStack_4c = *(undefined4 *)(iVar7 + 0x44);
      uStack_48 = *(undefined4 *)(iVar7 + 0x48);
      uStack_44 = *(undefined4 *)(iVar7 + 0x4c);
      uStack_40 = *(undefined4 *)(iVar7 + 0x50);
      uStack_3c = *(undefined4 *)(iVar7 + 0x54);
      uStack_38 = *(undefined4 *)(iVar7 + 0x58);
      uStack_34 = *(undefined4 *)(iVar7 + 0x5c);
      uStack_30 = *(undefined4 *)(iVar7 + 0x60);
      uStack_2c = *(undefined4 *)(iVar7 + 100);
      uStack_28 = *(undefined4 *)(iVar7 + 0x68);
      uStack_24 = *(undefined4 *)(iVar7 + 0x6c);
      piVar1 = (int *)(this + 0xfc);
      uStack_20 = *(undefined4 *)(iVar7 + 0x70);
      uStack_1c = *(undefined4 *)(iVar7 + 0x74);
      uStack_18 = *(undefined4 *)(iVar7 + 0x78);
      uStack_14 = *(undefined4 *)(iVar7 + 0x7c);
      if (*(int *)(this + 0xfc) != 0) {
        FUN_004df600(); // Free previous effect
      }
      FUN_004eacb0("zoomblur"); // Get zoomblur effect
      FUN_004df420(&iStack_a4,&uStack_a0,&uStack_50,0xffffffff,4,0,0xffffffff,0); // Create zoomblur effect
      if (*piVar1 != 0) {
        *(undefined4 *)(*piVar1 + 8) = 0;
        *piVar1 = 0;
      }
      *piVar1 = iStack_a4;
      if (iStack_a4 != 0) {
        *(int **)(iStack_a4 + 8) = piVar1;
      }
    }
    else {
      FUN_00424dc0(0,*(undefined4 *)(this + 0x68),0,1,1); // Play different hit reaction
    }
    if (*(int *)(this + 0x6c) != 0) { // If there's a weapon
      FUN_00956580(); // Update weapon state
      FUN_00424ea0(0,*(undefined4 *)(this + 0x6c),0); // Play weapon animation
    }
  }
  return 1;
}