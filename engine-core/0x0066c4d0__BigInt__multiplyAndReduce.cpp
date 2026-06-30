// FUNC_NAME: BigInt::multiplyAndReduce
undefined4 FUN_0066c4d0(int *param_1,int *param_2,undefined8 *param_3,int param_4)

{
  int iVar1;
  longlong lVar2;
  int iVar3;
  undefined4 uVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar10;
  size_t _Size;
  uint *puVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined8 uVar14;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined8 local_14;
  undefined8 local_c;
  
  iVar13 = *param_2;
  iVar3 = *param_1;
  uVar10 = iVar13 + 1 + iVar3;
  if ((int)uVar10 < 0x200) {
    if (iVar13 <= iVar3) {
      iVar3 = iVar13;
    }
    if (iVar3 < 0x100) {
      uVar4 = FUN_00665340(param_1,param_2,param_3,param_4);
      return uVar4;
    }
  }
  uVar8 = uVar10 & 0x8000003f;
  if ((int)uVar8 < 0) {
    uVar8 = (uVar8 - 1 | 0xffffffc0) + 1;
  }
  _Size = uVar10 + (0x80 - uVar8);
  pvVar5 = _calloc(4,_Size);
  if (pvVar5 == (void *)0x0) {
    return 0xfffffffe;
  }
  iVar3 = *param_1;
  iVar1 = *param_2;
  iVar13 = iVar1 + 1 + iVar3;
  local_2c = 0;
  if (0 < iVar3) {
    local_34 = param_4 * 4;
    puVar9 = (uint *)((int)pvVar5 + local_34);
    local_28 = param_4;
    do {
      uVar4 = *(undefined4 *)(param_1[3] + local_2c * 4);
      puVar12 = (undefined4 *)(param_2[3] + local_34);
      uVar10 = 0;
      puVar11 = puVar9;
      if (local_28 < iVar1) {
        local_30 = iVar1 - local_28;
        do {
          uVar14 = __allmul(*puVar12,0,uVar4,0);
          uVar8 = (uint)uVar14 + *puVar11;
          uVar6 = uVar8 + uVar10;
          uVar10 = uVar6 >> 0x1c | ((int)((ulonglong)uVar14 >> 0x20) + (uint)CARRY4((uint)uVar14,*puVar11) + (uint)CARRY4(uVar8,uVar10)) * 0x10;
          *puVar11 = uVar6 & 0xfffffff;
          puVar12 = puVar12 + 1;
          puVar11 = puVar11 + 1;
          local_30 = local_30 + -1;
        } while (local_30 != 0);
      }
      local_34 = local_34 + -4;
      local_2c = local_2c + 1;
      local_28 = local_28 + -1;
      *puVar11 = uVar10;
    } while (local_2c < iVar3);
  }
  if (0 < iVar13) {
    piVar7 = (int *)((int)pvVar5 + iVar13 * 4 + -4);
    do {
      if (*piVar7 != 0) break;
      iVar13 = iVar13 + -1;
      piVar7 = piVar7 + -1;
    } while (0 < iVar13);
  }
  local_14 = CONCAT44(_Size,iVar13);
  local_c = ZEXT48(pvVar5) << 0x20;
  lVar2 = local_c;
  uVar14 = *param_3;
  local_c._4_4_ = (void *)((ulonglong)param_3[1] >> 0x20);
  *param_3 = local_14;
  param_3[1] = lVar2;
  if (local_c._4_4_ != (void *)0x0) {
    local_14._0_4_ = (int)uVar14;
    _memset(local_c._4_4_,0,(int)local_14 * 4);
    _free(local_c._4_4_);
  }
  return 0;
}