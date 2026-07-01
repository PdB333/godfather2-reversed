// Xbox PDB: EARS_Apt_CrewWeaponsScreen_ShowScreen
// FUNC_NAME: CrewWeaponManager::openCrewWeapons
void __thiscall CrewWeaponManager::openCrewWeapons(void *pThis, undefined4 param2, undefined4 param3)
{
    int gameState;
    int iVar1;
    uint uVar2;
    undefined4 uState;
    
    *(undefined4 *)((int)pThis + 0x18) = param2;   // +0x18: likely UI element ID or index
    *(undefined4 *)((int)pThis + 0x1c) = param3;   // +0x1c: additional data
    GameManager *pGameManager = g_pGameManager;     // global singleton at 0x01129930
    if (*(char *)((int)pGameManager + 0x144) != '\0') { // +0x144: flag indicating UI enabled?
        DebugLog(&g_debugState, 0);                  // FUN_00402050(&DAT_01130448,0) – debug log
        pGameManager->field_0x2b4 = 0;               // +0x2b4: some counter/flag
        pGameManager->field_0x2b8 = 0;               // +0x2b8: same
        FUN_00967950();                              // unknown: maybe reset UI state
        ScriptCall("ShowCrewWeapons", 0, &g_scriptContext, 0); // FUN_005a04a0
        *(int *)((int)pThis + 4) = 1;                // +0x04: internal flag set to 1
        gameState = *(int *)((int)pGameManager + 0xdc); // +0xdc: current game state (e.g., menu state)
        if (gameState != 0xb) {                      // 0xb = 11, a specific state (maybe "crew weapon menu")
            pGameManager->field_0xc4 = 0;             // +0xc4: clear state data
            pGameManager->field_0xd4 = 0;             // +0xd4: clear state data
            switch(gameState) {
            case 1:  // e.g., "idle"
            case 6:  // e.g., "in car"
                uState = 9;
                break;
            default:
                uState = 10;
            }
            pGameManager->field_0xd8 = uState;        // +0xd8: store new state
            if (gameState == 4) {                     // e.g., "driving"
                ScriptCall("HideReadyState", 0, &g_scriptContext, 0); // FUN_005a04a0
            }
            if (gameState == 1) {
                FUN_0096adc0();                       // maybe enable ready state
            }
            iVar1 = (int)pGameManager + 0x10;         // +0x10: pointer to some callback list
            RegisterCallback(iVar1, &LAB_00969090, 1); // FUN_005c02f0 – register callbacks
            RegisterCallback(iVar1, &LAB_00963ee0, 1);
            RegisterCallback(iVar1, &LAB_0096fba0, 1);
            RegisterCallback(iVar1, &LAB_0096ccb0, 1);
            RegisterCallback(iVar1, &LAB_0096ee00, 1);
            pGameManager->field_0xdc = 0xb;           // set state to "crew weapon menu"
            FUN_00965720();                            // finalize setup
        }
        FUN_00967450();                                // refresh UI elements
        FUN_00967800();                                // update list
        FUN_009676f0();                                // update icons
        FUN_009679c0();                                // display
        ScriptCall("ShowWeaponsList", 0, &g_scriptContext, 0); // FUN_005a04a0
    }
    return;
}