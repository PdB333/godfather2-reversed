// FUNC_NAME: EARSObject::updateRadioControls
void __fastcall EARSObject::updateRadioControls(int this)
{
  undefined4 *puVar1;
  float local_cc;
  float local_c8;
  float local_c4;
  undefined1 local_c0 [16];
  undefined1 local_b0 [20];
  float local_9c [2];
  float local_94;
  undefined4 local_84;
  undefined4 local_74;
  undefined4 local_64;
  undefined4 local_54;
  undefined4 local_50 [19];
  
  // Check if radio is enabled (bit 4 of flags at +0x8e0) and if a radio state exists at +0x1e40
  // Also ensure radio state is not 0x48 (likely 'stopped' or 'idle')
  if ((((*(uint *)(this + 0x8e0) >> 4 & 1) != 0) && (*(int *)(this + 0x1e40) != 0)) &&
     (*(int *)(this + 0x1e40) != 0x48)) {
    puVar1 = (undefined4 *)FUN_00471610();
    puVar4 = local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    local_84 = 0;
    local_74 = 0;
    local_64 = 0;
    local_54 = _DAT_00d5780c;
    uVar2 = FUN_007f36c0();
    FUN_006cb9d0(local_9c, this + 0xa84, uVar2);
    if (DAT_00d723bc < local_9c[0]) {
      if (local_9c[0] < DAT_00d723b8) {
        local_c4 = local_9c[0];
      }
      else {
        local_c4 = DAT_00d723b8;
      }
    }
    else {
      local_c4 = DAT_00d723bc;
    }
    if (DAT_00d723b4 < local_94) {
      if (local_94 < DAT_00d723b0) {
        local_c8 = local_94;
      }
      else {
        local_c8 = DAT_00d723b0;
      }
    }
    else {
      local_c8 = DAT_00d723b4;
    }
    fVar5 = DAT_00d723ac;
    if ((DAT_00d723ac < local_9c[0]) && (fVar5 = local_9c[0], DAT_00d723a8 <= local_9c[0])) {
      fVar5 = DAT_00d723a8;
    }
    if (DAT_00d723ac < local_94) {
      if (local_94 < DAT_00d723b8) {
        local_cc = local_94;
      }
      else {
        local_cc = DAT_00d723b8;
      }
    }
    else {
      local_cc = DAT_00d723ac;
    }
    if (*(char *)(this + 0xa80) != '\0') {
      fVar5 = 0.0;
      local_cc = 0.0;
    }
    FUN_0056d6f0(DAT_00e44564 - fVar5, local_c0);
    FUN_0056d7b0(local_cc, local_b0);
    FUN_0056cba0(local_c0, local_b0, this + 0xa90);
    FUN_0056d6f0(DAT_00e44564 - local_c4, local_c0);
    FUN_0056d7b0(local_c8, local_b0);
    FUN_0056cba0(local_c0, local_b0, this + 0xaa0);
    FUN_0056cba0(local_c0, local_b0, this + 0xab0);
  }
  return;
}