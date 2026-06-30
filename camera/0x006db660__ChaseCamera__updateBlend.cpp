// FUNC_NAME: ChaseCamera::updateBlend
void __thiscall ChaseCamera::updateBlend(int this, float dt, float *inPose, float *outPose)
{
  float fVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int *piVar6;
  float *pfVar7;
  float *pfVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float local_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_c4;
  float local_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  float local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float local_90 [8];
  undefined1 auStack_70 [4];
  undefined1 auStack_6c [4];
  undefined1 auStack_68 [24];
  undefined1 local_50 [16];
  float local_40;
  float fStack_3c;
  float fStack_38;
  float local_30;
  float fStack_2c;
  float fStack_28;
  
  // Check if blending is disabled (global flag)
  if (DAT_0112a8f8 == '\0') {
    // No blending: copy input directly to output
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *outPose = *inPose;
      inPose = inPose + 1;
      outPose = outPose + 1;
    }
    return;
  }
  
  iVar5 = *(int *)(this + 0x1a4); // +0x1a4: blendState (0=idle, 1=blending, 2=finished, 3=reverse?)
  if (((iVar5 == 3) || (iVar5 == 2)) &&
     (fVar10 = dt + *(float *)(this + 0x1b0), *(float *)(this + 0x1b0) = fVar10,
     *(float *)(this + 0x1ac) - fVar10 < 0.0)) { // +0x1ac: blendDuration, +0x1b0: blendElapsed
    if (iVar5 == 2) {
      *(undefined4 *)(this + 0x1a4) = 0; // Reset to idle
      *(undefined1 *)(this + 8) = 1; // +0x08: some flag (maybe "dirty" or "updated")
      return;
    }
    *(undefined4 *)(this + 0x1a4) = 1; // Transition to blending
  }
  
  FUN_006db5d0(dt); // Probably update some time-related state
  FUN_0056b8a0(outPose[9], outPose[8], outPose[10], local_50); // Extract rotation from pose
  
  fVar10 = *(float *)(this + 0x6c); // +0x6c: some speed/scale factor
  fVar1 = *(float *)(this + 0x60); // +0x60: another speed/scale factor
  
  // Compute interpolated positions
  local_c0 = *inPose + fVar10 * local_40;
  fStack_bc = inPose[1] + fVar10 * fStack_3c;
  fStack_b8 = inPose[2] + fVar10 * fStack_38;
  local_e0 = *inPose + fVar1 * local_30;
  fStack_dc = inPose[1] + fVar1 * fStack_2c;
  fStack_d8 = inPose[2] + fVar1 * fStack_28;
  
  // Handle collision/obstacle avoidance
  if ((*(int *)(this + 0xe8) != 0) && (*(int *)(this + 0xe8) != 0x48)) {
    if (*(int *)(this + 0xe8) == 0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)(*(int *)(this + 0xe8) + -0x48);
    }
    (**(code **)(*piVar6 + 0xa4))(&local_b0, this + 0xf0); // Get collision target position
    fVar4 = fStack_a8;
    fVar3 = fStack_ac;
    fVar1 = local_b0;
    fVar10 = _DAT_00d5780c;
    fStack_a0 = local_b0;
    fStack_9c = fStack_ac;
    fStack_98 = fStack_a8;
    fStack_94 = _DAT_00d5780c;
    local_b0 = local_b0 - *(float *)(this + 400); // +0x190: camera position X
    fStack_ac = fStack_ac - *(float *)(this + 0x194); // +0x194: camera position Y
    fStack_a8 = fStack_a8 - *(float *)(this + 0x198); // +0x198: camera position Z
    fVar11 = SQRT(fStack_ac * fStack_ac + fStack_a8 * fStack_a8 + local_b0 * local_b0);
    if (DAT_00d58cbc < fVar11) {
      fVar11 = DAT_00d58cbc / fVar11;
      local_b0 = fVar11 * local_b0;
      fStack_ac = fVar11 * fStack_ac;
      fStack_a8 = fVar11 * fStack_a8;
    }
    if (*(char *)(this + 0x1a0) == '\0') { // +0x1a0: collisionActive flag
      fVar11 = *(float *)(this + 0x70); // +0x70: collision push strength
      local_e0 = fVar11 * local_b0 + local_e0;
      fStack_dc = fVar11 * fStack_ac + fStack_dc;
      fStack_d8 = fVar11 * fStack_a8 + fStack_d8;
    }
    *(float *)(this + 400) = fVar1; // Update stored camera position
    *(float *)(this + 0x194) = fVar3;
    *(float *)(this + 0x198) = fVar4;
    *(float *)(this + 0x19c) = fVar10;
  }
  
  cVar2 = *(char *)(this + 0x1a0);
  pfVar7 = outPose;
  pfVar8 = local_90;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar8 = pfVar8 + 1;
  }
  
  if (cVar2 == '\0') {
    // No collision: apply time-based interpolation
    FUN_006daac0(&local_c0, dt);
    FUN_006daac0(local_90, dt);
    FUN_006daac0(&local_e0, dt);
  }
  else {
    // Collision active: store intermediate results
    *(float *)(this + 0x110) = local_90[0];
    *(float *)(this + 0x114) = local_90[1];
    *(float *)(this + 0x118) = local_90[2];
    *(float *)(this + 0x11c) = local_90[3];
    *(float *)(this + 0x170) = local_c0;
    *(float *)(this + 0x174) = fStack_bc;
    *(float *)(this + 0x178) = fStack_b8;
    *(undefined4 *)(this + 0x17c) = uStack_b4;
    *(float *)(this + 0x140) = local_e0;
    *(float *)(this + 0x144) = fStack_dc;
    *(float *)(this + 0x148) = fStack_d8;
    *(undefined4 *)(this + 0x14c) = uStack_d4;
    *(undefined1 *)(this + 0x1a0) = 0; // Clear collision flag
  }
  
  // Compute direction vectors
  local_c0 = local_c0 - local_90[0];
  fStack_bc = fStack_bc - local_90[1];
  fStack_b8 = fStack_b8 - local_90[2];
  local_e0 = local_e0 - local_90[0];
  fStack_dc = fStack_dc - local_90[1];
  fStack_d8 = fStack_d8 - local_90[2];
  
  // Normalize vectors
  fVar10 = fStack_d8 * fStack_d8 + fStack_dc * fStack_dc + local_e0 * local_e0;
  if (fVar10 <= DAT_00d5f2b4) {
    fVar10 = 0.0;
  }
  else {
    fVar10 = _DAT_00d5780c / SQRT(fVar10);
  }
  local_e0 = local_e0 * fVar10;
  fStack_dc = fStack_dc * fVar10;
  fStack_d8 = fStack_d8 * fVar10;
  
  fVar10 = fStack_b8 * fStack_b8 + fStack_bc * fStack_bc + local_c0 * local_c0;
  if (fVar10 <= DAT_00d5f2b4) {
    fVar10 = 0.0;
  }
  else {
    fVar10 = _DAT_00d5780c / SQRT(fVar10);
  }
  local_c0 = local_c0 * fVar10;
  fStack_bc = fStack_bc * fVar10;
  fStack_b8 = fStack_b8 * fVar10;
  
  // Compute rotation from direction vectors
  FUN_0056c6b0(&local_e0, &local_c0, local_50);
  FUN_0056c180(local_50, auStack_6c, auStack_70, auStack_68);
  
  if (*(int *)(this + 0x1a4) == 1) {
    // Blend complete: copy stored pose to output
    pfVar7 = local_90;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *outPose = *pfVar7;
      pfVar7 = pfVar7 + 1;
      outPose = outPose + 1;
    }
    return;
  }
  
  // Compute blend factor
  fVar9 = (float10)FUN_004a2210(*(float *)(this + 0x1b0) / *(float *)(this + 0x1ac), 1);
  fStack_c4 = (float)fVar9;
  if (*(int *)(this + 0x1a4) == 3) {
    fStack_c4 = _DAT_00d5780c - fStack_c4; // Reverse blend
  }
  
  // Interpolate rotation
  FUN_004a2c80(outPose + 8, fStack_c4, auStack_70, inPose + 8);
  
  // Interpolate position
  fVar1 = inPose[1];
  fVar3 = inPose[2];
  fVar4 = inPose[3];
  fVar10 = outPose[3];
  *outPose = (*inPose - local_90[0]) * fStack_c4 + local_90[0];
  outPose[1] = (fVar1 - local_90[1]) * fStack_c4 + local_90[1];
  outPose[2] = (fVar3 - local_90[2]) * fStack_c4 + local_90[2];
  outPose[3] = (fVar4 - local_90[3]) * fStack_c4 + local_90[3];
  outPose[3] = fVar10;
  return;
}