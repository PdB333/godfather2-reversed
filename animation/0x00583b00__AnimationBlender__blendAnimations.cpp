// FUNC_NAME: AnimationBlender::blendAnimations
int AnimationBlender::blendAnimations(int param_1, int param_2, byte param_3)
{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  float *pfVar14;
  int iVar15;
  float *pfVar16;
  int *_Dst;
  float *pfVar17;
  int *_Src;
  float *pfVar18;
  int *piVar19;
  int iVar20;
  float *pfVar21;
  void *pvVar22;
  int iVar23;
  size_t _Size;
  float *pfVar24;
  uint uVar25;
  int iVar26;
  bool bVar27;
  void *local_3c;
  void *local_38;
  void *local_28;
  void *local_24;
  float *local_20;
  void *local_1c;
  void *local_18;
  float *local_14;
  
  if (((param_1 == 0) || (param_2 == 0)) || (iVar15 = FUN_0056fdd0(), iVar15 == 0)) {
    return 0;
  }
  if ((param_3 & 4) != 0) goto LAB_00584108;
  iVar26 = *(int *)(*(int *)(param_1 + 0x38) + 0xc);
  iVar3 = *(int *)(*(int *)(param_2 + 0x38) + 0xc);
  iVar20 = iVar3;
  if (iVar26 < iVar3) {
    iVar20 = iVar26;
  }
  FUN_0056f800(param_2);
  FUN_0056f800(param_1);
  iVar23 = param_2;
  if (iVar3 <= iVar26) {
    iVar23 = param_1;
  }
  FUN_0056f800(iVar23);
  if (*(int *)(iVar15 + 0x3c) == 0) {
    local_38 = (void *)(*(int *)(param_1 + 0x38) + 0x10);
    local_3c = (void *)(*(int *)(param_1 + 0x34) + 0x14);
    local_18 = (void *)(*(int *)(param_2 + 0x38) + 0x10);
    local_1c = (void *)(*(int *)(param_2 + 0x34) + 0x14);
    local_28 = (void *)(*(int *)(iVar15 + 0x34) + 0x14);
    local_24 = (void *)(*(int *)(iVar15 + 0x38) + 0x10);
    iVar23 = iVar20;
    if ((*(char *)(*(int *)(param_1 + 0x34) + 0x10) == '\0') ||
       (*(char *)(*(int *)(param_2 + 0x34) + 0x10) == '\0')) {
      for (; 0 < iVar23; iVar23 = iVar23 + -1) {
        FUN_00583aa0();
        local_3c = (void *)((int)local_3c + 1);
        local_1c = (void *)((int)local_1c + 1);
        local_28 = (void *)((int)local_28 + 1);
        local_38 = (void *)((int)local_38 + 0x20);
        local_18 = (void *)((int)local_18 + 0x20);
        local_24 = (void *)((int)local_24 + 0x20);
      }
    }
    else {
      FUN_0056f620();
      for (; 0 < iVar23; iVar23 = iVar23 + -1) {
        FUN_00582ea0(&local_28);
        local_3c = (void *)((int)local_3c + 1);
        local_1c = (void *)((int)local_1c + 1);
        local_28 = (void *)((int)local_28 + 1);
        local_38 = (void *)((int)local_38 + 0x20);
        local_18 = (void *)((int)local_18 + 0x20);
        local_24 = (void *)((int)local_24 + 0x20);
      }
    }
    if (iVar20 < iVar26) {
      _memcpy(local_28,local_3c,iVar26 - iVar20);
      _memcpy(local_24,local_38,(iVar26 - iVar20) * 0x20);
    }
    else if (iVar20 < iVar3) {
      _memcpy(local_28,local_1c,iVar3 - iVar20);
      _memcpy(local_24,local_18,(iVar3 - iVar20) * 0x20);
    }
  }
  else {
    local_38 = (void *)(*(int *)(param_1 + 0x38) + 0x10);
    local_3c = (void *)(*(int *)(param_1 + 0x34) + 0x14);
    local_28 = (void *)(*(int *)(param_2 + 0x34) + 0x14);
    local_24 = (void *)(*(int *)(param_2 + 0x38) + 0x10);
    local_20 = (float *)(*(int *)(param_2 + 0x3c) + 0x10);
    pfVar21 = (float *)(*(int *)(param_1 + 0x3c) + 0x10);
    local_1c = (void *)(*(int *)(iVar15 + 0x34) + 0x14);
    local_18 = (void *)(*(int *)(iVar15 + 0x38) + 0x10);
    pfVar24 = (float *)(*(int *)(iVar15 + 0x3c) + 0x10);
    iVar23 = iVar20;
    if ((*(char *)(*(int *)(param_1 + 0x34) + 0x10) == '\0') ||
       (*(char *)(*(int *)(param_2 + 0x34) + 0x10) == '\0')) {
      for (; local_14 = pfVar24, 0 < iVar23; iVar23 = iVar23 + -1) {
        FUN_00586400(&local_28);
        local_20 = local_20 + 4;
        local_3c = (void *)((int)local_3c + 1);
        local_28 = (void *)((int)local_28 + 1);
        local_1c = (void *)((int)local_1c + 1);
        local_38 = (void *)((int)local_38 + 0x20);
        local_24 = (void *)((int)local_24 + 0x20);
        local_18 = (void *)((int)local_18 + 0x20);
        pfVar21 = pfVar21 + 4;
        pfVar24 = local_14 + 4;
      }
    }
    else {
      local_14 = pfVar24;
      FUN_0056f620();
      for (; 0 < iVar23; iVar23 = iVar23 + -1) {
        FUN_00582ea0(&local_1c);
        fVar4 = pfVar21[1];
        fVar5 = pfVar21[2];
        fVar6 = pfVar21[3];
        fVar7 = local_20[1];
        fVar8 = local_20[2];
        fVar9 = local_20[3];
        local_3c = (void *)((int)local_3c + 1);
        local_28 = (void *)((int)local_28 + 1);
        local_1c = (void *)((int)local_1c + 1);
        *local_14 = *pfVar21 * *local_20;
        local_14[1] = fVar4 * fVar7;
        local_14[2] = fVar5 * fVar8;
        local_14[3] = fVar6 * fVar9;
        local_38 = (void *)((int)local_38 + 0x20);
        local_24 = (void *)((int)local_24 + 0x20);
        local_18 = (void *)((int)local_18 + 0x20);
        local_14[3] = DAT_00e2b1a4;
        pfVar21 = pfVar21 + 4;
        local_20 = local_20 + 4;
        pfVar24 = local_14 + 4;
        local_14 = pfVar24;
      }
    }
    if (iVar20 < iVar26) {
      _Size = iVar26 - iVar20;
      _memcpy(local_1c,local_3c,_Size);
      _memcpy(local_18,local_38,_Size * 0x20);
    }
    else {
      if (iVar3 <= iVar20) goto LAB_00583ef3;
      _Size = iVar3 - iVar20;
      _memcpy(local_1c,local_28,_Size);
      _memcpy(local_18,local_24,_Size * 0x20);
      pfVar21 = local_20;
    }
    _memcpy(pfVar24,pfVar21,_Size * 0x10);
  }
LAB_00583ef3:
  if (*(int *)(iVar15 + 0x40) != 0) {
    fVar4 = (*(float **)(iVar15 + 0x40))[3];
    iVar23 = (int)fVar4 >> 2;
    pfVar21 = *(float **)(iVar15 + 0x40);
    pfVar24 = *(float **)(param_1 + 0x40);
    pfVar14 = *(float **)(param_2 + 0x40);
    while( true ) {
      pfVar17 = pfVar14 + 4;
      pfVar16 = pfVar24 + 4;
      pfVar18 = pfVar21 + 4;
      if (iVar23 < 1) break;
      fVar5 = pfVar14[5];
      fVar6 = pfVar14[6];
      fVar7 = pfVar14[7];
      fVar8 = pfVar24[5];
      fVar9 = pfVar24[6];
      fVar10 = pfVar24[7];
      *pfVar18 = *pfVar17 + *pfVar16;
      pfVar21[5] = fVar5 + fVar8;
      pfVar21[6] = fVar6 + fVar9;
      pfVar21[7] = fVar7 + fVar10;
      iVar23 = iVar23 + -1;
      pfVar21 = pfVar18;
      pfVar24 = pfVar16;
      pfVar14 = pfVar17;
    }
    uVar25 = (uint)fVar4 & 3;
    if (3 < uVar25) {
      iVar23 = (uVar25 - 4 >> 2) + 1;
      uVar25 = uVar25 + iVar23 * -4;
      do {
        *pfVar18 = *pfVar17 + *pfVar16;
        pfVar18[1] = pfVar17[1] + pfVar16[1];
        pfVar18[2] = pfVar17[2] + pfVar16[2];
        pfVar18[3] = pfVar17[3] + pfVar16[3];
        pfVar16 = pfVar16 + 4;
        pfVar17 = pfVar17 + 4;
        pfVar18 = pfVar18 + 4;
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
    }
    for (; 0 < (int)uVar25; uVar25 = uVar25 - 1) {
      *pfVar18 = *pfVar17 + *pfVar16;
      pfVar16 = pfVar16 + 1;
      pfVar17 = pfVar17 + 1;
      pfVar18 = pfVar18 + 1;
    }
  }
  if (*(int *)(iVar15 + 0x44) != 0) {
    piVar19 = (int *)(*(int *)(param_1 + 0x44) + 0x10);
    _Src = (int *)(*(int *)(param_2 + 0x44) + 0x10);
    _Dst = (int *)(*(int *)(iVar15 + 0x44) + 0x10);
    iVar23 = iVar20;
    if (3 < iVar20) {
      local_28 = (void *)((iVar20 - 4U >> 2) + 1);
      iVar23 = iVar20 + (int)local_28 * -4;
      pvVar22 = local_28;
      do {
        if (*_Src == -1) {
          *_Dst = *piVar19;
          iVar2 = piVar19[1];
        }
        else {
          *_Dst = *_Src;
          iVar2 = _Src[1];
        }
        _Dst[1] = iVar2;
        if (_Src[2] == -1) {
          _Dst[2] = piVar19[2];
          iVar2 = piVar19[3];
        }
        else {
          _Dst[2] = _Src[2];
          iVar2 = _Src[3];
        }
        _Dst[3] = iVar2;
        if (_Src[4] == -1) {
          _Dst[4] = piVar19[4];
          iVar2 = piVar19[5];
        }
        else {
          _Dst[4] = _Src[4];
          iVar2 = _Src[5];
        }
        _Dst[5] = iVar2;
        if (_Src[6] == -1) {
          _Dst[6] = piVar19[6];
          iVar2 = piVar19[7];
        }
        else {
          _Dst[6] = _Src[6];
          iVar2 = _Src[7];
        }
        _Dst[7] = iVar2;
        piVar19 = piVar19 + 8;
        _Src = _Src + 8;
        _Dst = _Dst + 8;
        pvVar22 = (void *)((int)pvVar22 + -1);
      } while (pvVar22 != (void *)0x0);
    }
    for (; 0 < iVar23; iVar23 = iVar23 + -1) {
      if (*_Src == -1) {
        *_Dst = *piVar19;
        iVar2 = piVar19[1];
      }
      else {
        *_Dst = *_Src;
        iVar2 = _Src[1];
      }
      _Dst[1] = iVar2;
      piVar19 = piVar19 + 2;
      _Src = _Src + 2;
      _Dst = _Dst + 2;
    }
    if (iVar20 < iVar26) {
      iVar26 = iVar26 - iVar20;
      _Src = piVar19;
    }
    else {
      if (iVar3 <= iVar20) goto LAB_00584108;
      iVar26 = iVar3 - iVar20;
    }
    _memcpy(_Dst,_Src,iVar26 * 8);
  }
LAB_00584108:
  if ((param_3 & 8) != 0) {
    return iVar15;
  }
  bVar27 = *(char *)(param_2 + 0x30) != '\x02';
  puVar1 = (undefined4 *)(iVar15 + 0x10);
  if (*(char *)(param_1 + 0x30) == '\x02') {
    *(undefined1 *)(iVar15 + 0x30) = 2;
    if (bVar27) {
      uVar11 = *(undefined4 *)(param_1 + 0x14);
      uVar12 = *(undefined4 *)(param_1 + 0x18);
      uVar13 = *(undefined4 *)(param_1 + 0x1c);
      *puVar1 = *(undefined4 *)(param_1 + 0x10);
      *(undefined4 *)(iVar15 + 0x14) = uVar11;
      *(undefined4 *)(iVar15 + 0x18) = uVar12;
      *(undefined4 *)(iVar15 + 0x1c) = uVar13;
      uVar11 = *(undefined4 *)(param_1 + 0x24);
      uVar12 = *(undefined4 *)(param_1 + 0x28);
      uVar13 = *(undefined4 *)(param_1 + 0x2c);
      *(undefined4 *)(iVar15 + 0x20) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(iVar15 + 0x24) = uVar11;
      *(undefined4 *)(iVar15 + 0x28) = uVar12;
      *(undefined4 *)(iVar15 + 0x2c) = uVar13;
      return iVar15;
    }
    FUN_0056cba0((undefined4 *)(param_1 + 0x10),(undefined4 *)(param_2 + 0x10),puVar1);
    fVar4 = *(float *)(param_1 + 0x24);
    fVar5 = *(float *)(param_1 + 0x28);
    fVar6 = *(float *)(param_1 + 0x2c);
    fVar7 = *(float *)(param_2 + 0x24);
    fVar8 = *(float *)(param_2 + 0x28);
    fVar9 = *(float *)(param_2 + 0x2c);
    *(float *)(iVar15 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_2 + 0x20);
    *(float *)(iVar15 + 0x24) = fVar4 + fVar7;
    *(float *)(iVar15 + 0x28) = fVar5 + fVar8;
    *(float *)(iVar15 + 0x2c) = fVar6 + fVar9;
    *(float *)(iVar15 + 0x2c) = DAT_00e2b1a4;
    return iVar15;
  }
  if (bVar27) {
    *(undefined1 *)(iVar15 + 0x30) = 0;
    return iVar15;
  }
  *(undefined1 *)(iVar15 + 0x30) = 2;
  uVar11 = *(undefined4 *)(param_2 + 0x14);
  uVar12 = *(undefined4 *)(param_2 + 0x18);
  uVar13 = *(undefined4 *)(param_2 + 0x1c);
  *puVar1 = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(iVar15 + 0x14) = uVar11;
  *(undefined4 *)(iVar15 + 0x18) = uVar12;
  *(undefined4 *)(iVar15 + 0x1c) = uVar13;
  uVar11 = *(undefined4 *)(param_2 + 0x24);
  uVar12 = *(undefined4 *)(param_2 + 0x28);
  uVar13 = *(undefined4 *)(param_2 + 0x2c);
  *(undefined4 *)(iVar15 + 0x20) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(iVar15 + 0x24) = uVar11;
  *(undefined4 *)(iVar15 + 0x28) = uVar12;
  *(undefined4 *)(iVar15 + 0x2c) = uVar13;
  return iVar15;
}