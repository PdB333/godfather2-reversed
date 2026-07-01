// Xbox PDB: EARS_Apt_LobbyParams_Init
// FUNC_NAME: MultiplayerScenarioManager::initializeScenarioSettings
void MultiplayerScenarioManager::initializeScenarioSettings(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined2 in_FPUControlWord;
  longlong local_b4;
  undefined4 uStack_ac;
  code *local_a8;
  int aiStack_a4 [3];
  code *pcStack_98;
  uint uStack_94;
  int local_90 [3];
  code *local_84;
  undefined1 auStack_80 [128];
  
  if (DAT_011307f0 == '\0') {
    local_90[0] = 0;
    local_90[1] = 0;
    local_90[2] = 0;
    local_84 = (code *)0x0;
    FUN_004d8a00(); // resetStringBuffer
    FUN_004d3bc0("$mp_online_match_type"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_map"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_multiplayermode"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_score_limit"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_time_limit"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_max_players"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_max_rank"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_respawn_time"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_online_team_balance"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_player_cut"); // loadLocalizedString
    if (DAT_01130874 == DAT_01130878) {
      if (DAT_01130878 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130878 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130874 * 0x10;
    DAT_01130874 = DAT_01130874 + 1;
    if (iVar3 + DAT_01130870 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_0095e9f0(); // initializeScenarioSettingsPart2
    iVar3 = DAT_0112b9b4;
    if ((DAT_0112b9b4 != 0) && (uVar5 = 0, *(int *)(DAT_0112b9b4 + 8) != 0)) {
      do {
        local_b4 = 0;
        uStack_ac = 0;
        local_a8 = (code *)0x0;
        aiStack_a4[0] = 0;
        aiStack_a4[1] = 0;
        aiStack_a4[2] = 0;
        pcStack_98 = (code *)0x0;
        uVar2 = FUN_008a7160(); // getScenarioName
        FUN_004d3e20(uVar2); // setString
        uVar2 = FUN_008a7190(); // getScenarioDescription
        FUN_004d3e20(uVar2); // setString
        if (DAT_01130820 == DAT_01130824) {
          if (DAT_01130824 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = DAT_01130824 * 2;
          }
          FUN_0095e090(iVar4); // allocateScenarioEntry
        }
        iVar4 = DAT_01130820 * 0x20;
        DAT_01130820 = DAT_01130820 + 1;
        if (iVar4 + DAT_0113081c != 0) {
          FUN_004d3b50(&local_b4); // pushStringToArray
          FUN_004d3b50(aiStack_a4); // pushStringToArray
        }
        if (aiStack_a4[0] != 0) {
          (*pcStack_98)(aiStack_a4[0]); // callback
        }
        if ((int)local_b4 != 0) {
          (*local_a8)((int)local_b4); // callback
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(uint *)(iVar3 + 8));
    }
    FUN_004d8a00(); // resetStringBuffer
    FUN_004d3bc0("$rank_soldier"); // loadLocalizedString
    if (DAT_01130808 == DAT_0113080c) {
      if (DAT_0113080c == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_0113080c * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130808 * 0x10;
    DAT_01130808 = DAT_01130808 + 1;
    if (iVar3 + DAT_01130804 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$rank_capo"); // loadLocalizedString
    if (DAT_01130808 == DAT_0113080c) {
      if (DAT_0113080c == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_0113080c * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130808 * 0x10;
    DAT_01130808 = DAT_01130808 + 1;
    if (iVar3 + DAT_01130804 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$rank_underboss"); // loadLocalizedString
    if (DAT_01130808 == DAT_0113080c) {
      if (DAT_0113080c == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_0113080c * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130808 * 0x10;
    DAT_01130808 = DAT_01130808 + 1;
    if (iVar3 + DAT_01130804 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$rank_consigliere"); // loadLocalizedString
    if (DAT_01130808 == DAT_0113080c) {
      if (DAT_0113080c == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_0113080c * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130808 * 0x10;
    DAT_01130808 = DAT_01130808 + 1;
    if (iVar3 + DAT_01130804 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$rank_don"); // loadLocalizedString
    if (DAT_01130808 == DAT_0113080c) {
      if (DAT_0113080c == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_0113080c * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_01130808 * 0x10;
    DAT_01130808 = DAT_01130808 + 1;
    if (iVar3 + DAT_01130804 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d8a00(); // resetStringBuffer
    FUN_004d3bc0("$mp_weapon_rank_level4"); // loadLocalizedString
    if (DAT_0113085c == DAT_01130860) {
      if (DAT_01130860 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130860 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_0113085c * 0x10;
    DAT_0113085c = DAT_0113085c + 1;
    if (iVar3 + DAT_01130858 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_weapon_rank_level3"); // loadLocalizedString
    if (DAT_0113085c == DAT_01130860) {
      if (DAT_01130860 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130860 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_0113085c * 0x10;
    DAT_0113085c = DAT_0113085c + 1;
    if (iVar3 + DAT_01130858 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_weapon_rank_level2"); // loadLocalizedString
    if (DAT_0113085c == DAT_01130860) {
      if (DAT_01130860 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130860 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_0113085c * 0x10;
    DAT_0113085c = DAT_0113085c + 1;
    if (iVar3 + DAT_01130858 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_004d3bc0("$mp_weapon_rank_level1"); // loadLocalizedString
    if (DAT_0113085c == DAT_01130860) {
      if (DAT_01130860 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = DAT_01130860 * 2;
      }
      FUN_00407880(iVar3); // allocateString
    }
    iVar3 = DAT_0113085c * 0x10;
    DAT_0113085c = DAT_0113085c + 1;
    if (iVar3 + DAT_01130858 != 0) {
      FUN_004d3b50(&local_b4); // pushStringToArray
    }
    if ((int)local_b4 != 0) {
      (*local_a8)((int)local_b4); // callback
    }
    FUN_0095ea60(0); // initializeWeaponSettings
    FUN_004d8a00(); // resetStringBuffer
    uVar5 = 0;
    do {
      FUN_00603f90(uVar5,local_90,1); // getMapName
      if (DAT_01130844 == DAT_01130848) {
        if (DAT_01130848 == 0) {
          iVar3 = 1;
        }
        else {
          iVar3 = DAT_01130848 * 2;
        }
        FUN_00407880(iVar3); // allocateString
      }
      iVar3 = DAT_01130844 * 0x10;
      DAT_01130844 = DAT_01130844 + 1;
      if (iVar3 + DAT_01130840 != 0) {
        FUN_004d3b50(local_90); // pushStringToArray
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0xb);
    FUN_004d8a00(); // resetStringBuffer
    uVar5 = 0;
    do {
      uStack_94 = CONCAT22(uStack_94._2_2_,in_FPUControlWord);
      local_b4 = (longlong)ROUND(*(float *)((int)&DAT_00d8cc90 + uVar5));
      FUN_006042f0(0,(int)local_b4,local_90); // getScoreLimitString
      if (DAT_01130814 == DAT_01130818) {
        if (DAT_01130818 == 0) {
          iVar3 = 1;
        }
        else {
          iVar3 = DAT_01130818 * 2;
        }
        FUN_00407880(iVar3); // allocateString
      }
      iVar3 = DAT_01130814 * 0x10;
      DAT_01130814 = DAT_01130814 + 1;
      if (iVar3 + DAT_01130810 != 0) {
        FUN_004d3b50(local_90); // pushStringToArray
      }
      uVar5 = uVar5 + 4;
    } while (uVar5 < 0x18);
    FUN_004d8a00(); // resetStringBuffer
    uVar5 = 0;
    do {
      FUN_006042f0(*(undefined4 *)((int)&DAT_00d8ccd4 + uVar5),0,local_90); // getTimeLimitString
      if (DAT_01130850 == DAT_01130854) {
        if (DAT_01130854 == 0) {
          iVar3 = 1;
        }
        else {
          iVar3 = DAT_01130854 * 2;
        }
        FUN_00407880(iVar3); // allocateString
      }
      iVar3 = DAT_01130850 * 0x10;
      DAT_01130850 = DAT_01130850 + 1;
      if (iVar3 + DAT_0113084c != 0) {
        FUN_004d3b50(local_90); // pushStringToArray
      }
      uVar5 = uVar5 + 4;
    } while (uVar5 < 0x20);
    FUN_004d8a00(); // resetStringBuffer
    uVar5 = 0;
    do {
      FUN_005c4630(auStack_80,0x80,&DAT_00e325c4,*(undefined4 *)((int)&DAT_00d8ccfc + uVar5)); // formatString
      FUN_004d3bc0(auStack_80); // loadLocalizedString
      if (DAT_01130868 == DAT_0113086c) {
        if (DAT_0113086c == 0) {
          iVar3 = 1;
        }
        else {
          iVar3 = DAT_0113086c * 2;
        }
        FUN_00407880(iVar3); // allocateString
      }
      iVar3 = DAT_01130868 * 0x10;
      DAT_01130868 = DAT_01130868 + 1;
      if (iVar3 + _DAT_01130864 != 0) {
        FUN_004d3b50(&local_b4); // pushStringToArray
      }
      if ((int)local_b4 != 0) {
        (*local_a8)((int)local_b4); // callback
      }
      uVar1 = uStack_94;
      uVar5 = uVar5 + 4;
    } while (uVar5 < 0x14);
    uStack_94 = uStack_94 & 0xffffff00;
    if (DAT_01129930 != 0) {
      uStack_94 = CONCAT31(SUB43(uVar1,1),*(undefined1 *)(DAT_01129930 + 500));
    }
    FUN_0095eb90(uStack_94); // finalizeSettings
    DAT_011307f0 = '\x01';
    if (local_90[0] != 0) {
      (*local_84)(local_90[0]); // callback
    }
  }
  return;
}