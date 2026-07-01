// FUNC_NAME: Player::findClosestCoverPoint
undefined1 __thiscall Player::findClosestCoverPoint(undefined4 param_1, int param_2, undefined8 *param_3, undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  undefined1 local_131;
  int local_130;
  uint local_12c;
  undefined8 *local_128;
  uint local_124;
  undefined4 local_120;
  float local_11c;
  undefined4 local_118;
  float fStack_114;
  undefined4 local_110;
  undefined8 local_10c;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  float fStack_f8;
  undefined4 local_f4;
  undefined4 local_f0 [4];
  undefined **local_e0;
  undefined4 local_dc;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b0;
  undefined4 local_90;
  int local_80;
  undefined1 local_60 [92];
  
  local_11c = DAT_00d5fae0 + _DAT_00d5c458; // Time offset for animation blending
  local_128 = (undefined8 *)0x0;
  local_124 = 0;
  local_120 = 0;
  FUN_0079af20(8); // Allocate memory for cover point list
  local_131 = 0;
  iVar2 = FUN_007ff880(); // Check if player is in combat mode
  if (iVar2 == 0) {
    local_130 = FUN_007a8630(param_4,&local_e0,&local_128,8,param_1,param_2); // Get cover points from environment
    iVar3 = FUN_00471610(); // Get player position
    local_10c = *(undefined8 *)(iVar3 + 0x30); // Player position XZ
    local_104 = *(undefined4 *)(iVar3 + 0x38); // Player position Y
  }
  else {
    local_130 = FUN_007a87f0(param_4,&local_e0,&local_128); // Get cover points from combat system
    FUN_00799630(&local_10c,iVar2); // Get player position from combat target
  }
  local_10c = CONCAT44(local_10c._4_4_ + local_11c,(undefined4)local_10c); // Add time offset to position
  if (local_130 != 0) {
    if (1 < local_124) {
      _qsort(local_128,local_124,0x10,(_PtFuncCompare *)&LAB_00799600); // Sort cover points by distance
    }
    iVar3 = FUN_007ff880(); // Re-check combat mode
    local_100 = *(undefined4 *)(param_2 + 0x830); // Player's current weapon
    local_130 = 2;
    local_f0[0] = FUN_0043b490(); // Get player's facing direction
    local_f0[1] = FUN_0043b490(); // Get player's movement direction
    if (iVar2 != 0) {
      local_f0[2] = FUN_0043b490(); // Get combat target direction
      local_130 = 3;
    }
    if (iVar3 != 0) {
      uVar4 = FUN_0043b490(); // Get additional combat direction
      local_f0[local_130] = uVar4;
      local_130 = local_130 + 1;
    }
    local_12c = 0;
    puVar5 = local_128;
    if (local_124 != 0) {
      do {
        uVar4 = local_100;
        if (puVar5 != (undefined8 *)0x0) {
          local_110 = *(undefined4 *)(puVar5 + 1); // Cover point Y
          fStack_114 = (float)((ulonglong)*puVar5 >> 0x20); // Cover point XZ
          _local_118 = CONCAT44(fStack_114 + local_11c,(int)*puVar5); // Cover point position with time offset
          cVar1 = FUN_009a7aa0(param_1,&local_10c,&local_118,0x40332,local_100,local_f0,local_130,0,
                               0,0); // Check if cover point is valid (line of sight, angle, etc.)
          if (cVar1 == '\\0') {
            local_f4 = *(undefined4 *)(puVar5 + 1); // Cover point Y
            fStack_f8 = (float)((ulonglong)*puVar5 >> 0x20); // Cover point XZ
            _local_fc = CONCAT44(fStack_f8 - DAT_00d6a5b0,(int)*puVar5); // Cover point position minus offset
            FUN_00542650(&local_118,&local_fc,2,uVar4,0,0); // Calculate movement path to cover point
            local_bc = 0xffffffff;
            local_b0 = 0xffffffff;
            local_e0 = &PTR_FUN_00e32a8c; // Cover point navigation vtable
            local_80 = 0;
            local_c0 = _DAT_00d5780c; // Navigation flags
            local_90 = 0;
            local_dc = _DAT_00d5780c; // Navigation flags
            FUN_009e5ed0(local_60,&local_e0); // Check if path is valid
            if (local_80 != 0) {
              *param_3 = *puVar5; // Return cover point position
              local_131 = 1;
              *(undefined4 *)(param_3 + 1) = *(undefined4 *)(puVar5 + 1);
              break;
            }
          }
        }
        local_12c = local_12c + 1;
        puVar5 = puVar5 + 2;
      } while (local_12c < local_124);
    }
  }
  FUN_009c8f10(local_128); // Free cover point list
  return local_131;
}