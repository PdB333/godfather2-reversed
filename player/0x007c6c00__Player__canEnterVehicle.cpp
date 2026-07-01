// FUNC_NAME: Player::canEnterVehicle
bool __fastcall Player::canEnterVehicle(int thisPtr)
{
  char cVar1;
  undefined8 *puVar2;
  float *pfVar3;
  int iVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  float local_18;
  float fStack_14;
  float local_c;
  float local_8;
  float local_4;

  // Check if player is already in a vehicle (bit 7 of flags at +0x128)
  if ((*(uint *)(thisPtr + 0x128) >> 7 & 1) != 0) {
    // Return whether current vehicle is different from target vehicle
    return *(int *)(thisPtr + 0x118) != *(int *)(thisPtr + 0x120);
  }
  // Check if player is allowed to enter vehicles (bit 2 of flags at +0x128)
  if (((*(uint *)(thisPtr + 0x128) >> 2 & 1) != 0) && (cVar1 = FUN_007c6ab0(), cVar1 == '\\0')) {
    // Determine target position based on current vehicle state
    if (*(int *)(thisPtr + 0x118) == 2) {
      // Player is in a vehicle (state 2) - get vehicle position
      puVar2 = (undefined8 *)FUN_00471610();
      fVar5 = *(float *)(puVar2 + 1);
      fStack_14 = (float)((ulonglong)*puVar2 >> 0x20);
      local_18 = (float)*puVar2;
    }
    else {
      // Player is not in a vehicle - get world position offset
      pfVar3 = (float *)FUN_00471610();
      local_18 = DAT_00e44564 - *pfVar3;
      fStack_14 = DAT_00e44564 - pfVar3[1];
      fVar5 = DAT_00e44564 - pfVar3[2];
    }
    // Scale position by some factor
    local_18 = local_18 * DAT_00d6e928;
    fStack_14 = fStack_14 * DAT_00d6e928;
    fVar5 = fVar5 * DAT_00d6e928;
    // Get player position and add offset
    iVar4 = FUN_00471610();
    local_c = *(float *)(iVar4 + 0x30) + local_18;
    local_8 = *(float *)(iVar4 + 0x34) + fStack_14;
    local_4 = *(float *)(iVar4 + 0x38) + fVar5;
    uVar6 = 0;
    pfVar3 = &local_c;
    uVar7 = DAT_00d5ccf8;
    // Perform some spatial query (likely raycast or overlap check)
    FUN_007ab110(pfVar3,0,DAT_00d5ccf8);
    iVar4 = FUN_00550d30(pfVar3,uVar6,uVar7);
    if (iVar4 != 0) {
      return true;
    }
  }
  return false;
}