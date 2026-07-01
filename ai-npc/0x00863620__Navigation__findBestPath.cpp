// FUNC_NAME: Navigation::findBestPath
undefined4 __thiscall Navigation::findBestPath(int thisPtr, int param_2, float *targetPos)
{
  int iVar1;
  float fVar2;
  float *pfVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  float fVar9;
  float local_58;
  uint local_50;
  int local_4c;
  float local_48;
  uint local_44;
  int local_40;
  uint local_3c;
  int *local_38;
  int local_34;
  int *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24 [2];
  int local_1c;
  int local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined8 local_c;
  undefined4 local_4;
  
  pfVar3 = *(float **)(thisPtr + 8); // +0x8: current position
  if (*(float *)(thisPtr + 0x1c) <= // +0x1c: max distance squared
      (pfVar3[2] - targetPos[2]) * (pfVar3[2] - targetPos[2]) +
      (pfVar3[1] - targetPos[1]) * (pfVar3[1] - targetPos[1]) +
      (*pfVar3 - *targetPos) * (*pfVar3 - *targetPos)) {
    return 1; // Already at target
  }
  local_44 = (uint)*(byte *)(targetPos + 5); // +5: number of path nodes
  local_58 = 0.0;
  if (local_44 != 0) {
    do {
      iVar7 = (uint)(ushort)(*(short *)(targetPos + 4) + local_58._0_2_) * 0x10 + // +4: path node index
              *(int *)(param_2 + 0x24); // +0x24: path node table
      iVar1 = *(int *)(param_2 + 0x20) + (uint)*(ushort *)(iVar7 + 4) * 0x24; // +0x20: node data array
      local_3c = 0;
      local_38 = (int *)0x0;
      cVar6 = FUN_005fd340(*(undefined2 *)(iVar7 + 8),0xc2e43267,&local_3c); // Check if node is blocked
      if (((((cVar6 == '\0') || (local_38 == (int *)0x0)) || (local_3c == 0)) ||
          (((*(char *)(local_3c + 6) != '\x02' || (*local_38 == 0)) ||
           (*(char *)(thisPtr + 0x30) != '\0')))) && // +0x30: ignore blocked flag
         (((*(char *)(thisPtr + 0x30) == '\0' ||
           (cVar6 = FUN_005fd340(*(undefined2 *)(iVar7 + 8),0xf7276be5,&local_3c), cVar6 == '\0'))
          || ((local_38 == (int *)0x0 ||
              (((local_3c == 0 || (*(char *)(local_3c + 6) != '\x02')) || (*local_38 == 0)))))))) {
        FUN_0084cb90(*(undefined4 *)(thisPtr + 8),targetPos,iVar1,&local_18,1); // Calculate distance
        fVar9 = (float)extraout_ST0;
        bVar5 = false;
        if (extraout_ST0 <= (float10)*(float *)(thisPtr + 0x20)) { // +0x20: current best distance
          if (*(char *)(thisPtr + 0x31) != '\0') { // +0x31: check line of sight flag
            FUN_004a0b00(targetPos,*(undefined4 *)(thisPtr + 0x34),iVar1,&DAT_00d75690); // Check line of sight
            fVar2 = (float)extraout_ST0_00;
            if ((extraout_ST0_00 < (float10)0) && (iVar7 = FUN_005f5ec0(iVar1,targetPos), iVar7 != 0)) // Find connecting node
            {
              local_34 = 0;
              local_30 = (int *)0x0;
              bVar4 = true;
              cVar6 = FUN_005fd340(*(undefined2 *)(iVar7 + 8),0xc2e43267,&local_34);
              if ((cVar6 == '\0') ||
                 ((cVar6 = FUN_006a7fd0(&local_48), cVar6 == '\0' || (local_48 == 0.0)))) {
LAB_00863805:
                if (*(char *)(thisPtr + 0x30) != '\0') goto LAB_0086380b;
              }
              else {
                if (*(char *)(thisPtr + 0x30) == '\0') {
                  bVar4 = false;
                  goto LAB_00863805;
                }
LAB_0086380b:
                cVar6 = FUN_005fd340(*(undefined2 *)(iVar7 + 8),0xf7276be5,&local_34);
                if (((cVar6 != '\0') && (cVar6 = FUN_006a7fd0(&local_4c), cVar6 != '\0')) &&
                   (local_4c != 0)) goto LAB_00863882;
              }
              if (bVar4) {
                FUN_004a0b00(iVar1,*(undefined4 *)(thisPtr + 0x34),targetPos,&DAT_00d75690);
                if ((float10)fVar2 < extraout_ST0_01) {
                  bVar5 = true;
                  fVar2 = (float)extraout_ST0_01;
                }
              }
            }
LAB_00863882:
            fVar9 = (DAT_00e445a4 - fVar2) + fVar9; // Adjust distance by line of sight penalty
          }
          if (fVar9 <= *(float *)(thisPtr + 0x20)) {
            if (bVar5) {
              *(float **)(thisPtr + 0x14) = targetPos; // +0x14: best target position
              *(int *)(thisPtr + 0x18) = iVar1; // +0x18: best node
            }
            else {
              *(int *)(thisPtr + 0x14) = iVar1; // +0x14: best node
              *(float **)(thisPtr + 0x18) = targetPos; // +0x18: best target position
            }
            *(ulonglong *)(thisPtr + 0x24) = CONCAT44(uStack_14,local_18); // +0x24: path data
            *(int *)(thisPtr + 0xc) = param_2; // +0xc: navigation context
            *(int *)(thisPtr + 0x10) = param_2; // +0x10: navigation context
            *(float *)(thisPtr + 0x20) = fVar9; // +0x20: best distance
            *(undefined4 *)(thisPtr + 0x2c) = local_10; // +0x2c: extra data
          }
          if (fVar9 <= _DAT_00d5780c) {
            return 1; // Found optimal path
          }
        }
      }
      local_58 = (float)((int)local_58 + 1);
    } while ((uint)local_58 < local_44);
  }
  local_3c = (uint)*(byte *)(targetPos + 7) + (uint)*(byte *)((int)targetPos + 0x15); // +7 and +0x15: alternate path counts
  local_50 = 0;
  if (local_3c != 0) {
    do {
      iVar8 = (uint)(ushort)(*(short *)((int)targetPos + 0x16) + (short)local_50) * 0x10 + // +0x16: alternate path index
              *(int *)(param_2 + 0x30); // +0x30: alternate path table
      FUN_005fd1c0(local_24,iVar8); // Get path data
      iVar7 = local_1c;
      iVar1 = local_24[0];
      if (local_24[0] != 0) {
        if (local_1c != 0) {
          local_4c = local_1c;
          local_34 = 0;
          local_30 = (int *)0x0;
          cVar6 = FUN_005fd340(*(undefined2 *)(iVar8 + 8),0xc2e43267,&local_34);
          if (((cVar6 == '\0') || (local_30 == (int *)0x0)) ||
             ((local_34 == 0 || ((*(char *)(local_34 + 6) != '\x02' || (*local_30 == 0)))))) {
            if (*(char *)(thisPtr + 0x30) != '\0') goto LAB_008639db;
LAB_00863a10:
            iVar8 = local_4c;
            FUN_0084cb90(*(undefined4 *)(thisPtr + 8),targetPos,local_4c,&local_c,1);
            fVar9 = (float)extraout_ST0_02;
            bVar5 = false;
            local_48 = fVar9;
            if (extraout_ST0_02 <= (float10)*(float *)(thisPtr + 0x20)) {
              if (*(char *)(thisPtr + 0x31) != '\0') {
                FUN_004a0b00(targetPos,*(undefined4 *)(thisPtr + 0x34),iVar8,&DAT_00d75690);
                local_58 = (float)extraout_ST0_03;
                if (extraout_ST0_03 < (float10)0) {
                  FUN_005f5c20(param_2,targetPos); // Find alternate path
                  iVar8 = FUN_005f5f20(iVar8,&local_18);
                  if (iVar8 != 0) {
                    local_2c = 0;
                    local_28 = 0;
                    bVar4 = true;
                    cVar6 = FUN_005fd340(*(undefined2 *)(iVar8 + 8),0xc2e43267,&local_2c);
                    if (((cVar6 == '\0') || (cVar6 = FUN_006a7fd0(&local_44), cVar6 == '\0')) ||
                       (local_44 == 0)) {
LAB_00863ae4:
                      if (*(char *)(thisPtr + 0x30) != '\0') goto LAB_00863aea;
                    }
                    else {
                      if (*(char *)(thisPtr + 0x30) == '\0') {
                        bVar4 = false;
                        goto LAB_00863ae4;
                      }
LAB_00863aea:
                      cVar6 = FUN_005fd340(*(undefined2 *)(iVar8 + 8),0xf7276be5,&local_2c);
                      if (((cVar6 != '\0') && (cVar6 = FUN_006a7fd0(&local_40), cVar6 != '\0')) &&
                         (local_40 != 0)) goto LAB_00863b61;
                    }
                    if (bVar4) {
                      FUN_004a0b00(local_4c,*(undefined4 *)(thisPtr + 0x34),targetPos,&DAT_00d75690);
                      if ((float10)local_58 < extraout_ST0_04) {
                        bVar5 = true;
                        local_58 = (float)extraout_ST0_04;
                      }
                    }
                  }
LAB_00863b61:
                  if (local_18 != 0) {
                    FUN_004daf90(&local_18);
                  }
                }
                fVar9 = (DAT_00e445a4 - local_58) + local_48;
              }
              if (fVar9 <= *(float *)(thisPtr + 0x20)) {
                if (bVar5) {
                  *(float **)(thisPtr + 0x14) = targetPos;
                  *(int *)(thisPtr + 0xc) = param_2;
                  *(int *)(thisPtr + 0x10) = iVar1;
                  *(int *)(thisPtr + 0x18) = iVar7;
                }
                else {
                  *(int *)(thisPtr + 0x14) = iVar7;
                  *(int *)(thisPtr + 0xc) = iVar1;
                  *(float **)(thisPtr + 0x18) = targetPos;
                  *(int *)(thisPtr + 0x10) = param_2;
                }
                *(undefined8 *)(thisPtr + 0x24) = local_c;
                *(float *)(thisPtr + 0x20) = fVar9;
                *(undefined4 *)(thisPtr + 0x2c) = local_4;
              }
              if (fVar9 <= _DAT_00d5780c) {
                if (local_24[0] != 0) {
                  FUN_004daf90(local_24);
                }
                return 1;
              }
            }
          }
          else if (*(char *)(thisPtr + 0x30) != '\0') {
LAB_008639db:
            cVar6 = FUN_005fd340(*(undefined2 *)(iVar8 + 8),0xf7276be5,&local_34);
            if ((((cVar6 == '\0') || (local_30 == (int *)0x0)) || (local_34 == 0)) ||
               ((*(char *)(local_34 + 6) != '\x02' || (*local_30 == 0)))) goto LAB_00863a10;
          }
          if (local_24[0] == 0) goto LAB_008639b4;
        }
        FUN_004daf90(local_24);
      }
LAB_008639b4:
      local_50 = local_50 + 1;
    } while (local_50 < local_3c);
  }
  return 0; // No path found
}