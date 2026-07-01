// FUNC_NAME: Player::tryThrowProjectile
// Function at 0x007c0cd0: Attempts to throw a projectile (e.g., grenade/molotov) from the player's position toward a target.
// Returns 1 if throw was initiated, 0 otherwise.
// param_1 = this (Player object)
// param_2 = unknown (likely a context/state pointer)
// param_3 = output struct for throw trajectory data (size 0x20 bytes)
undefined1 Player::tryThrowProjectile(int this, undefined4 param_2, undefined8 *param_3)
{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined1 result; // local_1e1
  float throwStartPos[3]; // local_1dc, fStack_1d8, local_1d4
  float local_1cc;
  float fStack_1c8;
  float local_1c4;
  float local_1c0;
  float fStack_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  undefined1 local_190[96];
  int local_130;
  undefined1 local_120[96];
  int local_c0;
  undefined1 local_b0[80];
  undefined1 local_60[92];
  
  result = 0;
  // Check if player is not in a specific state (bit 0 of +0x8e4)
  if ((*(byte *)(this + 0x8e4) & 1) == 0) {
    // Get some global manager/state
    iVar3 = FUN_0043b870(DAT_01130fa0);
    // Get player's current vehicle pointer (+0xff0)
    iVar4 = *(int *)(this + 0xff0);
    // Check: has vehicle, vehicle is valid, manager exists, vehicle not destroyed, not in certain state
    if (((((iVar4 != 0) && (iVar4 + -0x48 != 0)) && (iVar3 != 0)) &&
        ((cVar2 = FUN_009a9b40(iVar4 + -0x48), cVar2 == '\0' && (*(char *)(iVar4 + 0x1b44) == '\0'))
        )) && (*(char *)(iVar4 + 0xfb1) == '\0')) {
      // Get player's facing direction (+0x1f98, +0x1f9c)
      uVar1 = *(undefined4 *)(this + 0x1f98);
      local_1d0 = *(undefined4 *)(this + 0x1f9c);
      // Check for obstacles in the throw direction using raycasts
      iVar4 = FUN_00896b30(2, 0x20, uVar1, local_1d0, 2, 0); // Raycast type 2, flags 0x20
      iVar3 = FUN_00896b30(2, 0x40, uVar1, local_1d0, 2, 0); // Raycast type 2, flags 0x40
      if ((iVar4 == 0) && (iVar3 == 0)) {
        // If both failed, try with type 5
        iVar4 = FUN_00896b30(5, 0x20, uVar1, local_1d0, 2, 0);
        iVar3 = FUN_00896b30(5, 0x40, uVar1, local_1d0, 2, 0);
      }
      // Get current player position
      FUN_008970a0(&local_1cc); // Gets player position into local_1cc (x), fStack_1c8 (y), local_1c4 (z)
      
      if (iVar4 == 0) {
        // No hit with 0x20 flags, use 0x40 hit
        if (iVar3 == 0) {
          return 0; // No valid target found
        }
        // Calculate throw trajectory from hit point
        cVar2 = FUN_007e94f0(param_2, &local_1cc, iVar3 + 8, (undefined8 *)(iVar3 + 0x18), 0x4010000,
                             0x40, &local_1dc);
        if (cVar2 != '\0') {
          return 0;
        }
        // Fill output struct with throw data
        *param_3 = CONCAT44(fStack_1d8, local_1dc); // Start position
        *(float *)(param_3 + 1) = local_1d4; // Start position z
        *(undefined8 *)((int)param_3 + 0xc) = *(undefined8 *)(iVar3 + 0x18); // Target position
        *(undefined4 *)((int)param_3 + 0x14) = *(undefined4 *)(iVar3 + 0x20);
        *(undefined1 *)((int)param_3 + 0x1c) = 0; // Flag: 0 = right-handed throw
      }
      else {
        // Use 0x20 hit
        cVar2 = FUN_007e94f0(param_2, &local_1cc, iVar4 + 8, (undefined8 *)(iVar4 + 0x18), 0x4010000,
                             0x20, &local_1dc);
        if (cVar2 != '\0') {
          return 0;
        }
        *param_3 = CONCAT44(fStack_1d8, local_1dc);
        *(float *)(param_3 + 1) = local_1d4;
        *(undefined8 *)((int)param_3 + 0xc) = *(undefined8 *)(iVar4 + 0x18);
        *(undefined4 *)((int)param_3 + 0x14) = *(undefined4 *)(iVar4 + 0x20);
        *(undefined1 *)((int)param_3 + 0x1c) = 1; // Flag: 1 = left-handed throw
      }
      // Calculate distance to target
      *(float *)(param_3 + 3) =
           SQRT((local_1c4 - local_1d4) * (local_1c4 - local_1d4) +
                (fStack_1c8 - fStack_1d8) * (fStack_1c8 - fStack_1d8) +
                (local_1cc - local_1dc) * (local_1cc - local_1dc));
      // Apply throw speed modifier
      fVar5 = *(float *)(this + 0x1f98) + DAT_00d5ef88;
      result = 1;
      // Calculate throw arc/parabola
      FUN_008970a0(&local_1b4);
      local_1b0 = local_1b0 + DAT_00d5842c;
      local_19c = (DAT_00e44564 - *(float *)((int)param_3 + 0xc)) * fVar5 + local_1b4;
      local_194 = (DAT_00e44564 - *(float *)((int)param_3 + 0x14)) * fVar5 + local_1ac;
      local_198 = local_1b0;
      // Perform physics sweep for throw trajectory
      FUN_00542650(&local_1b4, &local_19c, 0x40202, 0x20000, 0, 0);
      FUN_0046d6a0(); // Update physics
      // Check if trajectory hits something
      FUN_00897310(local_b0, local_190, 0);
      if (local_130 == 0) {
        *(undefined1 *)((int)param_3 + 0x1d) = 0; // No obstacle
      }
      else {
        // Check what was hit
        iVar4 = FUN_00541470(*(undefined4 *)(local_130 + 0x1c));
        if (iVar4 != 9) { // Not a specific type (9 = maybe destructible?)
          iVar4 = FUN_00541470(*(undefined4 *)(local_130 + 0x1c));
          if (iVar4 == 0x12) { // Type 0x12 = maybe player? Cancel throw
            return 0;
          }
          *(undefined1 *)((int)param_3 + 0x1d) = 0;
          return 0;
        }
        *(undefined1 *)((int)param_3 + 0x1d) = 1; // Obstacle is destructible
      }
      // Calculate final throw arc with different parameters
      fVar5 = *(float *)(this + 0x1f98) + _DAT_00d5780c;
      local_1a4 = fStack_1c8 + DAT_00d5c454;
      local_1b8 = local_1c4;
      local_1a8 = (DAT_00e44564 - *(float *)((int)param_3 + 0xc)) * fVar5 + local_1cc;
      local_1a0 = (DAT_00e44564 - *(float *)((int)param_3 + 0x14)) * fVar5 + local_1c4;
      _local_1c0 = CONCAT44(local_1a4, local_1cc);
      // Perform second physics sweep
      FUN_00542650(&local_1c0, &local_1a8, 0x40120, 0x20000, 0, 0);
      FUN_0046d6a0();
      // Check for obstacles in final trajectory
      FUN_009e5ed0(local_60, local_120);
      if (local_c0 != 0) {
        result = 0;
        *(undefined1 *)((int)param_3 + 0x1d) = 0;
      }
    }
  }
  return result;
}