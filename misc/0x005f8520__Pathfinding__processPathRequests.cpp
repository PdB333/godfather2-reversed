// FUNC_NAME: Pathfinding::processPathRequests
void Pathfinding::processPathRequests(int param_1, uint param_2)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  bool bVar10;
  int *local_4c;
  int local_48;
  undefined4 local_44;
  int local_40;
  uint local_3c;
  float local_30;
  uint local_2c;
  float fStack_28;
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  int iStack_14;
  int iStack_10;
  
  local_3c = 0;
  if ((*(byte *)(param_1 + 0x20) & 1) != 0) {
    param_2 = 0xffffffff;
  }
  local_18 = DAT_01223520;
  if (*(int *)(param_1 + 8) == 0) {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 0x204;
    local_44 = 0;
  }
  else {
    local_44 = *(undefined4 *)(param_1 + 0x10);
  }
  local_24 = *(int *)(param_1 + 0x14);
  if (local_24 == 0) {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 0x404;
    local_48 = 0;
  }
  else {
    local_48 = *(int *)(param_1 + 0x1c);
  }
  local_4c = *(int **)(param_1 + 0x30);
  if ((*(int *)(param_1 + 0x38) == 0) && (local_4c == (int *)0x0)) {
    local_4c = (int *)FUN_005f8370(param_1,*(int *)(param_1 + 8),local_44,local_24,local_48);
  }
  if (*(int *)(param_1 + 0x38) == 0) {
    if (((local_4c != (int *)0x0) && (*(int *)(param_1 + 0x28) == 0)) &&
       (iVar6 = FUN_005f8300(local_44), iVar6 != 0)) {
      FUN_005f8a90();
    }
    if (*(int *)(param_1 + 0x38) == 0) {
      do {
        if ((*local_4c == 0) || (param_2 <= local_3c)) break;
        local_3c = local_3c + 1;
        iVar7 = FUN_005f8e30(&local_1c);
        bVar5 = *(byte *)(iVar7 + 0xb);
        iVar6 = *(int *)(*(int *)(param_1 + 0x24) + (uint)bVar5 * 0xc);
        piVar8 = (int *)(*(int *)(param_1 + 0x24) + (uint)bVar5 * 0xc);
        if (iVar6 != 0) {
          iVar1 = *(int *)(iVar6 + 0x20) + ((iVar7 - piVar8[2]) / 0xc) * 0x24;
          *(int *)(param_1 + 0x34) = iVar7;
          if ((iVar1 == local_48) && (iVar6 == local_24)) {
            *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 1;
          }
          else if (*(float *)(iVar7 + 4) <= *(float *)(param_1 + 0x3c)) {
            local_20 = (uint)*(byte *)(iVar1 + 0x14);
            iVar2 = *(int *)(param_1 + 0x38);
            for (local_2c = 0; (iVar2 == 0 && ((int)local_2c < (int)local_20));
                local_2c = local_2c + 1) {
              pfVar9 = (float *)((uint)(ushort)(*(short *)(iVar1 + 0x10) + (short)local_2c) * 0x10 +
                                *(int *)(iVar6 + 0x24));
              local_30 = 0.0;
              if (*(int **)(param_1 + 0x44) == (int *)0x0) {
                cVar4 = (*(uint *)(param_1 + 0x4c) & (uint)*(ushort *)((int)pfVar9 + 10)) == 0;
              }
              else {
                cVar4 = (**(code **)(**(int **)(param_1 + 0x44) + 4))(pfVar9,iVar6,&local_30);
              }
              if (cVar4 != '\0') {
                iVar2 = *(int *)(iVar6 + 0x20) + (uint)*(ushort *)(pfVar9 + 1) * 0x24;
                if ((*(int **)(param_1 + 0x44) == (int *)0x0) || (iVar2 == 0)) {
                  if ((*(ushort *)(param_1 + 0x48) & *(ushort *)(iVar2 + 0x18)) != 0) {
                    bVar10 = (*(uint *)(param_1 + 0x20) & 0x800) == 0;
                    goto LAB_005f875e;
                  }
                }
                else {
                  cVar4 = (**(code **)(**(int **)(param_1 + 0x44) + 0xc))(iVar2,iVar6);
                  bVar10 = cVar4 == '\0';
LAB_005f875e:
                  if (bVar10) goto LAB_005f87bc;
                }
                iVar2 = piVar8[2] + ((iVar2 - *(int *)(*piVar8 + 0x20)) / 0x24) * 0xc;
                *(byte *)(iVar2 + 0xb) = bVar5;
                cVar4 = FUN_005f80d0(iVar7,iVar2,*pfVar9 + local_30,local_4c);
                if (cVar4 == '\0') {
                  *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 0x24;
                }
              }
LAB_005f87bc:
              iVar2 = *(int *)(param_1 + 0x38);
            }
            if ((*(byte *)(param_1 + 0x20) & 4) == 0) {
              local_20 = (uint)*(byte *)(iVar1 + 0x1c) + (uint)*(byte *)(iVar1 + 0x15);
              iVar2 = *(int *)(param_1 + 0x38);
              for (local_2c = 0; (iVar2 == 0 && (local_2c < local_20)); local_2c = local_2c + 1) {
                pfVar9 = (float *)((uint)(ushort)(*(short *)(iVar1 + 0x16) + (short)local_2c) * 0x10
                                  + *(int *)(iVar6 + 0x30));
                fStack_28 = 0.0;
                if (*(int **)(param_1 + 0x44) == (int *)0x0) {
                  cVar4 = (*(uint *)(param_1 + 0x4c) & (uint)*(ushort *)((int)pfVar9 + 10)) == 0;
                }
                else {
                  cVar4 = (**(code **)(**(int **)(param_1 + 0x44) + 8))(pfVar9,iVar6,&fStack_28);
                }
                if (cVar4 != '\0') {
                  piVar8 = (int *)FUN_005fd1c0(&iStack_14,pfVar9);
                  local_1c = *piVar8;
                  if (local_1c == 0) {
                    local_40 = 0;
                  }
                  else {
                    local_40 = piVar8[2];
                  }
                  if (iStack_14 != 0) {
                    piVar8 = *(int **)(iStack_14 + 4);
                    if (piVar8 == &iStack_14) {
                      *(int *)(iStack_14 + 4) = iStack_10;
                    }
                    else {
                      if ((int *)piVar8[1] != &iStack_14) {
                        do {
                          piVar8 = (int *)piVar8[1];
                        } while ((int *)piVar8[1] != &iStack_14);
                      }
                      piVar8[1] = iStack_10;
                    }
                  }
                  if ((local_1c != 0) &&
                     (((((*(ushort *)(param_1 + 0x48) & *(ushort *)(local_40 + 0x18)) == 0 ||
                        ((*(uint *)(param_1 + 0x20) & 0x800) != 0)) &&
                       (bVar5 = FUN_005f6710(), bVar5 != 0xff)) &&
                      (piVar8 = (int *)(*(int *)(param_1 + 0x24) + (uint)bVar5 * 0xc),
                      piVar8 != (int *)0x0)))) {
                    iVar2 = piVar8[2] + ((local_40 - *(int *)(*piVar8 + 0x20)) / 0x24) * 0xc;
                    *(byte *)(iVar2 + 0xb) = bVar5;
                    cVar4 = FUN_005f80d0(iVar7,iVar2,*pfVar9 + fStack_28,local_4c);
                    if (cVar4 == '\0') {
                      *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 0x24;
                    }
                  }
                }
                iVar2 = *(int *)(param_1 + 0x38);
              }
            }
          }
        }
        *(byte *)(iVar7 + 10) = *(byte *)(iVar7 + 10) | 2;
      } while (*(int *)(param_1 + 0x38) == 0);
      if (*(int *)(param_1 + 0x38) == 0) {
        if ((local_4c != (int *)0x0) && (*local_4c == 0)) {
          *(undefined4 *)(param_1 + 0x38) = 2;
        }
        if (*(int *)(param_1 + 0x38) == 0) goto LAB_005f8a03;
      }
    }
  }
  if (local_4c != (int *)0x0) {
    *local_4c = 0;
    puVar3 = *(undefined4 **)(local_18 + 0x30);
    piVar8 = (int *)*puVar3;
    if (piVar8 != (int *)0x0) {
      if (((int *)puVar3[7] == (int *)0x0) ||
         ((piVar8 <= local_4c && (local_4c < (int *)(puVar3[1] + (int)piVar8))))) {
        *local_4c = puVar3[2];
        puVar3[5] = puVar3[5] + 1;
        puVar3[2] = local_4c;
      }
      else {
        (**(code **)(*(int *)puVar3[7] + 8))(local_4c);
      }
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
LAB_005f8a03:
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + local_3c;
  return;
}