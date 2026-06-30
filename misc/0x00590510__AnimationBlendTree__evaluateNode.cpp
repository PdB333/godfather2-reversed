// FUNC_NAME: AnimationBlendTree::evaluateNode
float AnimationBlendTree::evaluateNode(int param_1, int *param_2, int *param_3)
{
  undefined4 *puVar1;
  short *psVar2;
  byte *pbVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  float fVar11;
  int local_c;
  
  piVar4 = param_3;
  psVar2 = *(short **)(param_2 + 4);
  iVar5 = (int)*(char *)(param_2 + 1);
  if (0 < iVar5) {
    puVar9 = (undefined4 *)(param_2 + 0xc);
    local_c = iVar5;
    do {
      pbVar3 = (byte *)*puVar9;
      param_3 = DAT_00e2b1a4;
      if ((*pbVar3 & 0x3f) < 0x23) {
        fVar11 = (float)(**(code **)(&DAT_0103b050 + (*pbVar3 & 0x3f) * 4))(param_1,pbVar3,piVar4);
        param_3 = (int *)(float)fVar11;
      }
      uVar7 = (uint)*(short *)(pbVar3 + 2);
      uVar8 = piVar4[1];
      if ((uVar8 <= uVar7) && (iVar10 = (uVar7 - uVar8) + 1, iVar10 != 0)) {
        FUN_005822d0(uVar8 + iVar10);
        iVar6 = piVar4[1];
        iVar10 = iVar6 + iVar10;
        do {
          puVar1 = (undefined4 *)(*piVar4 + iVar6 * 4);
          piVar4[1] = iVar6 + 1;
          if (puVar1 != (undefined4 *)0x0) {
            *puVar1 = 0;
          }
          iVar6 = piVar4[1];
        } while (iVar10 != iVar6);
      }
      puVar9 = puVar9 + 1;
      local_c = local_c + -1;
      *(int **)(*piVar4 + uVar7 * 4) = param_3;
    } while (local_c != 0);
  }
  uVar7 = (uint)*psVar2;
  uVar8 = piVar4[1];
  if ((uVar8 <= uVar7) && (iVar10 = (uVar7 - uVar8) + 1, iVar10 != 0)) {
    FUN_005822d0(uVar8 + iVar10);
    iVar6 = piVar4[1];
    iVar10 = iVar6 + iVar10;
    do {
      puVar9 = (undefined4 *)(*piVar4 + iVar6 * 4);
      piVar4[1] = iVar6 + 1;
      if (puVar9 != (undefined4 *)0x0) {
        *puVar9 = 0;
      }
      iVar6 = piVar4[1];
    } while (iVar10 != iVar6);
  }
  iVar10 = (int)*(float *)(*piVar4 + uVar7 * 4);
  if (iVar10 < 0) {
    iVar10 = 0;
  }
  if (iVar5 <= iVar10) {
    return 1.0f;
  }
  uVar8 = (uint)*(short *)(*(int *)(param_2 + 0xc + iVar10 * 4) + 2);
  if ((uint)piVar4[1] <= uVar8) {
    param_2 = 0;
    FUN_00591c00(&param_2);
  }
  return *(float *)(*piVar4 + uVar8 * 4);
}