// FUNC_NAME: GodfatherGameManager::handleDonControlTransition
void GodfatherGameManager::handleDonControlTransition(uint param_1, undefined4 *param_2, int param_3, uint param_4, uint param_5, char param_6, float param_7, float param_8)
{
  undefined8 uVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined8 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  int local_94;
  uint local_8c;
  code *local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined8 local_6c;
  undefined8 local_64;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 local_50 [19];
  
  iVar9 = *(int *)(DAT_01223398 + 8);
  puVar2 = *(uint **)(*(int *)(iVar9 + 4) + (param_1 % *(uint *)(iVar9 + 8)) * 4);
  do {
    if (puVar2 == (uint *)0x0) {
LAB_00953e7f:
      local_8c = 0;
LAB_00953e83:
      for (puVar2 = *(uint **)(*(int *)(iVar9 + 4) + (param_5 % *(uint *)(iVar9 + 8)) * 4);
          (puVar2 != (uint *)0x0 && (*puVar2 != param_5)); puVar2 = (uint *)puVar2[2]) {
      }
      puVar4 = (undefined8 *)FUN_00483a30();
      local_6c = *puVar4;
      uVar1 = puVar4[1];
      local_5c = *(undefined4 *)(puVar4 + 2);
      uStack_58 = *(undefined4 *)((int)puVar4 + 0x14);
      local_64._0_4_ = (undefined4)uVar1;
      local_54 = *(undefined4 *)(puVar4 + 3);
      local_64._4_4_ = (undefined4)((ulonglong)uVar1 >> 0x20);
      local_84 = 0;
      local_78 = 0;
      local_74 = 0;
      local_70 = 0;
      local_88 = FUN_009533e0;
      local_80 = (undefined4)local_64;
      local_7c = local_64._4_4_;
      local_64 = uVar1;
      FUN_004839f0(&local_88);
      uVar3 = DAT_01218e58;
      puVar10 = local_50;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar10 = *param_2;
        param_2 = param_2 + 1;
        puVar10 = puVar10 + 1;
      }
      FUN_0060e530(0,DAT_01218e58,0);
      if (param_6 != '\0') {
        FUN_00609810(0x31);
      }
      local_94 = 0;
      iVar9 = FUN_00422940();
      if (iVar9 != 0) {
        local_94 = FUN_00422930();
        FUN_00423610();
      }
      FUN_00422900();
      FUN_00423410();
      uVar5 = FUN_00422790();
      FUN_00433b30(3);
      FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
      uVar7 = *(undefined4 *)(local_8c + 0xa0);
      FUN_004349b0(uVar5,0);
      FUN_00433700(uVar7,local_50,3,0xffffffff,9,1);
      FUN_00433700(uVar7,local_50,3,0xffffffff,0x11,1);
      FUN_004349b0(uVar5,3);
      FUN_004349b0(uVar5,4);
      uVar11 = 0;
      if (param_4 != 0) {
        do {
          FUN_00433800(*(undefined4 *)(param_3 + uVar11 * 4));
          uVar11 = uVar11 + 1;
        } while (uVar11 < param_4);
      }
      FUN_004349b0(uVar5,6);
      if (param_6 == '\0') {
        FUN_00952e00(uVar3);
      }
      FUN_00433700(uVar7,local_50,3,0xffffffff,9,1);
      FUN_00433700(uVar7,local_50,3,0xffffffff,0x11,1);
      FUN_00433700(uVar7,local_50,3,0xffffffff,0x21,1);
      if (param_6 != '\0') {
        FUN_00609890(1);
        uVar7 = *(undefined4 *)(DAT_011298a0 + 0x90);
        uVar6 = FUN_0060db00(0,0);
        FUN_0060db20(0,uVar7,0,0);
        FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
        FUN_00609810(0x31);
        if (DAT_012058d0 < 0xe) {
          DAT_012058d0 = 0xe;
        }
        if (0xe < DAT_00f15988) {
          DAT_00f15988 = 0xe;
        }
        _DAT_011f3a10 = 0;
        if (DAT_012058d0 < 7) {
          DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
          DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 0;
        uVar7 = FUN_0060d740("SM_QuadEffectClass");
        piVar8 = (int *)FUN_00611d30(uVar7);
        FUN_00611b50(6);
        FUN_00611750(uVar6);
        (**(code **)(*piVar8 + 0x18))();
        _DAT_00e57414 = (param_8 / param_7) * _DAT_00d5c458;
        _DAT_00e57410 = _DAT_00d5c458 - _DAT_00e57414;
        _DAT_00e57414 = _DAT_00e57414 + _DAT_00d5c458;
        FUN_006105e0(_DAT_00e57410,_DAT_00e57414,_DAT_00e57418,_DAT_00e5741c);
        FUN_00609890(1);
        (**(code **)(*piVar8 + 0x20))();
        FUN_00611750(0);
        if (DAT_012058d0 < 0xe) {
          DAT_012058d0 = 0xe;
        }
        if (0xe < DAT_00f15988) {
          DAT_00f15988 = 0xe;
        }
        _DAT_011f3a10 = 1;
        if (DAT_012058d0 < 7) {
          DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
          DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 1;
        FUN_0060db20(0,uVar6,0,0);
        FUN_0060db60(0,0,0,0x3f800000,0x3f800000);
        FUN_00952e00(uVar3);
        piVar8 = (int *)(DAT_012068e8 + 0x14);
        **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_00e573b0;
        *piVar8 = *piVar8 + 4;
      }
      FUN_00423610();
      if (local_94 != 0) {
        FUN_00422900();
        FUN_00423410();
      }
      FUN_00434b90(uVar5);
      FUN_004839f0(&local_6c);
      return;
    }
    if (*puVar2 == param_1) {
      if ((puVar2 != (uint *)0x0) && (puVar2 + 1 != (uint *)0x0)) {
        local_8c = puVar2[1];
        goto LAB_00953e83;
      }
      goto LAB_00953e7f;
    }
    puVar2 = (uint *)puVar2[2];
  } while( true );
}