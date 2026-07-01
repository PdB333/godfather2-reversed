// FUNC_NAME: Player::attemptEnterVehicle
undefined1 __thiscall Player::attemptEnterVehicle(int this, char forceOrient, char skipLineOfSight) {
  float fVar1;
  char cVar2;
  int iVar3;
  undefined1 result;
  float10 fVar5;
  float10 fVar6;
  undefined4 local_e8;
  float fStack_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  float fStack_d8;
  undefined4 local_d4;
  undefined **local_d0;
  undefined4 local_cc;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a0;
  undefined4 local_80;
  int local_70;
  undefined1 local_60[92];

  result = 0;
  if (forceOrient != 0) {
    cVar2 = FUN_00481660(); // likely isPlayerBusy() or isAnimPlaying()
    if (cVar2 == 0) {
      cVar2 = FUN_00481640(); // maybe isCutsceneActive()
      if (cVar2 == 0) goto LAB_007ab9f4;
    }
    // Check if player is allowed to enter vehicles (flags at +0x2454, +0x2470 in game manager)
    if ((*(char *)(*(int *)(this + 0x58) + 0x2454) == 0) ||
       (*(char *)(*(int *)(this + 0x58) + 0x2470) == 0)) {
      return 0;
    }
  }
LAB_007ab9f4:
  iVar3 = *(int *)(this + 0x58); // pointer to game manager or player state
  // Check if vehicle slot is available (currentSlot == nextAvailableSlot or currentSlot == maxSlot)
  if ((*(int *)(iVar3 + 0x3d8) == *(int *)(iVar3 + 0x3dc)) ||
     (*(int *)(iVar3 + 0x3d8) == *(int *)(iVar3 + 0x3e0))) {
    if (forceOrient == 0) {
      // Check if currently in vehicle transition state and player is aiming
      if ((*(char *)(iVar3 + 0x1b8c) == 0x04) && ((*(uint *)(iVar3 + 0x8e0) >> 1 & 1) != 0)) {
        // Calculate entry direction and spawn point
        fVar5 = (float10)FUN_007f7d50(0,0); // getRandomNoise(0) or similar
        fVar6 = (float10)FUN_007f7d50(3,0); // getRandomNoise(3)
        iVar3 = FUN_00471610(); // getCameraOrPlayerTransform()
        fStack_d8 = (float)((ulonglong)*(undefined8 *)(iVar3 + 0x30) >> 0x20);
        fVar1 = fStack_d8;
        local_e0 = *(undefined4 *)(iVar3 + 0x38);
        local_dc = (undefined4)*(undefined8 *)(iVar3 + 0x30);
        // Apply noise and adjust entry point
        _local_dc = CONCAT44((float)fVar6 * _DAT_00d5c458 + fStack_d8, local_dc);
        _local_e8 = CONCAT44((float)fVar5 + DAT_00d58cbc + fVar1, local_dc);
        local_d4 = local_e0;
        FUN_00542650(&local_dc, &local_e8, 2, 0x10000, 0, 0); // projectToGround or findEntryPos
        local_70 = 0;
        local_ac = 0xffffffff;
        local_80 = 0;
        local_a0 = 0xffffffff;
        local_d0 = &PTR_FUN_00e32a8c; // likely a vtable for raycast query
        local_b0 = _DAT_00d5780c; // collision group mask
        local_cc = _DAT_00d5780c;
        FUN_009e5ed0(local_60, &local_d0); // perform raycast to check if entry point is accessible
        if ((local_70 == 0) || (skipLineOfSight != 0)) {
          FUN_007f6420(1); // lockPlayerControl or beginAction
          (**(code **)(**(int **)(this + 0x58) + 0x234))(0, 1); // setState(0, 1) - start vehicle entry
          FUN_0054e390(0); // enableInput(false)
          FUN_007ab2a0(0); // maybe setActionFlag(false)
          return 1;
        }
      }
      else if (*(char *)(iVar3 + 0x1b8c) == 0) {
        // Already in idle state, allow entry
        return 1;
      }
    }
    else {
      // Forced entry
      FUN_0079f100(0x2e, 0); // playSound(46, 0) - vehicle door open?
      FUN_007f63e0(1); // lockPlayerControl or beginAction (forced)
      (**(code **)(**(int **)(this + 0x58) + 0x234))(4, 1); // setState(4, 1) - start forced entry
      FUN_0054e390(1); // enableInput(true)
      result = 1;
    }
  }
  return result;
}