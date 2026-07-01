// FUNC_NAME: Player::spawnAtSafehouse
undefined4 Player::spawnAtSafehouse(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  undefined **local_120;
  undefined4 local_11c;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f0;
  undefined4 local_d0;
  int local_c0;
  undefined1 local_b0 [80];
  undefined1 local_60 [92];
  
  iVar1 = FUN_007ab710(); // GetPlayerManager
  if ((iVar1 != 0) && (*(char *)(iVar1 + 0x1b8c) == '\0')) { // Check if not in mission
    iVar1 = FUN_00896b30((-(uint)(param_1 != 0) & 0xffffff8b) + 0x81,0x30000,0x3f800000,DAT_00d5ccf8
                         ,2,0); // Create entity at safehouse
    if (iVar1 == 0) {
      FUN_008970a0(&local_144); // Get current camera position
      local_140 = local_140 + _DAT_00d5cf70; // Add offset
      if (param_1 == 0) {
        uVar2 = 0x80; // Spawn type: player
      }
      else {
        uVar2 = 8; // Spawn type: gangster
      }
      FUN_00896470(uVar2,&local_138); // Get spawn offset
      local_12c = local_138 + local_144;
      local_128 = local_134 + local_140;
      local_124 = local_130 + local_13c;
      FUN_00542650(&local_144,&local_12c,0x20,0x30000,0,0); // Set entity position
      local_fc = 0xffffffff;
      local_f0 = 0xffffffff;
      local_120 = &PTR_FUN_00e32a8c;
      local_c0 = 0;
      local_100 = _DAT_00d5780c;
      local_d0 = 0;
      local_11c = _DAT_00d5780c;
      FUN_009e5ed0(local_60,&local_120); // Create entity
      if (local_c0 == 0) {
        if (param_1 == 0) {
          uVar2 = 1; // Spawn type: player
        }
        else {
          uVar2 = 4; // Spawn type: gangster
        }
        FUN_00896470(uVar2,&local_138); // Get spawn offset
        local_12c = local_138 + local_144;
        local_128 = local_134 + local_140;
        local_124 = local_130 + local_13c;
        FUN_00542650(&local_144,&local_12c,0x20,0x30000,0,0); // Set entity position
        FUN_009e5ed0(local_b0,&local_120); // Create entity
        if (local_c0 == 0) {
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}