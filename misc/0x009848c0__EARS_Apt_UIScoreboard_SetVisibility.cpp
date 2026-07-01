// Xbox PDB: EARS_Apt_UIScoreboard_SetVisibility
// FUNC_NAME: ScoreboardManager::toggleScoreboard
// Function address: 0x009848c0
// Handles showing/hiding the multiplayer scoreboard. When show is true,
// determines winning team display and triggers presentation events.
void __thiscall ScoreboardManager::toggleScoreboard(ScoreboardManager* this, char show)
{
    int* piVar1;
    char cVar2;
    int local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined1 local_24;
    undefined1* local_20;
    undefined4 local_1c;
    undefined4 local_18;
    code* local_14;
    undefined1* local_10;
    code* pcStack_4;

    if (show == '\0') {
        // Hide scoreboard
        if ((*(int*)((uint)this + 0x5c) != 0) && (*(int*)((uint)this + 0x5c) != 4)) {
            Timer::reset(10); // +0x5c is state enum, 0=hidden, 4=maybe transitioning
            local_2c = g_scoreboardHideDelay; // DAT_01130368
            local_28 = 0;
            local_24 = 0;
            String::set(&local_2c, 0); // clear string/timer
        }
        if (*(char*)(g_gameState + 100) == '\0') { // DAT_01130010 + 0x64
            // No game state override? Call framework update
            (*(void (__thiscall**)(uint))(**(uint**)g_framework + 0x2c))(*(uint*)g_framework); // DAT_01129a74
        }
        *(undefined1*)((uint)this + 0xcd) = 0; // some flag
        Presentation::triggerEvent("HideScoreboard", 0, g_presentationManager, 0); // DAT_00d77dc0
    } else {
        // Show scoreboard
        ScoreboardManager::clearScreen(this, 0xffffffff); // FUN_009847c0
        local_20 = (undefined1*)0x0;
        local_1c = 0;
        local_18 = 0;
        local_14 = (code*)0x0;
        SomeManager::begin(&g_someManager); // DAT_00e36da0
        piVar1 = *(int**)(g_playerManager + 0x40); // DAT_0112b9b4 + 0x40
        if (piVar1 != (int*)0x0) {
            uint uVar3 = PlayerManager::getLocalPlayer(); // FUN_008aa920
            SomeManager::addRef(uVar3); // FUN_004d3e20
            if (*(int*)((uint)this + 0x5c) == 5) { // state == 5 (match over?)
                local_30 = 0;
                cVar2 = (*(char (__thiscall**)(int*, int*))(*piVar1 + 0x10))(piVar1, &local_30);
                if ((cVar2 != '\0') && (local_30 != 0)) {
                    int iVar4 = TeamManager::getLocalTeamIndex(); // FUN_008b5310
                    char* pcVar8;
                    char* pcVar7;
                    if (iVar4 == 0) {
                        pcVar8 = "$mp_online_blue_team_uppercase";
                        pcVar7 = "$mp_online_red_team_win_uppercase";
                    } else {
                        pcVar8 = "$mp_online_blue_team_win_uppercase";
                        pcVar7 = "$mp_online_red_team_uppercase";
                    }
                    Presentation::triggerEvent("ShowWinningTeam", 0, g_presentationManager, 2, pcVar7, pcVar8);
                }
            }
        }
        if (*(int*)((uint)this + 0x5c) == 3) {
            SomeManager::otherMethod(&g_someOther); // DAT_00e36d94
        }
        undefined1* puVar6 = local_10;
        if (local_10 == (undefined1*)0x0) {
            puVar6 = &g_emptyString; // DAT_0120546e
        }
        undefined1* puVar5 = local_20;
        if (local_20 == (undefined1*)0x0) {
            puVar5 = &g_emptyString;
        }
        Presentation::triggerEvent("ShowScoreboard", 0, g_presentationManager, 2, puVar5, puVar6);
        local_2c = g_scoreboardShowTimer; // DAT_01130470
        local_28 = 0;
        local_24 = 0;
        String::set(&local_2c, 0);
        Timer::set(10); // FUN_006915c0
        if (local_10 != (undefined1*)0x0) {
            (*(code*)pcStack_4)(local_10); // release strings if allocated
        }
        if (local_20 != (undefined1*)0x0) {
            (*(code*)local_14)(local_20);
        }
    }
    *(char*)((uint)this + 0x105) = show; // +0x105 = visibility flag
    ScoreboardManager::update(this); // FUN_009837d0
    return;
}