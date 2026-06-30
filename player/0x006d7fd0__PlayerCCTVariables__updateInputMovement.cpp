// FUNC_NAME: PlayerCCTVariables::updateInputMovement
void __thiscall PlayerCCTVariables::updateInputMovement(int this, float inputX, float inputY)
{
  int *piVar1;
  undefined8 uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  int iVar7;
  undefined8 *puVar8;
  int iVar9;
  float10 fVar10;
  float10 fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  uint uVar16;
  float local_f0;
  float local_ec;
  float local_e8;
  undefined4 local_e4;
  float local_d4;
  undefined8 local_d0;
  float local_c8;
  undefined4 local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  undefined4 local_b4;
  float local_b0;
  float fStack_ac;
  float local_a8;
  undefined4 local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float fStack_90;
  float local_8c;
  undefined8 local_88;
  float local_80;
  undefined8 local_7c;
  float local_74;
  undefined8 local_70;
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_50;
  undefined4 uStack_4c;
  float local_48;
  undefined4 local_44;
  undefined8 local_40;
  float local_38;
  undefined4 local_34;
  undefined8 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_14;
  
  // Apply speed multiplier if debug flag is set
  if (DAT_0112a7a5 != '\0') {
    inputX = inputX * DAT_00d5ccf8;
  }
  if (DAT_0112a7a4 != '\0') {
    inputY = inputY * DAT_00d5ccf8;
  }
  
  // Get the game manager instance
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    local_d4 = 0.0;
  }
  else {
    local_d4 = (float)(**(int **)(DAT_012233a0 + 4) + -0x1f30);
  }
  
  // Get current player controller
  if (*(int *)((int)local_d4 + 0x31a8) == 0) {
    iVar9 = 0;
  }
  else {
    iVar9 = *(int *)((int)local_d4 + 0x31a8) + -0x48;
  }
  
  piVar1 = (int *)(this + 0x260); // +0x260: pointer to some object
  if (*(int *)(this + 0x260) == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = *(int *)(this + 0x260) + -0x48;
  }
  
  // Update pointer if needed
  if (iVar7 != iVar9) {
    if (iVar9 == 0) {
      iVar9 = 0;
    }
    else {
      iVar9 = iVar9 + 0x48;
    }
    if (*piVar1 != iVar9) {
      if (*piVar1 != 0) {
        FUN_004daf90(piVar1);
      }
      *piVar1 = iVar9;
      if (iVar9 != 0) {
        *(undefined4 *)(this + 0x264) = *(undefined4 *)(iVar9 + 4);
        *(int **)(iVar9 + 4) = piVar1;
      }
    }
    *(undefined4 *)(this + 0x25c) = 0; // +0x25c: input accumulator?
    *(undefined4 *)(this + 600) = 0;   // +0x258: another accumulator
  }
  
  // Process input if we have a valid object
  if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
    puVar8 = (undefined8 *)FUN_00424fb0(&local_d0,0);
    local_7c = *puVar8;
    local_74 = *(float *)(puVar8 + 1);
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = _DAT_00d5780c;
    
    puVar8 = (undefined8 *)FUN_00425060(&local_b0,0);
    local_c8 = *(float *)(puVar8 + 1);
    uVar2 = *puVar8;
    local_d0._0_4_ = (float)uVar2;
    local_d0._4_4_ = (float)((ulonglong)uVar2 >> 0x20);
    uVar4 = local_d0._4_4_;
    uVar5 = (float)local_d0;
    local_d0 = uVar2;
    FUN_0056b8a0(uVar4,uVar5,local_c8,&local_50);
    
    // Vector operations
    local_d0 = local_40;
    local_70 = local_30;
    local_b0 = local_50;
    local_8c = local_48;
    fStack_ac = (float)uStack_4c;
    local_c8 = local_38;
    local_a8 = local_48;
    local_68 = local_28;
    local_a4 = 0;
    FUN_0056afa0(&local_b0,&local_b0);
    
    _local_94 = CONCAT44(fStack_ac,local_b0);
    local_8c = local_a8;
    local_f0 = (float)local_d0;
    local_ec = local_d0._4_4_;
    local_e8 = local_c8;
    local_e4 = 0;
    FUN_0056afa0(&local_f0,&local_f0);
    
    local_d0._0_4_ = (float)local_70;
    local_d0._4_4_ = (float)local_70._4_4_;
    local_c8 = (float)local_68;
    local_c4 = 0;
    FUN_0056afa0(&local_d0,&local_d0);
    local_70 = CONCAT44(local_d0._4_4_,(float)local_d0);
    local_68 = local_c8;
    
    // Check if we have movement input
    if (*piVar1 == 0) {
      iVar9 = 0;
    }
    else {
      iVar9 = *piVar1 + -0x48;
    }
    cVar6 = FUN_006c8620(&local_a0,iVar9,4);
    if (cVar6 != '\0') {
      // Get camera info
      iVar9 = FUN_00471610();
      iVar7 = FUN_00471610();
      fVar12 = *(float *)(iVar7 + 0x30) - *(float *)(iVar9 + 0x30);
      fVar13 = *(float *)(iVar7 + 0x34) - *(float *)(iVar9 + 0x34);
      fVar15 = *(float *)(iVar7 + 0x38) - *(float *)(iVar9 + 0x38);
      
      // Check distance to target
      bVar3 = SQRT(fVar15 * fVar15 + fVar13 * fVar13 + fVar12 * fVar12) < DAT_00e511d4;
      
      local_64 = DAT_00e448d4;
      local_d4 = DAT_00d5f544;
      cVar6 = FUN_00410eb0(); // Check if in combat mode
      uVar16 = DAT_00e44680;
      fVar12 = local_64;
      if (cVar6 != '\0') {
        local_d4 = DAT_00e44828; // Combat movement speed
        fVar12 = DAT_00e44718;   // Combat strafe speed
      }
      
      // Apply horizontal input (strafe)
      if ((float)((uint)inputY & DAT_00e44680) <= 0.0) {
        if (0.0 < (float)(DAT_0112a8f0 & DAT_00e44680)) {
          fVar10 = (float10)FUN_006c89b0(*(undefined4 *)(this + 600),0,DAT_0112a8f0);
          *(float *)(this + 600) = (float)fVar10;
          uVar16 = DAT_00e44680;
        }
      }
      else {
        *(float *)(this + 600) = fVar12 * inputY + *(float *)(this + 600);
      }
      
      // Apply vertical input (forward/backward)
      if ((float)((uint)inputX & uVar16) <= 0.0) {
        if (0.0 < (float)(DAT_0112a8ec & uVar16)) {
          fVar10 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0x25c),0,DAT_0112a8ec);
          *(float *)(this + 0x25c) = (float)fVar10;
        }
      }
      else {
        *(float *)(this + 0x25c) = local_d4 * inputX + *(float *)(this + 0x25c);
      }
      
      // Snap to target if close enough
      if (bVar3) {
        fVar10 = (float10)FUN_006c89b0(*(undefined4 *)(this + 600),0,_DAT_00e511d0);
        *(float *)(this + 600) = (float)fVar10;
      }
      
      // Clamp vertical movement
      fVar15 = DAT_00e511c4; // Max forward speed?
      fVar13 = DAT_00e44564; // Min backward speed?
      fVar12 = *(float *)(this + 600);
      fVar14 = DAT_00e511cc;
      if ((DAT_00e511cc < fVar12) && (fVar14 = DAT_00e511c8, fVar12 < DAT_00e511c8)) {
        fVar14 = fVar12;
      }
      *(float *)(this + 600) = fVar14;
      
      // Clamp horizontal movement
      fVar12 = *(float *)(this + 0x25c);
      fVar13 = fVar13 - fVar15;
      if ((fVar13 < fVar12) && (fVar13 = fVar12, fVar15 <= fVar12)) {
        fVar13 = fVar15;
      }
      *(float *)(this + 0x25c) = fVar13;
      
      // Apply movement to position
      local_c0 = local_94;
      local_bc = fStack_90;
      local_b8 = local_8c;
      local_b4 = 0;
      FUN_0056afa0(&local_c0,&local_c0);
      
      fVar12 = *(float *)(this + 0x25c);
      local_a0 = local_a0 + local_c0 * fVar12;
      local_9c = local_9c + local_bc * fVar12;
      local_98 = local_98 + local_b8 * fVar12;
      
      local_c0 = local_f0;
      local_bc = local_ec;
      local_b8 = local_e8;
      local_b4 = 0;
      FUN_0056afa0(&local_c0,&local_c0);
      
      fVar12 = *(float *)(this + 600);
      local_a0 = local_a0 + local_c0 * fVar12;
      local_9c = local_9c + local_bc * fVar12;
      local_f0 = local_a0 - (float)local_7c;
      local_98 = local_98 + local_b8 * fVar12;
      local_ec = local_9c - local_7c._4_4_;
      local_e8 = local_98 - local_74;
      local_e4 = 0;
      
      // Calculate movement direction
      local_b0 = local_f0;
      fStack_ac = local_ec;
      local_a8 = local_e8;
      FUN_0056afa0(&local_f0,&local_f0);
      
      local_b0 = local_f0;
      fStack_ac = local_ec;
      local_a8 = local_e8;
      local_80 = local_e8;
      local_88 = (ulonglong)(uint)local_f0;
      local_ec = 0.0;
      local_e4 = 0;
      FUN_0056afa0(&local_f0,&local_f0);
      
      local_88 = CONCAT44(local_ec,local_f0);
      local_80 = local_e8;
      
      // Calculate rotation based on input
      fVar10 = (float10)FUN_004a10f0(this + 0x200,&local_88,&DAT_00d5f478);
      *(float *)(this + 0x234) = (float)(fVar10 * (float10)DAT_00e44748 * (float10)DAT_00d5ccf8);
      
      fVar11 = (float10)FUN_004a10f0(&local_88,&local_b0,&local_94);
      fVar10 = (float10)DAT_00e44748;
      *(float *)(this + 0x22c) = (float)(fVar11 * fVar10);
      
      // Snap rotation if needed
      if (bVar3) {
        fVar10 = (float10)FUN_006c89b0((float)(fVar11 * fVar10),0,_DAT_00e511d0);
        *(float *)(this + 0x22c) = (float)fVar10;
      }
      
      // Calculate facing direction relative to target
      iVar9 = FUN_004262f0(0);
      FUN_00424fb0(&local_7c,0);
      local_f0 = *(float *)(DAT_01129944 + 0x108);
      local_ec = *(float *)(DAT_01129944 + 0x10c);
      local_e8 = *(float *)(DAT_01129944 + 0x110);
      local_e4 = _DAT_00d5780c;
      FUN_0056b420(iVar9 + 0x40,&local_f0,&local_60);
      
      local_c0 = local_60 - (float)local_7c;
      local_bc = local_5c - local_7c._4_4_;
      local_c8 = local_58 - local_74;
      local_d0 = CONCAT44(local_bc,local_c0);
      local_b4 = 0;
      local_b8 = local_c8;
      
      fVar10 = (float10)FUN_0056afa0(&local_c0,&local_c0);
      local_d0 = CONCAT44(local_bc,local_c0);
      local_c8 = local_b8;
      
      // Adjust rotation based on facing direction
      if ((float10)0 < fVar10) {
        fVar10 = (float10)FUN_004a10f0(&local_70,&local_d0,&local_94);
        *(float *)(this + 0x22c) =
             (float)((float10)*(float *)(this + 0x22c) - fVar10 * (float10)DAT_00e44748);
      }
    }
  }
  return;
}