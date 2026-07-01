// Xbox PDB: EARS_Apt_UIPauseMap_ShowSelectedBuildingInfo
// FUNC_NAME: PauseCityTooltip::updateTooltip
void __thiscall PauseCityTooltip::updateTooltip(int this, int param_2)
{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  char *pcVar8;
  undefined1 **ppuVar9;
  undefined1 *local_2048;
  undefined4 local_2044;
  undefined4 local_2040;
  code *local_203c;
  undefined1 *local_2038;
  undefined4 local_2034;
  undefined4 local_2030;
  code *local_202c;
  undefined1 local_2028 [4116];
  undefined1 local_1014 [4112];
  undefined4 uStack_4;
  
  uVar1 = DAT_012234a4;
  uStack_4 = 0x97831a;
  if (**(int **)(DAT_012233a0 + 4) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
  }
  iVar7 = *(int *)(param_2 + 0xc4); // +0xC4: venue type
  if ((iVar7 == 0) || (iVar7 == 1)) {
    FUN_00604be0(); // clearTooltipBuffer
    local_2048 = (undefined1 *)0x0;
    local_2044 = 0;
    local_2040 = 0;
    local_203c = (code *)0x0;
    local_2038 = (undefined1 *)0x0;
    local_2034 = 0;
    local_2030 = 0;
    local_202c = (code *)0x0;
    puVar5 = (undefined4 *)FUN_006b2160(); // getVenueName
    puVar6 = (undefined1 *)*puVar5;
    if (puVar6 == (undefined1 *)0x0) {
      puVar6 = &DAT_0120546e; // empty string
    }
    FUN_00604c10(0x6e,puVar6); // setTooltipLine(0x6e, venueName)
    iVar7 = FUN_008c74d0(*(undefined4 *)(param_2 + 0x40)); // isBombed
    if (iVar7 != 0) {
      puVar5 = (undefined4 *)FUN_008be2d0(); // getBombedIcon
      puVar6 = (undefined1 *)*puVar5;
      if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
      }
      FUN_00604c10(0x66,puVar6); // setTooltipLine(0x66, bombedIcon)
    }
    iVar7 = FUN_006b4860(); // getVenueStatus
    if (((*(int *)(param_2 + 0x16c) != 1) && (*(int *)(param_2 + 0x16c) != 2)) ||
       (0.0 < *(float *)(param_2 + 0x170))) {
      if (((iVar7 == 2) || (iVar7 == 3)) || (iVar7 == 4)) {
        pcVar8 = "{$pause_city_tooltip_status_bombed}";
        goto LAB_00978617;
      }
      if (iVar7 == 1) {
        pcVar8 = "{$pause_city_tooltip_status_closed}";
        goto LAB_00978617;
      }
    }
    else {
      pcVar8 = "{$pause_city_tooltip_openingsoon}";
LAB_00978617:
      FUN_00604c10(0x73,pcVar8); // setTooltipLine(0x73, statusText)
    }
    FUN_006038a0(uVar1,local_2028,&local_2048,"$pause_city_tooltip_venue"); // formatTooltipString
    iVar7 = *(int *)(param_2 + 0xc0); // +0xC0: racket data
    if (iVar7 == 0) {
      FUN_004d3d90("$pause_city_tooltip_front"); // setFrontText
    }
    else {
      FUN_00604be0(); // clearTooltipBuffer
      puVar5 = (undefined4 *)FUN_0084a4b0(); // getRacketName
      puVar6 = (undefined1 *)*puVar5;
      if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
      }
      FUN_00604c10(0x6d,puVar6); // setTooltipLine(0x6d, racketName)
      uVar4 = FUN_0084a470(*(undefined4 *)(iVar3 + 0x1ed4)); // getRacketLevel
      FUN_00604c80(0x78,uVar4); // setTooltipLine(0x78, racketLevel)
      FUN_00604c80(0x79,*(undefined4 *)(iVar7 + 8)); // setTooltipLine(0x79, racketIncome)
      puVar5 = (undefined4 *)FUN_0084a4e0(); // getRacketIcon
      puVar6 = (undefined1 *)*puVar5;
      if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
      }
      FUN_00604c10(0x70,puVar6); // setTooltipLine(0x70, racketIcon)
      FUN_006038a0(uVar1,local_1014,&local_2038,"$pause_city_tooltip_racket"); // formatTooltipString
      FUN_00604c00(); // finalizeTooltip
    }
    FUN_004d44b0(10); // setTooltipWidth(10)
    FUN_004d43f0(local_2038,0,local_2034); // setTooltipText
    puVar6 = local_2048;
    if (local_2048 == (undefined1 *)0x0) {
      puVar6 = &DAT_0120546e;
    }
    FUN_005c4660(*(undefined4 *)(param_1 + 0xf0),puVar6,0x100,0); // setTooltipTitle
    if (local_2038 != (undefined1 *)0x0) {
      (*local_202c)(local_2038); // freeString
    }
    if (local_2048 != (undefined1 *)0x0) {
      (*local_203c)(local_2048); // freeString
    }
  }
  else {
    if (iVar7 != 9) {
      puVar5 = (undefined4 *)FUN_006b2160(); // getVenueName
      puVar6 = (undefined1 *)*puVar5;
      if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
      }
      FUN_005c4660(*(undefined4 *)(param_1 + 0xf0),puVar6,0x100,0); // setTooltipTitle
      goto LAB_0097876b;
    }
    iVar3 = FUN_008ff310(*(undefined4 *)(param_2 + 0x38)); // isFamilyTree
    if (iVar3 == 0) goto LAB_0097876b;
    FUN_00604be0(); // clearTooltipBuffer
    uVar4 = FUN_008fdfb0(); // getFamilyTreeData
    iVar3 = FUN_00791540(); // getPlayerRank
    if (iVar3 != 0) {
      puVar5 = (undefined4 *)FUN_008be2d0(); // getRankIcon
      puVar6 = (undefined1 *)*puVar5;
      if (puVar6 == (undefined1 *)0x0) {
        puVar6 = &DAT_0120546e;
      }
      FUN_00604c10(0x66,puVar6); // setTooltipLine(0x66, rankIcon)
    }
    iVar3 = FUN_00791750(); // getPlayerRankType
    if (iVar3 == 3) {
      pcVar8 = "{$rank_soldier}";
LAB_009783e6:
      FUN_00604c10(0x72,pcVar8); // setTooltipLine(0x72, rankText)
    }
    else {
      if (iVar3 == 4) {
        pcVar8 = "{$rank_capo}";
        goto LAB_009783e6;
      }
      if (iVar3 == 5) {
        pcVar8 = "{$rank_underboss}";
        goto LAB_009783e6;
      }
    }
    puVar5 = (undefined4 *)FUN_00790610(); // getFamilyName
    puVar6 = (undefined1 *)*puVar5;
    if (puVar6 == (undefined1 *)0x0) {
      puVar6 = &DAT_0120546e;
    }
    FUN_00604c10(0x6e,puVar6); // setTooltipLine(0x6e, familyName)
    iVar3 = FUN_008c6d50(uVar4); // getFamilyMemberStatus
    if (iVar3 != 0) {
      iVar3 = *(int *)(iVar3 + 4);
      if ((iVar3 == 1) || (cVar2 = FUN_008fe3d0(), cVar2 != '\\0')) {
        pcVar8 = "{$pause_family_tree_status_at_hangout}";
      }
      else if (((iVar3 == 2) || (iVar3 == 3)) || (iVar3 == 4)) {
        pcVar8 = "{$pause_family_tree_status_alive}";
      }
      else if (iVar3 == 5) {
        pcVar8 = "{$pause_family_tree_status_hospital}";
      }
      else {
        if (iVar3 != 6) goto LAB_00978470;
        pcVar8 = "{$pause_family_tree_status_jail}";
      }
      FUN_00604c10(0x73,pcVar8); // setTooltipLine(0x73, statusText)
    }
