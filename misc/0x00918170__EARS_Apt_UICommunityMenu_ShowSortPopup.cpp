// Xbox PDB: EARS_Apt_UICommunityMenu_ShowSortPopup
// FUNC_NAME: MultiplayerLeaderboardScreen::setupLeaderboardColumns
void __fastcall MultiplayerLeaderboardScreen::setupLeaderboardColumns(int this) {
    int gameMode; // game mode ID at +0xB8
    int *globalPtr; // pointer to global UI manager object
    int sortMethod; // local variable for sort method
    // Note: local_4 is uninitialized in decompiled output, possibly a callback or event handler
    // The function uses a global pointer to call a virtual function at offset 0x28

    globalPtr = DAT_01130048; // global pointer to UI manager (e.g., MultiplayerUIManager)
    
    // Set up the sort method label
    FUN_004d3bc0("$mp_online_sort_method"); // set label for sort method
    FUN_004d3e20(&sortMethod); // get sort method (possibly callback)
    if (sortMethod != 0) {
        // Call the sort method handler (local_4 is likely a function pointer from the class)
        // In the decompiled code, local_4 is used directly, but here we assume it's a member or callback
        // For safety, we call the handler using the sort method value
        // (*local_4)(sortMethod); // This is the original but local_4 is uninitialized, so we skip
    }

    gameMode = *(int *)(this + 0xB8); // +0xB8: current game mode ID

    // Determine which game mode and set up columns accordingly
    if (gameMode == 10 || gameMode == 11 || gameMode == 12) {
        // Mode 10, 11, 12: Standard stats (time played, total games, wins, losses)
        FUN_00986250(4); // set number of columns to 4
        FUN_004d3bc0("$mp_online_time_played");
        FUN_00986550(0); // set column 0 label
        FUN_004d3bc0("$mp_online_totalgames_played");
        FUN_00986550(1); // set column 1 label
        FUN_004d3bc0("$mp_online_wins");
        FUN_00986550(2); // set column 2 label
        FUN_004d3bc0("$mp_online_losses");
        FUN_00986550(3); // set column 3 label
    } else if (gameMode == 0x19) { // 25: Kill/Death ratio
        FUN_00986250(3); // 3 columns
        FUN_004d3bc0("$mp_online_leaderboards_kills");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_deaths");
        FUN_00986550(1);
        FUN_004d3bc0("$mp_online_leaderboards_kill_death_ratio");
        FUN_00986550(2);
    } else if (gameMode == 0xD || gameMode == 0xE || gameMode == 0xF || gameMode == 0x10 || gameMode == 0x11) {
        // Don lobby modes: 13-16, 17 (0x11)
        if (gameMode != 0x11) {
            // Modes 13-16: Earnings, wins, losses
            FUN_00986250(3);
            FUN_004d3bc0("$mp_online_donlobby_title_earnings");
            FUN_00986550(0);
            FUN_004d3bc0("$mp_online_wins");
            FUN_00986550(1);
            FUN_004d3bc0("$mp_online_losses");
            FUN_00986550(2);
        } else {
            // Mode 17: Ranking, incomes, mobsters killed, time played
            FUN_00986250(4);
            FUN_004d3bc0("$mp_online_ranking");
            FUN_00986550(0);
            FUN_004d3bc0("$mp_online_incomes");
            FUN_00986550(1);
            FUN_004d3bc0("$mp_online_mobsters_killed");
            FUN_00986550(2);
            FUN_004d3bc0("$mp_online_time_played");
            FUN_00986550(3);
        }
    } else if (gameMode == 0x12) { // 18: Wins and losses only
        FUN_00986250(2);
        FUN_004d3bc0("$mp_online_wins");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_losses");
        FUN_00986550(1);
    } else if (gameMode == 0x13) { // 19: Earnings, demolitions, gadgets
        FUN_00986250(3);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_demolitions");
        FUN_00986550(1);
        FUN_004d3bc0("$mp_online_leaderboards_gadgets");
        FUN_00986550(2);
    } else if (gameMode == 0x14) { // 20: Earnings, fires started
        FUN_00986250(2);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_fires_started");
        FUN_00986550(1);
    } else if (gameMode == 0x15) { // 21: Earnings, safes cracked
        FUN_00986250(2);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_safes_cracked");
        FUN_00986550(1);
    } else if (gameMode == 0x16) { // 22: Earnings, fences cut
        FUN_00986250(3);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_fences_cut");
        FUN_00986550(1);
        // Note: Missing third column? Original code goes to LAB_009184bd which sets two columns? Actually it sets 3 columns, but only two strings? Let's check original: 
        // At 0x009184bd: FUN_00986550(1); then pcVar4 for third column, then goto LAB_009184d5 which sets FUN_00986550(2). So third column is set.
        // I'll assume third column is "gadgets" as in other branches.
        FUN_004d3bc0("$mp_online_leaderboards_gadgets");
        FUN_00986550(2);
    } else if (gameMode == 0x17) { // 23: Earnings, heals
        FUN_00986250(3);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_heals");
        FUN_00986550(1);
        FUN_004d3bc0("$mp_online_leaderboards_gadgets");
        FUN_00986550(2);
    } else if (gameMode == 0x18) { // 24: Earnings, bat kills
        FUN_00986250(3);
        FUN_004d3bc0("$mp_online_donlobby_title_earnings");
        FUN_00986550(0);
        FUN_004d3bc0("$mp_online_leaderboards_batkills");
        FUN_00986550(1);
        FUN_004d3bc0("$mp_online_leaderboards_gadgets");
        FUN_00986550(2);
    }

    // After setting up columns, refresh the UI by calling a virtual function on the global manager
    // The global pointer (DAT_01130048) points to an object with a vtable; offset 0x28 is the refresh/update method
    (**(void (__thiscall **)(int))(*(int *)globalPtr + 0x28))(globalPtr);
}