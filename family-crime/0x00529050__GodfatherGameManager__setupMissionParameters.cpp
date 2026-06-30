// FUNC_NAME: GodfatherGameManager::setupMissionParameters
void GodfatherGameManager::setupMissionParameters(int param_1, int param_2)

{
  float fVar1;
  bool bVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  uint uVar10;
  float *pfVar11;
  uint uVar12;
  int iVar13;
  bool bVar14;
  float fVar15;
  uint local_28;
  uint local_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  fVar6 = DAT_00e35654;
  fVar4 = DAT_00e2e780;
  iVar9 = 0;
  bVar14 = false;
  bVar2 = true;
  local_28 = 0;
  local_24 = 0;
  if (0 < param_2) {
    pfVar11 = (float *)(param_1 + 0xc);
    do {
      if (fVar4 <= *pfVar11) {
        bVar14 = true;
      }
      if (((uint)pfVar11[2] & 1) == 0) {
        local_28 = local_28 | 1 << ((byte)iVar9 & 0x1f);
      }
      if (((uint)pfVar11[2] & 2) != 0) {
        local_24 = local_24 | 1 << ((byte)iVar9 & 0x1f);
      }
      if (pfVar11[1] != *(float *)(param_1 + 0x10)) {
        bVar2 = false;
      }
      fVar1 = *pfVar11;
      fVar15 = *pfVar11 * fVar6;
      pfVar11[-3] = fVar15 * pfVar11[-3];
      pfVar11[-2] = fVar15 * pfVar11[-2];
      pfVar11[-1] = fVar15 * pfVar11[-1];
      *pfVar11 = fVar15 * *pfVar11;
      *pfVar11 = fVar1;
      if (pfVar11[3] == 0.0) {
        *pfVar11 = 0.0;
      }
      else {
        *pfVar11 = fVar15;
      }
      iVar9 = iVar9 + 1;
      pfVar11 = pfVar11 + 8;
    } while (iVar9 < param_2);
    if (bVar14) {
      if (param_2 < 4) {
        puVar7 = (undefined4 *)(param_2 * 0x20 + 0x10 + param_1);
        iVar9 = 4 - param_2;
        do {
          puVar7[-1] = 0;
          *puVar7 = 0;
          puVar7[1] = 1;
          puVar7 = puVar7 + 8;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      iVar9 = 0;
      uVar12 = DAT_011f3910;
      do {
        if ((iVar9 == 4) && (uVar12 != 0)) {
          if (uVar12 < 0x1000) {
            puVar8 = &DAT_011a0f28 + uVar12 * 0x38;
          }
          else {
            puVar8 = (undefined1 *)0x0;
          }
          FUN_00606830(uVar12,puVar8);
          uVar12 = DAT_011f3910;
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < 5);
      if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
      }
      if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
      }
      _DAT_011f3a30 = 1;
      if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
      }
      if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
      }
      _DAT_011f39f4 = 0;
      if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
      }
      if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
      }
      _DAT_011f3a10 = 0;
      if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
      }
      if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
      }
      _DAT_011f3a3c = 5;
      if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
      }
      if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
      }
      _DAT_011f3a38 = 0;
      if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
      }
      if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
      }
      _DAT_011f3a14 = 0;
      if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
      }
      if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
      }
      _DAT_011f3a44 = 1;
      FUN_00417cf0(1,2,1);
      uVar12 = DAT_01218ea8;
      uVar10 = 0;
      do {
        if ((&DAT_01218e50)[uVar10 * 2] == DAT_01218ea8) {
          if (uVar10 < 0x14) {
            (&DAT_01218e54)[uVar10 * 2] = (&DAT_01218e54)[uVar10 * 2] & 0xfffffffc;
          }
          break;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < 0x14);
      uVar3 = DAT_011f38f4;
      iVar9 = DAT_011f38f0;
      DAT_011f38f0 = uVar12;
      DAT_011f38f4 = 0;
      FUN_00609340(0,iVar9,uVar3);
      iVar9 = DAT_011f3914;
      bVar14 = DAT_011f3910 != 0;
      DAT_011f3910 = 0;
      DAT_011f3914 = 0;
      if ((bVar14) || (iVar9 != 0)) {
        (**(code **)(*DAT_01205750 + 0x9c))(DAT_01205750,0);
      }
      FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
      if ((DAT_01218ea0 != 0xffffffff) && (DAT_01218ea0 < 0x1000)) {
        iVar9 = DAT_01218ea0 * 0x38;
        if ((&DAT_011a0f28 + iVar9 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar9] < 4)) {
          if (*(int *)(&DAT_011a0f44 + iVar9) != 0) {
            FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar9),0x110000);
          }
          *(uint *)(&DAT_011a0f34 + iVar9) =
               *(uint *)(&DAT_011a0f34 + iVar9) & 0xfc9d8fff | 0x110000;
          FUN_006189c0();
        }
      }
      DAT_01125ba0 = DAT_01219908;
      DAT_01125d78 = -1;
      DAT_01125ba4 = DAT_01125d74;
      if (DAT_012058e8 == &PTR_PTR_01125b90) {
        FUN_0060a460(DAT_01125d74);
        FUN_0060a460(DAT_01125ba0);
      }
      FUN_00612a60();
      if ((DAT_01125ba0 == DAT_01219908) && (DAT_01219928 != 0)) {
        fStack_20 = 0.0;
        fStack_1c = 0.0;
        fStack_18 = 0.0;
        fStack_14 = 0.0;
        FUN_0060add0(DAT_01125ba0,DAT_01219928,&fStack_20);
      }
      FUN_0053ce90();
      puVar7 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
      uVar5 = DAT_00e2eff4;
      uVar3 = DAT_00e2b1a4;
      if (puVar7 != (undefined4 *)0x0) {
        *puVar7 = DAT_00e2eff4;
        puVar7[1] = uVar5;
        puVar7[2] = uVar3;
        puVar7[3] = uVar5;
        puVar7[4] = uVar3;
        puVar7[5] = uVar3;
        puVar7[6] = uVar5;
        puVar7[7] = uVar3;
        FUN_0060cde0();
      }
      if (DAT_01125c30 != 0) {
        uVar12 = DAT_01125c30 & 0xff;
        if ((&DAT_011eb8fc)[DAT_01125ba4 * 0x10] != '\\0') {
          uVar12 = uVar12 + 0x10;
        }
        FUN_00618d40();
        (&DAT_011d912c)[uVar12] = 0;
      }
      DAT_012058e8 = (undefined **)0x0;
      DAT_012058f0 = 0;
      DAT_01125ba0 = 0;
      DAT_01125ba4 = 0;
      iVar9 = 0;
      do {
        if ((iVar9 != 4) && (uVar12 = (&DAT_011f38f0)[iVar9 * 2], uVar12 != 0)) {
          if (uVar12 < 0x1000) {
            puVar8 = &DAT_011a0f28 + uVar12 * 0x38;
          }
          else {
            puVar8 = (undefined1 *)0x0;
          }
          FUN_00606830(uVar12,puVar8);
        }
        uVar12 = DAT_01218ea8;
        iVar9 = iVar9 + 1;
      } while (iVar9 < 5);
      if (DAT_012058d4 < 0xa8) {
        DAT_012058d4 = 0xa8;
      }
      if (0xa7 < DAT_00f1598c) {
        DAT_00f1598c = 0xa8;
      }
      _DAT_011f3c78 = 0xf;
      if (DAT_012058d4 < 0xbe) {
        DAT_012058d4 = 0xbe;
      }
      if (0xbd < DAT_00f1598c) {
        DAT_00f1598c = 0xbe;
      }
      _DAT_011f3cd0 = 0xf;
      if (local_28 != 0) {
        FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
        if ((uVar12 != 0xffffffff) && (uVar12 < 0x1000)) {
          iVar9 = uVar12 * 0x38;
          if ((&DAT_011a0f28 + iVar9 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar9] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar9) != 0) {
              FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar9),0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar9) =
                 *(uint *)(&DAT_011a0f34 + iVar9) & 0xfc9c8fff | 0x100000;
            FUN_006189c0();
          }
        }
        FUN_0053c6f0();
        FUN_00612a60();
        if (((DAT_0121bc20 == DAT_01219900) && (iVar9 = DAT_01219924, DAT_01219924 != 0)) ||
           ((DAT_0121bc20 == DAT_01198e74 && (iVar9 = DAT_0121be80, DAT_0121be80 != 0)))) {
          FUN_0060add0(DAT_0121bc20,iVar9,&DAT_011f6680);
        }
        if (*DAT_0121be7c != 0) {
          FUN_006063b0();
        }
        if (uVar12 < 0x1000) {
          puVar8 = &DAT_011a0f28 + uVar12 * 0x38;
        }
        else {
          puVar8 = (undefined1 *)0x0;
        }
        fStack_20 = DAT_00e2b198 / (float)*(ushort *)(puVar8 + 2);
        if (uVar12 < 0x1000) {
          puVar8 = &DAT_011a0f28 + uVar12 * 0x38;
        }
        else {
          puVar8 = (undefined1 *)0x0;
        }
        fStack_1c = DAT_00e2b198 / (float)*(ushort *)(puVar8 + 4);
        fStack_14 = DAT_00e44564 - fStack_1c;
        fStack_18 = fStack_20;
        if (DAT_0121be7c[7] != 0) {
          FUN_0060add0(DAT_0121bc24,DAT_0121be7c[7],&fStack_20);
        }
        FUN_00417f50(local_28);
        puVar7 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
        uVar5 = DAT_00e2eff4;
        uVar3 = DAT_00e2b1a4;
        if (puVar7 != (undefined4 *)0x0) {
          *puVar7 = DAT_00e2eff4;
          puVar7[1] = uVar3;
          puVar7[2] = 0;
          puVar7[3] = 0;
          puVar7[4] = uVar3;
          puVar7[5] = uVar3;
          puVar7[6] = uVar3;
          puVar7[7] = 0;
          puVar7[8] = uVar3;
          puVar7[9] = uVar5;
          puVar7[10] = uVar3;
          puVar7[0xb] = uVar3;
          puVar7[0xc] = uVar5;
          puVar7[0xd] = uVar5;
          puVar7[0xe] = 0;
          puVar7[0xf] = uVar3;
          FUN_0060cde0();
        }
        if (DAT_0121bcb0 != 0) {
          uVar10 = DAT_0121bcb0 & 0xff;
          if ((&DAT_011eb8fc)[DAT_0121bc24 * 0x10] != '\\0') {
            uVar10 = uVar10 + 0x10;
          }
          FUN_00618d40();
          (&DAT_011d912c)[uVar10] = 0;
        }
        DAT_012058e8 = (undefined **)0x0;
        DAT_012058f0 = 0;
        DAT_0121bc20 = 0;
        DAT_0121bc24 = 0;
        if (local_24 != 0) {
          FUN_00417f50(local_24);
          FUN_00417cf0(3,2,2);
          DAT_01219954 = DAT_012198fc;
          DAT_01219950 = DAT_01219900;
          _DAT_01219a6c = 4;
          FUN_00530a60();
          if ((uVar12 != 0xffffffff) && (uVar12 < 0x1000)) {
            iVar9 = uVar12 * 0x38;
            if ((&DAT_011a0f28 + iVar9 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar9] < 4)) {
              if (*(int *)(&DAT_011a0f44 + iVar9) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar9),0x110000);
              }
              *(uint *)(&DAT_011a0f34 + iVar9) =
                   *(uint *)(&DAT_011a0f34 + iVar9) & 0xfc9d8fff | 0x110000;
              FUN_006189c0();
            }
          }
          FUN_00530df0();
          puVar7 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
          uVar5 = DAT_00e2eff4;
          uVar3 = DAT_00e2b1a4;
          if (puVar7 != (undefined4 *)0x0) {
            *puVar7 = DAT_00e2eff4;
            puVar7[1] = uVar3;
            puVar7[2] = 0;
            puVar7[3] = 0;
            puVar7[4] = uVar3;
            puVar7[5] = uVar3;
            puVar7[6] = uVar3;
            puVar7[7] = 0;
            puVar7[8] = uVar3;
            puVar7[9] = uVar5;
            puVar7[10] = uVar3;
            puVar7[0xb] = uVar3;
            puVar7[0xc] = uVar5;
            puVar7[0xd] = uVar5;
            puVar7[0xe] = 0;
            puVar7[0xf] = uVar3;
            FUN_0060cde0();
          }
          if (DAT_012199e0 != 0) {
            uVar12 = DAT_012199e0 & 0xff;
            if ((&DAT_011eb8fc)[DAT_01219954 * 0x10] != '\\0') {
              uVar12 = uVar12 + 0x10;
            }
            FUN_00618d40();
            (&DAT_011d912c)[uVar12] = 0;
          }
          DAT_01219950 = 0;
          DAT_01219954 = 0;
          _DAT_012199e4 = 0;
          _DAT_012199e8 = 0;
        }
        DAT_012058f0 = 0;
        DAT_012058e8 = (undefined **)0x0;
        FUN_00609890(1);
        if (DAT_012058d4 < 0xa8) {
          DAT_012058d4 = 0xa8;
        }
        if (0xa7 < DAT_00f1598c) {
          DAT_00f1598c = 0xa8;
        }
        if (DAT_012058d4 < 0xbe) {
          DAT_012058d4 = 0xbe;
        }
        uVar12 = DAT_011f38f0;
        if (0xbd < DAT_00f1598c) {
          DAT_00f1598c = 0xbe;
        }
      }
      _DAT_011f3cd0 = 0xf;
      _DAT_011f3c78 = 0xf;
      iVar9 = DAT_012058a4;
      if (DAT_012054dc != 0) {
        iVar9 = *(int *)(DAT_012054dc + 0x16c);
      }
      uVar10 = 0;
      do {
        if ((&DAT_01218e50)[uVar10 * 2] == iVar9) {
          if (uVar10 < 0x14) {
            (&DAT_01218e54)[uVar10 * 2] = (&DAT_01218e54)[uVar10 * 2] & 0xfffffffc;
          }
          break;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < 0x14);
      uVar3 = DAT_011f38f4;
      uVar10 = DAT_011f38f0;
      DAT_011f38f4 = 0;
      DAT_011f38f0 = iVar9;
      FUN_00609340(0,uVar10,uVar3);
      FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
      if (DAT_012234d4 == '\\0') {
        if (DAT_012058d0 < 0x16) {
          DAT_012058d0 = 0x16;
        }
        if (0x16 < DAT_00f15988) {
          DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 1;
        if (DAT_012058d0 < 7) {
          DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
          DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 0;
        if (DAT_012058d0 < 0x19) {
          DAT_012058d0 = 0x19;
        }
        if (0x19 < DAT_00f15988) {
          DAT_00f15988 = 0x19;
        }
        _DAT_011f3a3c = 5;
        if (DAT_012058d0 < 0x18) {
          DAT_012058d0 = 0x18;
        }
        if (0x18 < DAT_00f15988) {
          DAT_00f15988 = 0x18;
        }
        _DAT_011f3a38 = 0;
        if (DAT_012058d0 < 0xf) {
          DAT_012058d0 = 0xf;
        }
        if (0xf < DAT_00f15988) {
          DAT_00f15988 = 0xf;
        }
        _DAT_011f3a14 = 0;
        if (DAT_012058d0 < 0x1b) {
          DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
          DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 1;
        FUN_00417cf0(1,2,6);
        DAT_01125ba0 = DAT_01219908;
        DAT_01125d78 = param_2 + -1;
        if ((bVar2) && (1 < param_2)) {
          DAT_01125d78 = param_2 + 2;
        }
        DAT_01125ba4 = (&DAT_01125c34)[DAT_01125d78 * 0xb];
        if (DAT_012058e8 == &PTR_PTR_01125b90) {
          FUN_0060a460(DAT_01125ba4);
          FUN_0060a460(DAT_01125ba0);
        }
        FUN_00612a60();
        if ((DAT_01125ba0 == DAT_01219908) && (DAT_01219928 != 0)) {
          fStack_20 = 0.0;
          fStack_1c = 0.0;
          fStack_18 = 0.0;
          fStack_14 = 0.0;
          FUN_0060add0(DAT_01125ba0,DAT_01219928,&fStack_20);
        }
        if ((uVar12 != 0xffffffff) && (uVar12 < 0x1000)) {
          iVar9 = uVar12 * 0x38;
          if ((&DAT_011a0f28 + iVar9 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar9] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar9) != 0) {
              FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar9),0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar9) =
                 *(uint *)(&DAT_011a0f34 + iVar9) & 0xfc9c8fff | 0x100000;
            FUN_006189c0();
          }
        }
        FUN_0053cdc0();
        iVar13 = 0;
        iVar9 = FUN_00606370(uVar12);
        do {
          if ((&DAT_01125c38)[DAT_01125d78 * 0xb + iVar13] != 0) {
            FUN_0060add0(DAT_01125ba4,(&DAT_01125c38)[DAT_01125d78 * 0xb + iVar13],param_1);
          }
          fStack_1c = *(float *)(param_1 + 0x10) * DAT_00e2cd54;
          fStack_20 = fStack_1c / (float)*(ushort *)(iVar9 + 2);
          fStack_1c = fStack_1c / (float)*(ushort *)(iVar9 + 4);
          fStack_14 = DAT_00e44564 - fStack_1c;
          fStack_18 = fStack_20;
          if ((&DAT_01125c48)[DAT_01125d78 * 0xb + iVar13] != 0) {
            FUN_0060add0(DAT_01125ba4,(&DAT_01125c48)[DAT_01125d78 * 0xb + iVar13],&fStack_20);
          }
          iVar13 = iVar13 + 1;
          param_1 = param_1 + 0x20;
        } while (iVar13 < param_2);
        puVar7 = (undefined4 *)FUN_0060cd00(0xd,4,0,1,0);
        uVar5 = DAT_00e2eff4;
        uVar3 = DAT_00e2b1a4;
        if (puVar7 != (undefined4 *)0x0) {
          *puVar7 = DAT_00e2eff4;
          puVar7[1] = uVar5;
          puVar7[2] = uVar3;
          puVar7[3] = uVar5;
          puVar7[4] = uVar3;
          puVar7[5] = uVar3;
          puVar7[6] = uVar5;
          puVar7[7] = uVar3;
          FUN_0060cde0();
        }
        if (DAT_01125c30 != 0) {
          uVar12 = DAT_01125c30 & 0xff;
          if ((&DAT_011eb8fc)[DAT_01125ba4 * 0x10] != '\\0') {
            uVar12 = uVar12 + 0x10;
          }
          FUN_00618d40();
          (&DAT_011d912c)[uVar12] = 0;
        }
        DAT_012058e8 = (undefined **)0x0;
        DAT_012058f0 = 0;
        DAT_01125ba0 = 0;
        DAT_01125ba4 = 0;
      }
      if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
      }
      if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
      }
      _DAT_011f3a30 = 1;
      if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
      }
      if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
      }
      _DAT_011f39f4 = 1;
      if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
      }
      if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
      }
      _DAT_011f3a10 = 1;
      if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
      }
      if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
      }
      _DAT_011f3a3c = 7;
      if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
      }
      if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
      }
      _DAT_011f3a38 = 0;
      if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
      }
      if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
      }
      _DAT_011f3a14 = 0;
      if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
      }
      if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
      }
      _DAT_011f3a44 = 0;
      FUN_00417cf0(1,5,6);
    }
  }
  return;
}