// FUNC_NAME: TimeManager::interpolateKeyframe
undefined4 * __thiscall TimeManager::interpolateKeyframe(int this, undefined4 *outResult, undefined4 *keyframes, uint *outIndicesOrT)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  float fVar11;
  undefined **local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_14;
  
  uVar7 = FUN_0082c770(keyframes);
  if (uVar7 == 0xffffffff) {
    if (outIndicesOrT != (uint *)0x0) {
      *outIndicesOrT = 0xffffffff;
      outIndicesOrT[1] = 0xffffffff;
      outIndicesOrT[2] = 0;
    }
    FUN_008334a0();  // Reset/clear something
    local_60 = &PTR_LAB_00d73738;  // Default vtable pointer
    local_14 = _DAT_00d5780c;  // Some global time value or zero
  }
  else {
    *(uint *)(this + 4) = uVar7;  // Store current frame index
    fVar5 = _DAT_00d5780c;  // Global time/zero
    if (uVar7 < *(int *)(this + 0xc) - 1U) {  // Check if not at last frame
      uVar9 = uVar7 + 1;
    }
    else {
      uVar9 = 0;  // Wrap around to first frame
    }
    iVar3 = *(int *)(*(int *)(this + 8) + uVar7 * 4);  // Get current frame data
    iVar4 = *(int *)(*(int *)(this + 8) + uVar9 * 4);  // Get next frame data
    
    // Calculate total time in seconds from frame start times
    // Frame seems to store hours, minutes, seconds as fields at +0x10, +0x14, +0x18
    uVar1 = *(int *)(iVar3 + 0x18) + (*(int *)(iVar3 + 0x14) + *(int *)(iVar3 + 0x10) * 0x3c) * 0x3c;
    
    if (uVar9 == 0) {
      uVar2 = keyframes[5] + (keyframes[4] + keyframes[3] * 0x3c) * 0x3c;  // Target time from keyframes array
      iVar8 = *(int *)(iVar4 + 0x18) +
              (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c + (0x15180 - uVar1);  // 0x15180 = 86400 seconds (1 day)
      if (uVar2 < uVar1) {
        iVar10 = uVar2 + (0x15180 - uVar1);
      }
      else {
        iVar10 = uVar2 - uVar1;
      }
    }
    else {
      iVar10 = ((keyframes[4] + keyframes[3] * 0x3c) * 0x3c - uVar1) + keyframes[5];
      iVar8 = (*(int *)(iVar4 + 0x18) +
              (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c) - uVar1;
    }
    
    if (iVar8 == 0) {  // Edge case: no time difference between frames
      if (outIndicesOrT != (uint *)0x0) {
        *outIndicesOrT = uVar7;
        outIndicesOrT[1] = uVar9;
        outIndicesOrT[2] = (uint)fVar5;
      }
      FUN_0081f9f0(iVar4);  // Use next frame directly
      local_14 = *(float *)(iVar4 + 0x4c);  // Some value from next frame (+0x4C)
      local_60 = &PTR_LAB_00d73738;
    }
    else {
      fVar5 = (float)iVar10;
      if (iVar10 < 0) {
        fVar5 = fVar5 + DAT_00e44578;  // Handle negative wrap (maybe 86400.0f?)
      }
      fVar6 = (float)iVar8;
      if (iVar8 < 0) {
        fVar6 = fVar6 + DAT_00e44578;
      }
      if (outIndicesOrT != (uint *)0x0) {
        fVar11 = _DAT_00d5780c - fVar5 / fVar6;  // t = 1.0 - (elapsed / total) ?
        *outIndicesOrT = uVar7;
        outIndicesOrT[1] = uVar9;
        outIndicesOrT[2] = (uint)fVar11;
      }
      FUN_0082bb60(&local_60, fVar5 / fVar6, iVar3, iVar4);  // Interpolation function
    }
    if (&local_5c != keyframes) {  // Copy keyframes into local buffer
      local_5c = *keyframes;
      local_54 = keyframes[2];
      local_58 = keyframes[1];
      local_50 = keyframes[3];
      local_48 = keyframes[5];
      local_4c = keyframes[4];
    }
  }
  FUN_0081f9f0(&local_60);  // Finalize/apply interpolation
  *outResult = &PTR_LAB_00d73738;  // Set result vtable
  outResult[0x13] = local_14;  // Store interpolated value at +0x4C
  return outResult;
}