// FUNC_NAME: PlayerActionableTargetSM::updateTargetList
void __thiscall PlayerActionableTargetSM::updateTargetList(int thisPtr, int *targetList, int param_3)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  char cVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  int local_7c;
  int local_78;
  int *local_74;
  int *local_70;
  int *local_6c;
  int local_68;
  int iStack_64;
  int iStack_60;
  int *piStack_5c;
  float fStack_58;
  int local_54;
  int iStack_50;
  int local_4c;
  int iStack_48;
  float fStack_44;
  int *local_40 [2];
  int *local_38 [3];
  undefined8 uStack_2c;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  
  // Check if targeting is enabled (bit 2 of some flag at this+4+0xe4)
  if ((~(byte)(*(uint *)(*(int *)(thisPtr + 4) + 0xe4) >> 2) & 1) != 0) {
    local_7c = *(int *)(param_3 + 0x4c) - targetList[1]; // remaining capacity
    local_54 = 0;
    if (0 < targetList[1]) {
      local_78 = 0;
      local_68 = 0;
      do {
        iVar9 = *targetList + local_78;
        local_70 = (int *)0x0;
        local_4c = iVar9;
        // Get entity from entity manager (type 0x2001)
        FUN_004af8c0(local_40,0x2001);
        if (local_40[0] != (int *)0x0) {
          local_70 = local_40[0];
        }
        local_74 = (int *)0x0;
        FUN_004af8c0(local_38,0x2001);
        if (local_38[0] != (int *)0x0) {
          local_74 = local_38[0];
        }
        local_6c = (int *)0x0;
        // Check if entity has a specific component (hash 0x55859efa)
        cVar5 = (**(code **)(*local_70 + 0x10))(0x55859efa,&local_6c);
        if ((cVar5 != '\\0') && (piStack_5c = local_6c, local_6c != (int *)0x0)) {
          // Check if entity is alive and has a valid health component
          if (((char)local_6c[0x3fe] == '\\x01') &&
             ((local_6c[0x3fc] != 0 && (iStack_60 = local_6c[0x3fc] + -0x48, iStack_60 != 0)))) {
            // Allocate memory for a new target entry
            piVar6 = (int *)TlsGetValue(DAT_01139810);
            iVar8 = piVar6[8];
            if ((uint)piVar6[0xb] < iVar8 + 0x10U) {
              iVar8 = (**(code **)(*piVar6 + 0x14))(0x10);
            }
            else {
              piVar6[8] = iVar8 + 0x10U;
            }
            iStack_64 = iStack_60 + 0x3c0;
            if (iStack_64 != 0) {
              iStack_50 = *(int *)(param_3 + 0x48) + local_68;
              iVar7 = FUN_00553700(); // Get some global state
              iStack_48 = *(int *)(iVar7 + 4);
              iStack_60 = 0;
              if (0 < iStack_48) {
                iVar7 = 0;
                do {
                  if (3 < local_7c) break;
                  piVar6 = (int *)FUN_00553700();
                  iVar4 = *piVar6;
                  // Check if entity is within some range (dot product with zero vector)
                  if (*(float *)(iVar7 + 0x18 + iVar4) * 0.0 +
                      *(float *)(iVar7 + 0x10 + iVar4) * 0.0 + *(float *)(iVar7 + 0x14 + iVar4) <=
                      DAT_00d723d0) {
                    puVar10 = (undefined4 *)
                              (*(int *)(param_3 + 0x4c) * 0x40 + *(int *)(param_3 + 0x48));
                    FUN_007f4170(iStack_50); // Initialize target entry
                    puVar10[7] = 0;
                    puVar10[6] = 0;
                    puVar10[5] = 0;
                    puVar10[4] = 0;
                    piVar6 = (int *)FUN_00553700();
                    iVar9 = *piVar6;
                    uVar1 = *(undefined4 *)(iVar9 + 0x14 + iVar7);
                    uVar2 = *(undefined4 *)(iVar9 + 0x18 + iVar7);
                    *puVar10 = *(undefined4 *)(iVar9 + 0x10 + iVar7);
                    puVar10[1] = uVar1;
                    puVar10[2] = uVar2;
                    puVar10[3] = 0;
                    puVar10[8] = _DAT_00d6e970;
                    *(int *)(param_3 + 0x4c) = *(int *)(param_3 + 0x4c) + 1;
                    local_7c = local_7c + 1;
                    iVar9 = local_4c;
                  }
                  iStack_60 = iStack_60 + 1;
                  iVar7 = iVar7 + 0x30;
                } while (iStack_60 < iStack_48);
              }
            }
            // Free allocated memory
            piVar6 = (int *)TlsGetValue(DAT_01139810);
            piVar6[8] = iVar8;
            if (iVar8 == piVar6[10]) {
              (**(code **)(*piVar6 + 0x18))(iVar8);
            }
          }
          // Get some object from entity data
          iVar8 = FUN_005566a0(*(undefined4 *)(iVar9 + 0x28),*(undefined4 *)(iVar9 + 0x2c));
          if (local_74 != (int *)0x0) {
            iStack_60 = 0;
            // Check if entity has a specific component (hash 0xa5975eb2)
            cVar5 = (**(code **)(*local_74 + 0x10))(0xa5975eb2,&iStack_60);
            if (((cVar5 == '\\0') || (iStack_60 == 0)) &&
               ((*(int *)(**(int **)(iVar9 + 0x28) + 0xc) != 0xb ||
                ((iVar8 != 0 && ((*(uint *)(iVar8 + 4) & 0x20000000) != 0)))))) {
              // Process existing targets for distance checks
              iVar9 = *(int *)(param_3 + 0x4c);
              iVar8 = 0;
              iStack_60 = 0;
              iStack_48 = iVar9;
              if (0 < iVar9) {
                do {
                  if (3 < local_7c) break;
                  iVar7 = *(int *)(param_3 + 0x48);
                  fStack_44 = *(float *)(iVar7 + 8 + iVar8) * 0.0 + *(float *)(iVar7 + iVar8) * 0.0
                              + *(float *)(iVar7 + iVar8 + 4);
                  if ((DAT_00d5ef84 < fStack_44) && (fStack_44 < DAT_00d723d0)) {
                    pfVar11 = (float *)(*(int *)(param_3 + 0x4c) * 0x40 + iVar7);
                    FUN_007f4170(iVar7 + iVar8); // Initialize target entry
                    fVar13 = DAT_00e44564 - fStack_44;
                    pfVar11[7] = 0.0;
                    pfVar11[6] = 0.0;
                    pfVar11[5] = 0.0;
                    pfVar11[4] = 0.0;
                    fVar17 = pfVar11[3];
                    fVar14 = fVar13 + pfVar11[1];
                    fVar13 = fVar13 * 0.0;
                    fVar12 = *pfVar11 + fVar13;
                    fVar15 = fVar13 + pfVar11[2];
                    fVar16 = fVar15 * fVar15 + fVar14 * fVar14 + fVar12 * fVar12;
                    *pfVar11 = fVar12;
                    pfVar11[1] = fVar14;
                    pfVar11[2] = fVar15;
                    pfVar11[3] = fVar17 + fVar13;
                    if (fVar16 == 0.0) {
                      fVar16 = 0.0;
                    }
                    else {
                      fVar16 = _DAT_00d5780c / SQRT(fVar16);
                    }
                    *pfVar11 = fVar12 * fVar16;
                    pfVar11[1] = fVar14 * fVar16;
                    pfVar11[2] = fVar15 * fVar16;
                    pfVar11[3] = (fVar17 + fVar13) * fVar16;
                    *(int *)(param_3 + 0x4c) = *(int *)(param_3 + 0x4c) + 1;
                    local_7c = local_7c + 1;
                    iVar9 = iStack_48;
                  }
                  iStack_60 = iStack_60 + 1;
                  iVar8 = iVar8 + 0x40;
                } while (iStack_60 < iVar9);
              }
            }
            // Check if entity type is 6 (likely a specific game object type)
            if (*(int *)(**(int **)(local_78 + 0x28 + *targetList) + 0xc) == 6) {
              fStack_58 = DAT_00d71b00;
              iStack_60 = 0;
              // Check for specific component (hash 0x383225a1)
              cVar5 = (**(code **)(*local_6c + 0x10))(0x383225a1,&iStack_60);
              if ((((cVar5 == '\\0') || (iStack_60 == 0)) ||
                  ((*(byte *)(iStack_60 + 0x8e6) & 1) != 0)) ||
                 ((cVar5 = FUN_00690210(0x39), cVar5 == '\\0' ||
                  (cVar5 = FUN_00690210(0x4c), cVar5 != '\\0')))) {
                // Check if entity has a specific flag and is valid for targeting
                if ((((uint)piStack_5c[0x23b] >> 3 & 1) != 0) &&
                   (iVar9 = FUN_006bc8d0(local_74,0x369ac561), iVar9 != 0)) goto LAB_00809f03;
              }
              else {
                cVar5 = FUN_00481640(); // Check if player is in some state
                if ((cVar5 == '\\0') &&
                   ((cVar5 = FUN_00690150(9), cVar5 == '\\0' ||
                    (piVar6 = (int *)FUN_00716c30(), piVar6 != local_74)))) {
                  iVar9 = FUN_006bc8b0(local_74); // Get some component
                  if ((iVar9 != 0) && (cVar5 = FUN_006eb940(), cVar5 != '\\0')) {
                    if ((*(uint *)(iVar9 + 0x48) >> 1 & 1) != 0) goto LAB_0080a01b;
                    fStack_58 = _DAT_00d5ca1c;
                  }
LAB_00809f03:
                  iVar9 = *targetList;
                  fVar17 = *(float *)(local_78 + 0x10 + iVar9);
                  fVar12 = *(float *)(local_78 + 0x14 + iVar9);
                  fVar13 = *(float *)(local_78 + 0x18 + iVar9);
                  iVar9 = 0;
                  fStack_20 = fVar17;
                  fStack_1c = fVar12;
                  fStack_18 = fVar13;
                  if (0 < *(int *)(param_3 + 0x4c)) {
                    local_70 = (int *)0x0;
                    do {
                      pfVar11 = (float *)(*(int *)(param_3 + 0x48) + (int)local_70);
                      uVar3 = uStack_2c;
                      // Check dot product with target direction
                      if (DAT_00e446dc <
                          pfVar11[2] * fVar13 + pfVar11[1] * fVar12 + *pfVar11 * fVar17) {
                        iVar8 = FUN_00471610(); // Get camera info
                        uVar3 = *(undefined8 *)(iVar8 + 0x20);
                        fStack_24 = *(float *)(iVar8 + 0x28);
                        uStack_2c._4_4_ = (float)((ulonglong)uVar3 >> 0x20);
                        uStack_2c._0_4_ = (float)uVar3;
                        fVar17 = fStack_20;
                        fVar12 = fStack_1c;
                        fVar13 = fStack_18;
                        // Check if target is in front of camera
                        if (fStack_1c * uStack_2c._4_4_ + fStack_18 * fStack_24 +
                            fStack_20 * (float)uStack_2c < 0.0) {
                          pfVar11[6] = fStack_24 * fStack_58;
                          fVar14 = _DAT_00d5780c;
                          pfVar11[4] = (float)uStack_2c * fStack_58;
                          pfVar11[5] = uStack_2c._4_4_;
                          pfVar11[7] = fVar14;
                        }
                      }
                      uStack_2c = uVar3;
                      local_70 = (int *)((int)local_70 + 0x40);
                      iVar9 = iVar9 + 1;
                    } while (iVar9 < *(int *)(param_3 + 0x4c));
                  }
                }
              }
            }
          }
        }
LAB_0080a01b:
        local_68 = local_68 + 0x40;
        local_78 = local_78 + 0x30;
        local_54 = local_54 + 1;
      } while (local_54 < targetList[1]);
    }
  }
  return;
}