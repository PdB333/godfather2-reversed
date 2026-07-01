// Xbox PDB: EARS_Apt_LobbyScreen_RefreshPlayers
// FUNC_NAME: MultiplayerScenarioManager::updateTeamAssignments
void __fastcall MultiplayerScenarioManager::updateTeamAssignments(int *this)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  int blueTeamCount;
  int neutralTeamCount;
  int redTeamCount;
  undefined1 *puStack_40;
  code *pcStack_34;
  int iStack_30;
  code *pcStack_24;
  int iStack_20;
  code *pcStack_14;
  int iStack_10;
  code *pcStack_4;
  
  // Call virtual function at vtable+0x90 (likely update or preUpdate)
  (**(code **)(*this + 0x90))();
  
  uVar7 = 0;
  // Check if game state is not 3 (likely not in-game)
  if (*(int *)(DAT_01129930 + 0xdc) != 3) {
    *(undefined4 *)(DAT_01129930 + 0xc4) = 0;
  }
  
  redTeamCount = 0;
  neutralTeamCount = 0;
  blueTeamCount = 0;
  
  // Get network session (likely NetSession singleton)
  FUN_004d3b00(0);
  
  // Iterate through players (this[0x14] = player count)
  if (this[0x14] != 0) {
    do {
      // Get player data at index uVar7
      iVar1 = *(int *)(this[0x13] + uVar7 * 4); // this[0x13] = player array
      iVar2 = *(int *)(iVar1 + 0x10); // team ID at +0x10
      
      if (iVar2 == 1) {
        // Red team
        pcVar9 = "AddUserToRedTeam";
        if (*(char *)(iVar1 + 0x58) == '\0') { // +0x58 = isAI flag
          pcVar9 = "AddPlayerToRedTeam";
        }
        FUN_00962da0(iVar1, redTeamCount); // Assign to red team slot
        uVar3 = FUN_004d3b00(redTeamCount);
        FUN_004d3e20(uVar3);
        if (iStack_10 != 0) {
          (*pcStack_4)(iStack_10);
        }
        redTeamCount = redTeamCount + 1;
        pcVar8 = (char *)&PTR_LAB_00d8e0fc; // "red" string
      }
      else if ((iVar2 == 2) || (iVar2 != 3)) {
        // Neutral zone (team 2 or unknown)
        pcVar9 = "AddUserToNeutralZone";
        if (*(char *)(iVar1 + 0x58) == '\0') {
          pcVar9 = "AddPlayerToNeutralZone";
        }
        FUN_00962da0(iVar1, neutralTeamCount);
        pcVar8 = "neutral";
        uVar3 = FUN_004d3b00(neutralTeamCount);
        FUN_004d3e20(uVar3);
        if (iStack_20 != 0) {
          (*pcStack_14)(iStack_20);
        }
        neutralTeamCount = neutralTeamCount + 1;
      }
      else {
        // Blue team (team 3)
        pcVar9 = "AddUserToBlueTeam";
        if (*(char *)(iVar1 + 0x58) == '\0') {
          pcVar9 = "AddPlayerToBlueTeam";
        }
        FUN_00962da0(iVar1, blueTeamCount);
        pcVar8 = &DAT_00d8e160; // "blue" string
        uVar3 = FUN_004d3b00(blueTeamCount);
        FUN_004d3e20(uVar3);
        if (iStack_30 != 0) {
          (*pcStack_24)(iStack_30);
        }
        blueTeamCount = blueTeamCount + 1;
      }
      
      // Update VoIP visibility for this player
      FUN_005a04a0(pcVar9, 0, &DAT_00d8cdec, 0);
      puVar4 = puStack_40;
      if (puStack_40 == (undefined1 *)0x0) {
        puVar4 = &DAT_0120546e; // Default string
      }
      FUN_005a04a0("UpdateVoIPVisibility", 0, &DAT_00d8cdec, 3, pcVar8, puVar4, &DAT_00e36da0);
      
      uVar7 = uVar7 + 1;
    } while (uVar7 < (uint)this[0x14]);
  }
  
  // Update D-pad visibility for neutral and red teams
  puVar5 = (undefined4 *)FUN_004d3b00(blueTeamCount != 7);
  puVar4 = (undefined1 *)*puVar5;
  if (puVar4 == (undefined1 *)0x0) {
    puVar4 = &DAT_0120546e;
  }
  puVar5 = (undefined4 *)FUN_004d3b00(redTeamCount != 7);
  puVar6 = (undefined1 *)*puVar5;
  if (puVar6 == (undefined1 *)0x0) {
    puVar6 = &DAT_0120546e;
  }
  FUN_005a04a0("SetNeutralDPadVisibility", 0, &DAT_00d8cdec, 2, puVar6, puVar4);
  
  // Cleanup callbacks
  if (iStack_10 != 0) {
    (*pcStack_4)(iStack_10);
  }
  if (iStack_20 != 0) {
    (*pcStack_14)(iStack_20);
  }
  if (puStack_40 != (undefined1 *)0x0) {
    (*pcStack_34)(puStack_40);
  }
  return;
}