LAB_00978470:
    ppuVar9 = &local_2038;
    local_2038 = (undefined1 *)0x0;
    local_2034 = 0;
    local_2030 = 0;
    local_202c = (code *)0x0;
    uVar4 = FUN_008fda40(1); // getHangoutName
    FUN_00603330(uVar4,ppuVar9); // formatHangoutString
    puVar6 = local_2038;
    if (local_2038 == (undefined1 *)0x0) {
      puVar6 = &DAT_0120546e;
    }
    FUN_00604c10(0x6b,puVar6); // setTooltipLine(0x6b, hangoutName)
    local_2048 = (undefined1 *)0x0;
    local_2044 = 0;
    local_2040 = 0;
    local_203c = (code *)0x0;
    FUN_006038a0(uVar1,local_2028,&local_2048,"$pause_city_tooltip_hangout"); // formatTooltipString
    puVar6 = local_2048;
    if (local_2048 == (undefined1 *)0x0) {
      puVar6 = &DAT_0120546e;
    }
    FUN_005c4660(*(undefined4 *)(param_1 + 0xf0),puVar6,0x100,0); // setTooltipTitle
    if (local_2048 != (undefined1 *)0x0) {
      (*local_203c)(local_2048); // freeString
    }
    if (local_2038 != (undefined1 *)0x0) {
      (*local_202c)(local_2038); // freeString
    }
  }
  FUN_00604c00(); // finalizeTooltip
LAB_0097876b:
  FUN_00977ec0(); // updateTooltipDisplay
  return;
}