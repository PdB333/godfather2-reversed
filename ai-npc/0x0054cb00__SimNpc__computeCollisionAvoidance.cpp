// FUNC_NAME: SimNpc::computeCollisionAvoidance
void __thiscall SimNpc::computeCollisionAvoidance(SimNpc *this)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 *puVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  int local_624;
  byte *local_620;
  int local_61c;
  uint local_618;
  byte local_610 [1548];
  
  if (*(int *)(this + 0x14) < 0x21) { // +0x14 = collision count
    local_620 = local_610;
    iVar9 = 0;
    local_61c = 0;
    local_618 = 0x80000020;
    FUN_00551700(&local_620);
    *(undefined4 *)(this + 0x14) = 0;
    local_624 = 0;
    pbVar5 = local_620;
    iVar8 = local_61c;
    fVar10 = DAT_0103b23c; // some threshold constant
    if (0 < local_61c) {
      do {
        iVar6 = 0;
        if (0 < iVar8) {
          pfVar2 = (float *)(pbVar5 + 0x14); // +0x14 = first agent data
          do {
            if ((((local_624 != iVar6) && (((uint)pfVar2[6] & 0xc0000000) == 0x40000000)) &&
                ((*(uint *)(pbVar5 + iVar9 + 0x2c) & 0xc0000000) != 0x40000000)) &&
               (fVar10 < (pfVar2[-5] * pfVar2[-1] + pfVar2[-3] * pfVar2[1] + pfVar2[-4] * *pfVar2) -
                         (*(float *)(pbVar5 + iVar9 + 8) * pfVar2[1] +
                          *(float *)(pbVar5 + iVar9 + 4) * *pfVar2 +
                         *(float *)(pbVar5 + iVar9) * pfVar2[-1]))) goto LAB_0054cd52;
            iVar6 = iVar6 + 1;
            pfVar2 = pfVar2 + 0xc; // each agent is 0x30 bytes (12 floats)
          } while (iVar6 < iVar8);
        }
        iVar8 = *(int *)(this + 0x1c0); // +0x1c0 = navigation system
        if ((iVar8 != 0) && (iVar6 = 0, 0 < *(int *)(iVar8 + 0x14))) {
          pfVar7 = *(float **)(iVar8 + 0x10);
          pfVar2 = pfVar7 + 5;
          do {
            if (((((uint)pfVar2[6] & 0xc0000000) == 0x40000000) &&
                ((*(uint *)(pbVar5 + iVar9 + 0x2c) & 0xc0000000) != 0x40000000)) &&
               (iVar8 = local_61c,
               fVar10 < (pfVar2[-3] * pfVar2[1] + pfVar2[-4] * *pfVar2 + pfVar2[-1] * *pfVar7) -
                        (*(float *)(pbVar5 + iVar9 + 8) * pfVar2[1] +
                         *(float *)(pbVar5 + iVar9 + 4) * *pfVar2 +
                        *(float *)(pbVar5 + iVar9) * pfVar2[-1]))) goto LAB_0054cd52;
            iVar6 = iVar6 + 1;
            pfVar7 = pfVar7 + 0xc;
            pfVar2 = pfVar2 + 0xc;
          } while (iVar6 < *(int *)(*(int *)(this + 0x1c0) + 0x14));
        }
        puVar3 = (undefined4 *)(pbVar5 + iVar9);
        if (*(uint *)(this + 0x14) == (*(uint *)(this + 0x18) & 0x3fffffff)) {
          FUN_00aa4190((int *)(this + 0x10),0x30); // grow array
          fVar10 = DAT_0103b23c;
        }
        // copy agent data to output buffer
        iVar9 = *(int *)(this + 0x14) * 0x30;
        puVar3 = (undefined4 *)(*(int *)(this + 0x10) + iVar9);
        *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
        *puVar3 = *(undefined4 *)(pbVar5 + iVar9);
        puVar3[1] = *(undefined4 *)(pbVar5 + iVar9 + 4);
        puVar3[2] = *(undefined4 *)(pbVar5 + iVar9 + 8);
        puVar3[3] = *(undefined4 *)(pbVar5 + iVar9 + 0xc);
        puVar3[4] = *(undefined4 *)(pbVar5 + iVar9 + 0x10);
        puVar3[5] = *(undefined4 *)(pbVar5 + iVar9 + 0x14);
        puVar3[6] = *(undefined4 *)(pbVar5 + iVar9 + 0x18);
        puVar3[7] = *(undefined4 *)(pbVar5 + iVar9 + 0x1c);
        puVar3[8] = *(undefined4 *)(pbVar5 + iVar9 + 0x20);
        puVar3[9] = *(undefined4 *)(pbVar5 + iVar9 + 0x24);
        puVar3[10] = *(undefined4 *)(pbVar5 + iVar9 + 0x28);
        puVar3[0xb] = *(undefined4 *)(pbVar5 + iVar9 + 0x2c);
        pbVar5 = local_620;
        iVar8 = local_61c;
LAB_0054cd52:
        local_624 = local_624 + 1;
        iVar9 = iVar9 + 0x30;
      } while (local_624 < iVar8);
    }
    if (-1 < (int)local_618) {
      uVar4 = local_618 & 0x3fffffff;
      TlsGetValue(DAT_01139810);
      FUN_00aa26e0(local_620,uVar4 * 0x30,0x17); // memory deallocation
    }
  }
  return;
}