// FUNC_NAME: EffectManager::spawnEffect
undefined4 __thiscall EffectManager::spawnEffect(void *this, undefined4 effectId, PositionData *posData, undefined4 param4, int type, int orientationFlags, int loopFlags, undefined4 extraData, float rotation, undefined4 param11, undefined4 param12, undefined4 param13)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  double dVar6;
  undefined4 local_24;
  float local_20;
  undefined4 uStack_1c;
  float fStack_18;
  undefined4 uStack_14;

  // Create base effect object from param_5 (effectId)
  local_24 = FUN_00949ee0(effectId);
  uVar5 = 0;

  // Determine type flags based on param_6 (type)
  if (type == 1) {
    uVar5 = 1; // 0x1 - e.g., once
  }
  else {
    if (type == 4) {
      // Type 4: calculate orientation from position data if not zero
      if (posData->position.x * posData->position.x + 
          posData->position.y * posData->position.y + 
          posData->position.z * posData->position.z == 0.0f) {
        rotation = 0.0f;
      }
      else {
        local_20 = posData->position.x; // +0x20
        uStack_1c = *(undefined4 *)(posData + 0x24); // position.y
        fStack_18 = posData->position.z; // +0x28
        uStack_14 = *(undefined4 *)(posData + 0x2c); // possibly quaternion.w
        // Compute angle using cross product and globals (likely camera transform)
        dVar6 = (double)(DAT_00e56a68 * local_20 - DAT_00e56a60 * fStack_18);
        FUN_00b9a9fa(); // possibly atan2
        rotation = (DAT_00e44564 - (float)dVar6) * DAT_00e44748;
      }
    }
    else if (type != 3) goto LAB_0094cb0f; // type == 3 also falls through to uVar5 = 4
    uVar5 = 4; // 0x4
  }

LAB_0094cb0f:
  // Orientation flags from param_7
  if (orientationFlags == 1) {
    uVar5 |= 0x20; // e.g., world space?
  }
  else if (orientationFlags == 2) {
    uVar5 |= 0x10; // e.g., local space?
  }

  // Loop/start flags from param_8
  if (loopFlags == 0) {
    uVar5 |= 0x200; // play once?
  }
  else if (loopFlags == 1) {
    uVar5 |= 0x100; // loop?
  }

  // Check if effects are enabled (global at DAT_0112af90+0x48)
  if (*(char *)(DAT_0112af90 + 0x48) == '\0') {
    uVar5 |= 0x80; // disabled flag
    FUN_00408680(&DAT_011301a8); // clear or reset some global array
  }

  // Allocate a node from pool (using &local_24 - maybe effect object)
  puVar3 = (undefined4 *)FUN_0094ab00(&local_24);
  if ((*(int *)((int)this + 0x5c) == 0) &&
     ((*(int *)((int)this + 0x58) == 0 || ((*(byte *)((int)this + 0x4c) & 1) == 0)))) {
    FUN_004de190(); // possibly fallback or error handling
  }

  uVar2 = local_24;
  puVar1 = *(undefined4 **)((int)this + 0x5c);
  if (puVar1 != (undefined4 *)0x0) {
    uVar4 = *puVar1;
    *(int *)((int)this + 0x38) = *(int *)((int)this + 0x38) + 1; // active count
    *(int *)((int)this + 0x34) = *(int *)((int)this + 0x34) - 1; // free count
    *(undefined4 *)((int)this + 0x5c) = uVar4; // pop next free node
    if (puVar1 != (undefined4 *)0x0) {
      uVar4 = FUN_0094bd30(local_24, effectId, (posData + 0x30), // +0x30 likely extra data (quaternion or transform)
                           param4, uVar5, extraData, rotation, param11, param12, param13);
      *puVar3 = uVar4;
      return uVar2;
    }
  }

  *puVar3 = 0; // no node available
  return local_24;
}