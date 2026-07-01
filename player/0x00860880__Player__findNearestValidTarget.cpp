// FUNC_NAME: Player::findNearestValidTarget
void __thiscall Player::findNearestValidTarget(int *this, int param_2, float *outDistance)
{
  uint *puVar1;
  bool bFound;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float closestDistSq;
  int local_1c;
  int local_18;
  int *local_14;
  float fStack_10;
  int local_c;
  int *local_8 [2];
  
  // Get target list from this object at offset 0x3e5 * 4 = 0xF94 (likely a pointer to a container)
  local_14 = (int *)(this[0x3e5] + 0xc0); // +0xc0: pointer to array of target pointers
  local_c = *(int *)(this[0x3e5] + 0xc4); // +0xc4: count of targets
  bFound = false;
  closestDistSq = DAT_00e44794; // Some global max distance constant
  local_18 = 0;
  if (0 < local_c) {
    do {
      iVar6 = *(int *)(*local_14 + local_18 * 4);
      if ((iVar6 != 0) && (*(char *)(iVar6 + 0x10) + iVar6 != 0)) {
        // Get the player object (likely singleton)
        FUN_004af8c0(local_8, 0x2001); // Get player by ID 0x2001
        piVar7 = (int *)0x0;
        if (local_8[0] != (int *)0x0) {
          piVar7 = local_8[0];
        }
        if ((piVar7 != (int *)0x0) && (piVar7 != this)) {
          local_1c = 0;
          // Call virtual function at vtable+0x10 to get some object from player
          cVar3 = (**(code **)(*piVar7 + 0x10))(0x10e5319e, &local_1c);
          iVar6 = local_1c;
          if ((cVar3 != '\0') &&
             ((local_1c != 0 &&
              (puVar1 = (uint *)(local_1c + 0xc88), (*(uint *)(local_1c + 0xc88) >> 2 & 1) == 0))))
          {
            // Get two positions (likely player and target)
            iVar4 = FUN_00471610(); // Get player position
            iVar5 = FUN_00471610(); // Get target position
            fVar8 = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30); // dx
            fVar9 = *(float *)(iVar5 + 0x34) - *(float *)(iVar4 + 0x34); // dy
            fVar10 = *(float *)(iVar5 + 0x38) - *(float *)(iVar4 + 0x38); // dz
            fStack_10 = fVar10 * fVar10 + fVar9 * fVar9 + fVar8 * fVar8; // distance squared
            
            if ((fStack_10 < closestDistSq) &&
               (((((iVar4 = FUN_00542d70(), iVar4 != 0 && (*(int *)(iVar4 + 0xc4) == 1)) && // Check target type
                  (*(int *)(iVar6 + 0xf2c) == 2)) && // Check some state at +0xF2C
                 (((*(uint *)(iVar6 + 0xf28) >> 0xc & 1) == 0 && // Check flags at +0xF28
                  ((*(uint *)(iVar6 + 0xf28) >> 0xe & 1) == 0)))) &&
                (((*puVar1 >> 0xb & 1) == 0 && // Check flags at +0xC88
                 ((*(int *)(iVar6 + 0xfd0) == param_2 || (cVar3 = FUN_00860440(), cVar3 != '\0')))) // Check target ID or special condition
                ))) {
              // Check dot product with forward vector
              iVar6 = FUN_00471610(); // Get forward vector
              iVar4 = FUN_00471610(); // Get direction to target
              if (_DAT_00d577a0 <= // Some threshold (likely cos(angle))
                  *(float *)(iVar4 + 0x24) * *(float *)(iVar6 + 0x24) +
                  *(float *)(iVar4 + 0x20) * *(float *)(iVar6 + 0x20) +
                  *(float *)(iVar4 + 0x28) * *(float *)(iVar6 + 0x28)) {
                closestDistSq = fStack_10;
                bFound = true;
              }
            }
          }
        }
      }
      local_18 = local_18 + 1;
    } while (local_18 < local_c);
    if (bFound) {
      *outDistance = SQRT(closestDistSq);
    }
  }
  return;
}