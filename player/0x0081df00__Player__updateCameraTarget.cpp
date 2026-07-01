// FUNC_NAME: Player::updateCameraTarget
void __fastcall Player::updateCameraTarget(int thisPtr)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  bool bVar5;
  char cVar6;
  int *piVar7;
  undefined4 *puVar8;
  float10 fVar9;
  int *piStack_24;
  int *local_1c;
  int *local_18;
  int local_14;
  
  // Check camera mode flags at +0x10
  // Bit 2 = chase camera, Bit 0 = first person
  if ((*(uint *)(thisPtr + 0x10) >> 2 & 1) == 0) {
    if ((*(byte *)(thisPtr + 0x10) & 1) != 0) {
      // First person mode: set camera target to first person offset
      *(undefined4 *)(*(int *)(thisPtr + 0xf4) + 0x2c) = *(undefined4 *)(thisPtr + 0x18);
    }
  }
  else {
    // Chase camera mode: set camera target to chase offset
    *(undefined4 *)(*(int *)(thisPtr + 0xfc) + 0x2c) = *(undefined4 *)(thisPtr + 0x18);
  }
  
  // If neither first person nor chase camera, return
  if (((*(uint *)(thisPtr + 0x10) >> 2 & 1) == 0) && ((*(byte *)(thisPtr + 0x10) & 1) == 0)) {
    return;
  }
  
  // Get global game manager (DAT_012233a0 + 4)
  iVar1 = **(int **)(DAT_012233a0 + 4);
  if (iVar1 == 0) {
    return;
  }
  
  local_14 = iVar1 + -0x1f30;
  if (local_14 == 0) {
    return;
  }
  
  // Get current vehicle (if any) - offset 0x5f8 points to vehicle object, -0x48 for base
  if (*(int *)(iVar1 + 0x5f8) == 0) {
    piVar7 = (int *)0x0;
  }
  else {
    piVar7 = (int *)(*(int *)(iVar1 + 0x5f8) + -0x48);
  }
  
  bVar5 = false;
  puVar8 = (undefined4 *)(thisPtr + 0x20); // Default camera position offset
  
  // Check for target entity (e.g., enemy, objective) at +0x1278
  if ((*(int *)(iVar1 + 0x1278) != 0) &&
     (local_18 = (int *)(*(int *)(iVar1 + 0x1278) + -0x48), local_18 != (int *)0x0)) {
    local_1c = (int *)0x0;
    // Query if target is valid (vtable +0x10 = isAlive?)
    cVar6 = (**(code **)(*local_18 + 0x10))(0xa0d329d6, &local_1c);
    if ((cVar6 == '\0') ||
       ((local_1c == (int *)0x0 ||
        (fVar9 = (float10)(**(code **)(*local_1c + 0xc0))(), (float10)0 < fVar9)))) {
      // Target is dead or invalid
      if (local_18 == piVar7) {
        bVar5 = false;
      }
      else {
        bVar5 = true;
        puVar8 = (undefined4 *)(thisPtr + 0x60); // Use secondary camera offset
      }
    }
    else {
      // Target is alive
      bVar5 = true;
      puVar8 = (undefined4 *)(thisPtr + 0x70); // Use target tracking offset
    }
  }
  
  // Handle camera mode based on state at +0x120 (isInVehicle?)
  if (*(char *)(thisPtr + 0x120) == '\0') {
    // Not in vehicle
    if ((!bVar5) && (piVar7 != (int *)0x0)) {
      // No target, but have vehicle - check vehicle state
      local_1c = (int *)0x0;
      cVar6 = (**(code **)(*piVar7 + 0x10))(0xa0d329d6, &local_1c);
      if ((cVar6 != '\0') && (piStack_24 != (int *)0x0)) {
        fVar9 = (float10)(**(code **)(*piStack_24 + 0xc0))();
        if ((float10)0 < fVar9) {
          // Vehicle is moving
          fVar9 = (float10)(**(code **)(*piStack_24 + 0xbc))(local_1c);
          if (fVar9 == (float10)0) {
            cVar6 = FUN_00690150(7); // Check some game state
            puVar8 = (undefined4 *)(thisPtr + 0x40); // Use vehicle camera offset
            if (cVar6 == '\0') goto LAB_0081e0af;
          }
          puVar8 = (undefined4 *)(thisPtr + 0x50); // Use alternative vehicle offset
        }
        else {
          puVar8 = (undefined4 *)(thisPtr + 0x70); // Use target tracking offset
        }
      }
    }
  }
  else {
    // In vehicle - use vehicle camera slot
    puVar8 = (undefined4 *)((*(int *)(thisPtr + 0x124) + 2) * 0x10 + thisPtr);
    if (*(int *)(thisPtr + 0x124) == 8) {
      *(undefined4 *)(thisPtr + 0x18) = _DAT_00d5c458; // Default camera target
    }
    else {
      *(undefined4 *)(thisPtr + 0x18) = DAT_00d5842c; // Alternative camera target
    }
  }
  
LAB_0081e0af:
  // Apply camera position to appropriate camera objects
  if ((*(byte *)(thisPtr + 0x10) & 1) == 0) {
    // Not first person - update chase camera
    if ((*(uint *)(thisPtr + 0x10) >> 2 & 1) != 0) {
      iVar1 = *(int *)(thisPtr + 0xfc); // Chase camera object
      uVar2 = puVar8[1];
      uVar3 = puVar8[2];
      uVar4 = puVar8[3];
      *(undefined4 *)(iVar1 + 0x10) = *puVar8;
      *(undefined4 *)(iVar1 + 0x14) = uVar2;
      *(undefined4 *)(iVar1 + 0x18) = uVar3;
      *(undefined4 *)(iVar1 + 0x1c) = uVar4;
      iVar1 = *(int *)(thisPtr + 0x100); // Secondary chase camera
      uVar2 = puVar8[1];
      uVar3 = puVar8[2];
      uVar4 = puVar8[3];
      *(undefined4 *)(iVar1 + 0x10) = *puVar8;
      *(undefined4 *)(iVar1 + 0x14) = uVar2;
      *(undefined4 *)(iVar1 + 0x18) = uVar3;
      *(undefined4 *)(iVar1 + 0x1c) = uVar4;
    }
    return;
  }
  
  // First person mode - update first person camera
  iVar1 = *(int *)(thisPtr + 0xf4); // First person camera object
  uVar2 = puVar8[1];
  uVar3 = puVar8[2];
  uVar4 = puVar8[3];
  *(undefined4 *)(iVar1 + 0x10) = *puVar8;
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  *(undefined4 *)(iVar1 + 0x18) = uVar3;
  *(undefined4 *)(iVar1 + 0x1c) = uVar4;
  iVar1 = *(int *)(thisPtr + 0xf8); // Secondary first person camera
  uVar2 = puVar8[1];
  uVar3 = puVar8[2];
  uVar4 = puVar8[3];
  *(undefined4 *)(iVar1 + 0x10) = *puVar8;
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  *(undefined4 *)(iVar1 + 0x18) = uVar3;
  *(undefined4 *)(iVar1 + 0x1c) = uVar4;
  return;
}