// FUNC_NAME: PlayerCCTVariables::updateMovement
void __thiscall PlayerCCTVariables::updateMovement(int *this, float deltaTime)
{
  uint *puVar1;
  int iVar2;
  float *pfVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  char cVar7;
  int unaff_FS_OFFSET;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined1 local_50 [48];
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  // +0x4 = pointer to some object (likely player state)
  // +0x8 = pointer to another object (likely character controller)
  // +0x10 = timer
  // +0x14 = some flag
  // +0x1c = vtable offset for update
  
  fVar11 = *(float *)(this[1] + 0x8c); // Get some value from object at +0x4
  iVar2 = *(int *)(this[1] + 0x10) + 0x30 + *(short *)((int)this + 0xe) * 0x24; // Calculate index into array
  fVar8 = (fVar11 - *(float *)(iVar2 + 0x18)) * *(float *)(iVar2 + 0x14); // Compute weighted difference
  if (0.0 < fVar8) {
    if (DAT_00e2b1a4 <= fVar8) {
      fVar8 = DAT_00e2b1a4; // Clamp to max
    }
  }
  else {
    fVar8 = 0.0; // Clamp to zero
  }
  fVar11 = (fVar11 - *(float *)(iVar2 + 0x20)) * *(float *)(iVar2 + 0x1c); // Another weighted difference
  if (0.0 < fVar11) {
    if (DAT_00e2b1a4 <= fVar11) {
      fVar11 = DAT_00e2b1a4; // Clamp to max
    }
  }
  else {
    fVar11 = 0.0; // Clamp to zero
  }
  if (fVar11 * fVar8 <= 0.0) {
    if (this[10] != 0) {
      FUN_004ff430(); // Stop movement
      return;
    }
  }
  else if ((this[10] != 0) || (FUN_004ff0f0(), this[10] != 0)) {
    local_60 = 0.0;
    piVar4 = *(int **)(unaff_FS_OFFSET + 0x2c); // Get thread-local storage
    if ((0.0 < (float)this[0x10]) &&
       (fVar9 = (float)this[0x10] - deltaTime, this[0x10] = (int)fVar9, fVar9 <= 0.0)) {
      puVar1 = (uint *)(*(int *)(*piVar4 + 8) + this[4]); // Set flag
      *puVar1 = *puVar1 | 1;
    }
    uVar5 = *(uint *)(*(int *)(this[1] + 0x10) + 0x14); // Get flags from object
    if (((uVar5 & 0x40) == 0) && ((uVar5 & 0x4000) == 0)) {
      pfVar3 = (float *)(this[4] + 0x80 + *(int *)(*piVar4 + 8)); // Get position from some array
      local_20 = *pfVar3;
      fStack_1c = pfVar3[1];
      fStack_18 = pfVar3[2];
      fStack_14 = pfVar3[3];
      iVar2 = this[9]; // Get some object
      if ((*(uint *)(iVar2 + 0x10) & 6) == 0) {
        local_20 = *(float *)(iVar2 + 0x1c) + local_20;
        fStack_1c = *(float *)(iVar2 + 0x20) + fStack_1c;
        fStack_18 = *(float *)(iVar2 + 0x24) + fStack_18;
      }
      if (*(char *)(iVar2 + 0x6c) == '\0') {
        FUN_004e9440(this[10], &local_20); // Apply movement
      }
      else {
        if ((*(uint *)(iVar2 + 0x10) & 0x2000) == 0) {
          FUN_0048efa0(this[4] + *(int *)(*piVar4 + 8) + 0x50, local_50); // Get rotation
        }
        else {
          FUN_004fef50(); // Get rotation alternative
        }
        FUN_004e9400(); // Apply rotation
        local_60 = 0.0;
      }
    }
    if ((local_60 < *(float *)(this[9] + 0x14)) &&
       (*(float *)(this[9] + 0x14) < (float)this[0xd])) {
      (**(code **)(*this + 0x1c))(); // Call virtual function
      local_60 = 0.0;
    }
    iVar2 = *piVar4;
    if ((*(byte *)(this[4] + *(int *)(iVar2 + 8)) & 1) != 0) {
      local_5c = local_60;
      local_58 = local_60;
      local_54 = local_60;
      FUN_004e94a0(&local_60, 0); // Apply zero force
      return;
    }
    iVar6 = this[9];
    fVar9 = *(float *)(iVar6 + 0x38);
    fVar12 = (float)this[0xd] * *(float *)(iVar6 + 0x2c) + *(float *)(iVar6 + 0x28);
    fVar10 = (float)this[0xd] * *(float *)(iVar6 + 0x34) + *(float *)(iVar6 + 0x30);
    if (fVar12 < fVar10) {
      fVar10 = fVar12;
    }
    if ((fVar10 < fVar9) || (fVar9 = *(float *)(iVar6 + 0x3c), *(float *)(iVar6 + 0x3c) < fVar10)) {
      fVar10 = fVar9;
    }
    if ((this[0xb] != 1) || (this[0xc] != 0)) {
      fVar9 = fVar10;
      FUN_004ebc00(this[1], 0); // Some update
      fVar10 = fVar9 * fVar10;
      local_60 = 0.0;
    }
    fVar10 = fVar10 * fVar11 * fVar8; // Combine weighted values
    if (local_60 < (float)this[0x10]) {
      fVar10 = ((float)this[0x10] / *(float *)(this[9] + 0x78)) * fVar10; // Scale by timer
    }
    uVar5 = this[0xf];
    if ((uVar5 & 6) != 0) {
      if ((uVar5 & 2) == 0) {
        if ((uVar5 & 1) != 0) {
          this[0xf] = uVar5 & 0xfffffffe;
          FUN_004e9600(); // Clear flag
        }
        this[0xf] = this[0xf] & 0xfffffffb;
      }
      else if (fVar10 <= DAT_00e2dd1c) {
        if ((uVar5 & 1) != 0) {
          this[0xf] = uVar5 & 0xfffffffe;
          FUN_004e9600(); // Clear flag
        }
      }
      else if (((uVar5 & 1) == 0) && (cVar7 = FUN_004e95e0(), cVar7 != '\0')) {
        this[0xf] = this[0xf] | 1; // Set flag
      }
    }
    iVar6 = this[9];
    local_60 = fVar10 * *(float *)(iVar6 + 0x44); // Apply direction
    local_5c = fVar10 * *(float *)(iVar6 + 0x48);
    local_58 = fVar10 * *(float *)(iVar6 + 0x4c);
    if ((*(uint *)(this[4] + *(int *)(iVar2 + 8)) & 0x80000) != 0) {
      iVar2 = this[1];
      local_60 = *(float *)(iVar2 + 0xa0) * local_60; // Scale by object's scale
      local_5c = *(float *)(iVar2 + 0xa4) * local_5c;
      local_58 = *(float *)(iVar2 + 0xa8) * local_58;
    }
    local_54 = DAT_00e2b1a4; // Set w component to 1.0
    FUN_004e94a0(&local_60, *(undefined4 *)(iVar6 + 0x40)); // Apply force
    FUN_004aa7b0(*(undefined4 *)(this[1] + 0x84)); // Update some system
    this[0xd] = (int)((float)this[0xd] + deltaTime); // Accumulate time
  }
  return;
}