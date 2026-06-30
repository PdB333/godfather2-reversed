// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined4 uVar7;
  bool bVar8;
  
  if ((DAT_01194a6c == 0) && (DAT_01194a68 == 0)) {
    bVar8 = false;
LAB_00531d6b:
    cVar2 = '\0';
    if (!bVar8) goto LAB_00531ff0;
  }
  else {
    bVar8 = true;
    if ((DAT_01194a6c == 0) || (DAT_01194a68 == 0)) goto LAB_00531d6b;
    cVar2 = '\x01';
  }
  if ((DAT_011f38f0 == DAT_01218e58) && (DAT_011f38f4 == 0)) {
    FUN_00609890(1);
  }
  else {
    FUN_0060df60(DAT_011f38f0,DAT_01218e58);
  }
  FUN_005322a0();
  iVar3 = DAT_01218e98;
  uVar7 = DAT_011f3914;
  iVar1 = DAT_011f3910;
  DAT_011f3910 = DAT_01218e98;
  DAT_011f3914 = 0;
  FUN_00609340(4,iVar1,uVar7);
  if ((DAT_00f15a14 == 1) || (DAT_00f15a14 == 2)) {
    uVar6 = 0;
    do {
      if ((&DAT_01218e50)[uVar6 * 2] == 0) {
        if (uVar6 < 0x14) {
          (&DAT_01218e54)[uVar6 * 2] = (&DAT_01218e54)[uVar6 * 2] & 0xfffffffc;
        }
        break;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < 0x14);
    piVar5 = DAT_01205750;
    iVar1 = DAT_011f38f4;
    bVar8 = DAT_011f38f0 != 0;
    DAT_011f38f0 = 0;
    DAT_011f38f4 = 0;
    if ((bVar8) || (iVar1 != 0)) {
      iVar1 = *DAT_01205750;
      uVar7 = FUN_00609260();
      (**(code **)(iVar1 + 0x94))(piVar5,0,uVar7);
      DAT_01223538 = 1;
    }
  }
  else {
    uVar6 = 0;
    do {
      if ((&DAT_01218e50)[uVar6 * 2] == iVar3) {
        if (uVar6 < 0x14) {
          (&DAT_01218e54)[uVar6 * 2] = (&DAT_01218e54)[uVar6 * 2] & 0xfffffffc;
        }
        break;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < 0x14);
    iVar4 = DAT_011f38f4;
    iVar1 = DAT_011f38f0;
    DAT_011f38f0 = iVar3;
    DAT_011f38f4 = 0;
    FUN_00609340(0,iVar1,iVar4);
  }
  FUN_0060db60(4,0,0,0x3f800000,0x3f800000);
  FUN_004e2b30();
  FUN_00609890(2);
  iVar3 = DAT_01218eb0;
  uVar7 = DAT_011f3914;
  iVar1 = DAT_011f3910;
  DAT_011f3910 = DAT_01218eb0;
  DAT_011f3914 = 0;
  FUN_00609340(4,iVar1,uVar7);
  if ((DAT_00f15a14 != 1) && (DAT_00f15a14 != 2)) {
    uVar6 = 0;
    do {
      if ((&DAT_01218e50)[uVar6 * 2] == iVar3) {
        if (uVar6 < 0x14) {
          (&DAT_01218e54)[uVar6 * 2] = (&DAT_01218e54)[uVar6 * 2] & 0xfffffffc;
        }
        break;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < 0x14);
    uVar7 = DAT_011f38f4;
    iVar1 = DAT_011f38f0;
    DAT_011f38f0 = iVar3;
    DAT_011f38f4 = 0;
    FUN_00609340(0,iVar1,uVar7);
  }
  FUN_0060db60(4,0,0,0x3f800000,0x3f800000);
  FUN_004e2b30();
  iVar1 = DAT_01218eb8;
  uVar6 = 0;
  do {
    if ((&DAT_01218e50)[uVar6 * 2] == DAT_01218eb8) {
      if (uVar6 < 0x14) {
        (&DAT_01218e54)[uVar6 * 2] = (&DAT_01218e54)[uVar6 * 2] & 0xfffffffc;
      }
      break;
    }
    uVar6 = uVar6 + 1;
  } while (uVar6 < 0x14);
  uVar7 = DAT_011f38f4;
  iVar3 = DAT_011f38f0;
  DAT_011f38f0 = iVar1;
  DAT_011f38f4 = 0;
  FUN_00609340(0,iVar3,uVar7);
LAB_00531ff0:
  if (DAT_01194a6c != 0) {
    FUN_00609730(0,0,0,0,0x3f800000,0);
    FUN_00609810(1);
    FUN_00609730(0,0,0,0,0x3f800000,0);
    for (iVar1 = DAT_01194a6c; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x10)) {
      FUN_005326c0(iVar1);
    }
    FUN_00532350();
    iVar1 = DAT_01218eb8;
    if (cVar2 == '\0') {
      FUN_00531400();
    }
    else {
      uVar6 = 0;
      do {
        if ((&DAT_01218e50)[uVar6 * 2] == DAT_01218eb8) {
          if (uVar6 < 0x14) {
            (&DAT_01218e54)[uVar6 * 2] = (&DAT_01218e54)[uVar6 * 2] & 0xfffffffc;
          }
          break;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < 0x14);
      iVar4 = DAT_011f38f4;
      iVar3 = DAT_011f38f0;
      DAT_011f38f0 = iVar1;
      DAT_011f38f4 = 0;
      FUN_00609340(0,iVar3,iVar4);
      uVar7 = DAT_011f3914;
      iVar1 = DAT_011f3910;
      DAT_011f3910 = DAT_01218eb0;
      DAT_011f3914 = 0;
      FUN_00609340(4,iVar1,uVar7);
      FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
    }
  }
  if (DAT_01194a68 != 0) {
    FUN_00609730(0,0,0,0,0x3f800000,0);
    FUN_00609810(1);
    FUN_00609730(0,0,0,0,0x3f800000,0);
    for (iVar1 = DAT_01194a68; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x10)) {
      FUN_005326c0(iVar1);
    }
    FUN_00531700(cVar2);
  }
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
  FUN_00417cf0(1,5,6);
  if (DAT_012058d0 < 0x1b) {
    DAT_012058d0 = 0x1b;
  }
  _DAT_011f3a44 = 0;
  if (0x1a < DAT_00f15988) {
    DAT_00f15988 = 0x1b;
  }
  return;
}