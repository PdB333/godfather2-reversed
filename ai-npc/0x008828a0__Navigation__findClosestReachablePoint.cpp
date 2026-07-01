// FUNC_NAME: Navigation::findClosestReachablePoint
uint __thiscall Navigation::findClosestReachablePoint(int param_1, int param_2, int param_3, undefined4 param_4)
{
  float fVar1;
  byte bVar2;
  uint uVar3;
  undefined2 extraout_var;
  uint uVar4;
  uint uVar5;
  float10 fVar6;
  int local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 uStack_8;
  uint local_4;
  
  bVar2 = *(byte *)(param_3 + 0x14); // +0x14: number of direct neighbors
  uVar4 = 0;
  if (bVar2 != 0) {
    do {
      fVar6 = (float10)FUN_0084cb90(param_4, param_3,
                                    *(int *)(param_2 + 0x20) + // +0x20: neighbor array base
                                    (uint)*(ushort *)
                                           ((uint)(ushort)(*(short *)(param_3 + 0x10) + (short)uVar4 // +0x10: neighbor offset array
                                                          ) * 0x10 + 4 + *(int *)(param_2 + 0x24)) * // +0x24: neighbor data stride
                                    0x24, &local_18, 1);
      if ((*(float *)(param_1 + 0x14) == DAT_00d5ccf8) || // +0x14: best distance (initialized to INF)
         ((float)fVar6 < *(float *)(param_1 + 0x14))) {
        *(int *)(param_1 + 8) = local_18; // +0x08: best point position x
        *(undefined4 *)(param_1 + 0xc) = uStack_14; // +0x0C: best point position y
        *(undefined4 *)(param_1 + 0x10) = local_10; // +0x10: best point position z
        *(float *)(param_1 + 0x14) = (float)fVar6; // +0x14: best distance
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < bVar2);
  }
  uVar3 = (uint)*(byte *)(param_3 + 0x1c) + (uint)*(byte *)(param_3 + 0x15); // +0x1C: number of indirect neighbors, +0x15: number of direct neighbors (again?)
  uVar4 = uVar3;
  if (uVar3 != 0) {
    uVar5 = 0;
    do {
      uVar4 = FUN_005fd1c0(&local_18,
                           (uint)(ushort)(*(short *)(param_3 + 0x16) + (short)uVar5) * 0x10 + // +0x16: indirect neighbor offset array
                           *(int *)(param_2 + 0x30)); // +0x30: indirect neighbor data base
      if (local_18 != 0) {
        fVar6 = (float10)FUN_0084cb90(param_4, param_3, local_10, &local_c, 1);
        fVar1 = *(float *)(param_1 + 0x14);
        if ((fVar1 == DAT_00d5ccf8) ||
           (uVar4 = (uint)CONCAT21(extraout_var,
                                   (fVar1 == DAT_00d5ccf8) << 6 |
                                   (NAN(fVar1) || NAN(DAT_00d5ccf8)) << 2 | 2U |
                                   fVar1 < DAT_00d5ccf8) << 8, (float)fVar6 < fVar1)) {
          *(undefined4 *)(param_1 + 8) = local_c; // +0x08: best point position x
          *(undefined4 *)(param_1 + 0xc) = uStack_8; // +0x0C: best point position y
          *(uint *)(param_1 + 0x10) = local_4; // +0x10: best point position z
          *(float *)(param_1 + 0x14) = (float)fVar6; // +0x14: best distance
          uVar4 = local_4;
        }
        if (local_18 != 0) {
          uVar4 = FUN_004daf90(&local_18); // release temporary object
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar3);
  }
  return uVar4 & 0xffffff00;
}