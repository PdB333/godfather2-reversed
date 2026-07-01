// FUNC_NAME: Player::updateAimAssist
void __thiscall Player::updateAimAssist(int this, float *aimDir, undefined4 *cameraInfo, undefined4 param4)
{
  byte bVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float local_114;
  float local_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float local_100;
  float fStack_fc;
  float local_f8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  undefined1 local_d0 [32];
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  undefined1 local_90 [64];
  undefined1 local_50 [76];
  
  // Check if player state is not in certain states (3=dead, 4=dying) and game is not paused
  if (((*(int *)(this + 0x14c) != 3) && (*(int *)(this + 0x14c) != 4)) &&
     (*(int *)(DAT_0112982c + 0x6c) == 0)) {
    bVar1 = *(byte *)(this + 0x49) & 2;
    if ((bVar1 == 0) && ((*(byte *)(this + 0x49) & 8) == 0)) {
      // Convert camera info to a matrix (local_d0)
      FUN_0056b8a0(cameraInfo[1],*cameraInfo,cameraInfo[2],local_d0);
      local_a0 = *aimDir;
      fStack_9c = aimDir[1];
      fStack_98 = aimDir[2];
      fStack_94 = aimDir[3];
      // Check if aim assist is enabled and player is not in a vehicle
      if (((*(char *)(this + 0x1c0) == '\0') || (*(char *)(this + 0x1c1) == '\0')) ||
         ((*(int *)(this + 0x68) == 0 || (*(int *)(*(int *)(this + 0x68) + 0x110) != 0)))) {
        FUN_009772f0(local_d0);
        fStack_10c = aimDir[1];
        local_110 = *aimDir;
        local_f8 = aimDir[2];
        _local_100 = CONCAT44(local_ac * _DAT_00d8fab4 + fStack_10c,
                              local_b0 * _DAT_00d8fab4 + local_110);
        local_d8 = local_a8;
      }
      else {
        // Apply aim assist with snap-to-target
        FUN_00614440(param4,DAT_01205878,0x3f800000,DAT_00d5e288,local_50,local_90);
        if (*(int *)(DAT_01130020 + 0x78) < 1) {
          FUN_00926810(&local_114,&local_e4);
          fVar5 = DAT_00d5eee4;
          fVar4 = _DAT_00d5780c;
          *(float *)(this + 0x1b0) = local_114 * DAT_00d5eee4 - _DAT_00d5780c;
          *(float *)(this + 0x1b4) = fVar4 - local_e4 * fVar5;
        }
        local_110 = *(float *)(this + 0x1b0);
        fStack_10c = *(float *)(this + 0x1b4);
        fStack_108 = *(float *)(this + 0x1b8);
        fStack_104 = *(float *)(this + 0x1bc);
        FUN_0056b420(local_90,&local_110,&local_110);
        FUN_0045c110(_DAT_00d5780c / fStack_104,&local_110,&local_110);
        FUN_0056b420(local_d0,&local_110,&local_100);
        FUN_00414c60(&local_100,aimDir,&local_e0);
        local_d4 = _DAT_00d5780c;
        FUN_004177a0(&local_e0,&local_e0);
        FUN_009772f0(local_d0);
        fStack_10c = aimDir[1];
        local_110 = *aimDir;
        local_f8 = aimDir[2];
        _local_100 = CONCAT44(local_dc * _DAT_00d8fab4 + fStack_10c,
                              local_e0 * _DAT_00d8fab4 + local_110);
      }
      fStack_108 = local_f8;
      local_f8 = local_d8 * _DAT_00d8fab4 + local_f8;
      fVar3 = (float10)FUN_0084c870(&local_110,&local_100,&DAT_00e575bc,0);
      local_e4 = (float)fVar3;
      if ((float10)0 <= fVar3) {
        local_a0 = (local_100 - local_110) * local_e4 + local_a0;
        fStack_9c = (fStack_fc - fStack_10c) * local_e4 + fStack_9c;
        fStack_98 = (local_f8 - fStack_108) * local_e4 + fStack_98;
        FUN_009763c0(local_d0);
        iVar2 = *(int *)(this + 0x68);
        if (((iVar2 != 0) && (*(int *)(iVar2 + 0x110) == 0)) &&
           ((*(uint *)(this + 0x60) >> 9 & 1) != 0)) {
          FUN_0097e700(&local_a0,aimDir,*(undefined4 *)(iVar2 + 0xe0));
        }
      }
    }
    else if (bVar1 == 2) {
      FUN_0056b8a0(cameraInfo[1],*cameraInfo,cameraInfo[2],local_d0);
      local_a0 = *aimDir;
      fStack_9c = aimDir[1];
      fStack_98 = aimDir[2];
      fStack_94 = aimDir[3];
      FUN_009772f0(local_d0);
    }
    if ((DAT_012233ac != 0) && (*(int *)(this + 0x68) != 0)) {
      iVar2 = FUN_00424fb0(&local_110,0);
      if (*(float *)(iVar2 + 4) <= DAT_00e448d8) {
        fVar4 = *(float *)(this + 0x78);
      }
      else {
        fVar4 = aimDir[1] - _DAT_00d8f950;
        fVar5 = DAT_00d5d7b8;
        if ((fVar4 < DAT_00d5d7b8) ||
           (fVar5 = _DAT_00d8fab4, local_114 = fVar4, _DAT_00d8fab4 < fVar4)) {
          fVar4 = fVar5;
          local_114 = fVar5;
        }
      }
      FUN_00478680(fVar4);
      FUN_00478670(*(undefined4 *)(*(int *)(this + 0x68) + 0xe8));
    }
  }
  return;
}