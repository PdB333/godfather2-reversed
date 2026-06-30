// FUNC_NAME: CollisionCamera::raycastTerrain
float __thiscall CollisionCamera::raycastTerrain(int this, undefined4 *rayStart, undefined4 *rayEnd, undefined4 *hitResult, char param5)
{
  float fVar1;
  int iVar2;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined **local_50;
  float local_4c;
  char local_48;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  
  // Check if camera is disabled via global flag at +0x54
  if (*(char *)(DAT_01223394 + 0x54) != '\0') {
    return (float)1.0f;
  }
  
  // Copy ray start and set w component to 0
  local_80 = *rayStart;
  local_7c = rayStart[1];
  local_78 = rayStart[2];
  local_74 = 0;
  FUN_009f1820(&local_80, 0); // Likely vector normalization or setup
  
  // Copy ray end
  local_70 = *rayEnd;
  local_6c = rayEnd[1];
  local_68 = rayEnd[2];
  local_64 = 0;
  
  // Some global constants
  local_60 = DAT_00d5ef84;
  local_5c = DAT_00d5ef84;
  
  if (param5 == '\0') {
    iVar2 = 0;
    local_18 = 0;
  }
  else {
    // Check some global pointer for collision context
    if (**(int **)(DAT_012233a0 + 4) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
      if (iVar2 != 0) {
        local_18 = FUN_007ff880(); // Likely getCollisionFilter or similar
        goto LAB_006c9bda;
      }
    }
    local_18 = 0;
  }
  
LAB_006c9bda:
  // Get camera transform from this+0x88
  local_20 = *(undefined4 *)(this + 0x88);
  local_48 = '\0';
  local_24 = DAT_00e445dc; // Some global float constant
  local_4c = DAT_00e445dc;
  local_50 = &PTR_LAB_00d5f038; // Likely function pointer table for collision
  local_1c = iVar2;
  
  // Perform raycast against terrain
  FUN_009e7fd0(*(int *)(this + 0x84) + 0x10, &local_70, &local_50, 0);
  
  fVar1 = _DAT_00d5780c; // Global hit distance
  local_84 = _DAT_00d5780c;
  
  if (hitResult != (undefined4 *)0x0) {
    hitResult[2] = 0;
    hitResult[1] = 0;
    *hitResult = 0;
  }
  
  // If hit detected (local_48 != 0), clamp distance
  if (local_48 != '\0') {
    local_84 = local_24;
    if (0.0f < local_24) {
      if (fVar1 <= local_24) {
        local_84 = fVar1;
      }
    }
    else {
      local_84 = 0.0f;
    }
    if (hitResult != (undefined4 *)0x0) {
      *hitResult = local_30;
      hitResult[1] = local_2c;
      hitResult[2] = local_28;
    }
  }
  
  return (float)local_84;
}