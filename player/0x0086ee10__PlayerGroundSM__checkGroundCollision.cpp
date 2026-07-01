// FUNC_NAME: PlayerGroundSM::checkGroundCollision
uint __thiscall PlayerGroundSM::checkGroundCollision(int this, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 local_10;
  float local_c;
  float local_8;
  float local_4;
  
  // Check if ground collision is already resolved (bit 1 of flags at +0x6c)
  if ((*(uint *)(this + 0x6c) >> 1 & 1) != 0) {
    return (*(uint *)(this + 0x6c) >> 9) << 8;
  }
  
  // Check if player is in a valid state for ground collision (FUN_0086e440 likely checks player state)
  cVar1 = FUN_0086e440(1, 0);
  if (((cVar1 != '\0') && (iVar2 = *(int *)(*(int *)(this + 0x50) + 0x70), iVar2 != 0)) &&
     (iVar2 != 0x48)) {
    // Get current world position (likely from camera or player transform)
    local_10 = FUN_0043b490();
    // Get player transform matrix
    iVar2 = FUN_00471610();
    // Perform ground collision raycast (FUN_008720d0 likely does raycast from position downwards)
    cVar1 = FUN_008720d0(iVar2 + 0x30, &local_10, 0);
    *(undefined4 *)(this + 0x7c) = param_2;
    if (cVar1 != '\0') {
      // Collision detected - store hit point position
      iVar2 = FUN_00471610();
      *(undefined8 *)(this + 0x70) = *(undefined8 *)(iVar2 + 0x30);
      *(undefined4 *)(this + 0x78) = *(undefined4 *)(iVar2 + 0x38);
      // Clear bit 4 (0x10) and set bit 3 (0x8) in flags
      *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) & 0xffffffef;
      *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 8;
      return *(uint *)(this + 0x6c) >> 3 & 1;
    }
    // No collision detected - check if we were previously on ground
    if ((*(uint *)(this + 0x6c) >> 3 & 1) != 0) {
      // Get current player position
      pfVar3 = (float *)FUN_0086d5a0();
      local_c = *(float *)(this + 0x70) - *pfVar3;
      local_8 = *(float *)(this + 0x74) - pfVar3[1];
      local_4 = *(float *)(this + 0x78) - pfVar3[2];
      // Get player transform matrices for dot product check
      iVar2 = FUN_00471610();
      iVar4 = FUN_00471610();
      iVar5 = FUN_00471610();
      // Check if we're falling (dot product with gravity direction)
      if ((_DAT_00d577a0 <
           *(float *)(iVar4 + 0x24) * local_8 + *(float *)(iVar2 + 0x20) * local_c +
           *(float *)(iVar5 + 0x28) * local_4) &&
         // Try to snap to ground (raycast from stored position downwards)
         (cVar1 = FUN_008720d0(this + 0x70, &local_10, 1), cVar1 != '\0')) {
        // Ground snap successful - set bit 4 (0x10) indicating snapped to ground
        *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) | 0x10;
        return *(uint *)(this + 0x6c) >> 3 & 1;
      }
      // Clear ground flags (bits 3 and 5)
      *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) & 0xffffffe7;
    }
  }
  return *(uint *)(this + 0x6c) >> 3 & 1;
}