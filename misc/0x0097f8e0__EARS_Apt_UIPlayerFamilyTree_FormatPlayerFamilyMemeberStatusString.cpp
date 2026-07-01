// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_FormatPlayerFamilyMemeberStatusString
// FUNC_NAME: PauseFamilyTreeEntry::updateStatusDisplay
// Address: 0x0097f8e0
// This function updates the status display for a family tree entry in the pause menu.
// It determines the current status (ready, guarding, attacking, etc.) from the entity's
// member data and player state, then sets the status text and a status hash (at +0x110).

void __thiscall PauseFamilyTreeEntry::updateStatusDisplay(PauseFamilyTreeEntry* this, Entity* entity)
{
    int statusId;                   // unused local? (local_1028 used in switch)
    char isWoundedFlag;
    int playerGangster;             // player's gangster (iVar5)
    int currentAction;              // local_102c: active mission action type
    undefined4* missionDataPtr;
    char* statusString;             replaces puVar7 for generic string ptr
    char* formattedTimeStr;         replaces local_1024
    undefined4 local_103c_unused;   // for destructor pair with formattedTimeStr
    undefined4 local_1038_unused;
    code* formattedTimeDestructor;  // local_1018 destructor for time string

    int familyStatusMgr = FUN_007915b0(); // getFamilyStatusDisplayManager, returns pointer to manager (local_1030). Contains player's family protection info at +0x54, etc.
    int memberData = FUN_008c12a0(entity); // getMemberDataFromEntity, returns pointer to per-member data (iVar3). NULL if not a family member.
    if (memberData == 0) {
        return;
    }

    FUN_00604be0(); // profilingBegin

    // Determine display mode: if entity has bit0 at +0x5f set, force mode 8 (crew/wounded)
    if ((*(byte*)(entity + 0x5f) & 1) == 0) {
        int unknownStatus = *(int*)(memberData + 4); // +0x4: some status code (e.g., 1=ready, 2=attacking, 3=cooldown, etc.)
        statusId = unknownStatus; // local_1028
    } else {
        statusId = 8;
    }

    currentAction = FUN_008bfe00(entity); // getActiveMissionAction, returns 1=attack, 2=bomb, 4=defend? (0 for no action)

    int playerMgr = FUN_00790d90(); // getPlayerManager
    playerGangster = FUN_006b0ee0(playerMgr); // getPlayerControlledGangster, returns pointer to gangster (or 0)

    // If there is a player gangster, set the timer text at offset 0x76 (maybe mission timer)
    if (playerGangster != 0) {
        missionDataPtr = (undefined4*)FUN_006b2160(); // getCurrentMissionData
        char* missionName = (char*)*missionDataPtr;
        if (missionName == (char*)0x0) {
            missionName = (char*)&emptyStringGlobal; // DAT_0120546e
        }
        FUN_00604c10(0x76, missionName); // setTimerText(this, 0x76, missionName)
    }

    // Format the countdown timer (memberData +0x14 is a float timer, multiplied by global time scale)
    formattedTimeStr = (char*)0x0;
    local_103c_unused = 0;
    local_1038_unused = 0;
    formattedTimeDestructor = (code*)0x0;
    int totalSeconds = (int)(*(float*)(globalTimeBase + 0x70) * globalTimeScale * *(float*)(memberData + 0x14)); // DAT_0112a53c+0x70 and DAT_00e446b4
    FUN_006042a0(totalSeconds / 60, totalSeconds % 60, &formattedTimeStr); // formatTime, returns allocated string in formattedTimeStr
    if (formattedTimeStr == (char*)0x0) {
        formattedTimeStr = (char*)&emptyStringGlobal;
    }
    FUN_00604c10(0x74, formattedTimeStr); // setTimerText(this, 0x74, formattedTimeStr)

    // Resolve status string based on statusId
    char* statusStringReact = (char*)0x0; // replaces local_1040
    undefined4 local_103c_unused2;
    undefined4 local_1038_unused2;
    code* statusDestructor = (code*)0x0; // local_1018

    switch (statusId) {
    case 1: // Ready or guarding
        if ((playerGangster == 0) || (*(int*)(playerGangster + 0x40) != *(int*)(familyStatusMgr + 0x54))) {
            // Player's gangster not guarding anyone, or guarding different family
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_ready");
            *(undefined4*)(this + 0x110) = 0xf3fd04ab; // statusHash for "ready"
        } else {
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_guarding");
            *(undefined4*)(this + 0x110) = 0x6b939ce9; // statusHash for "guarding"
        }
        break;
    case 2: // Attacking/Bombing/Defending
        if (playerGangster != 0) {
            if (currentAction == 1) {
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_attacking");
                *(undefined4*)(this + 0x110) = 0x7efd766a;
            } else if (currentAction == 2) {
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_bombing");
                *(undefined4*)(this + 0x110) = 0x39f8a10e;
            } else {
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_defending");
                *(undefined4*)(this + 0x110) = 0xe83276fc;
            }
            break;
        }
        goto defaultFallback;
    case 3: // Bomb cooldown, guarding timer, or ready
        if (playerGangster == 0) {
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_bomb_cooldown");
            *(undefined4*)(this + 0x110) = 0x163b06e7;
        } else if (*(int*)(playerGangster + 0x40) == *(int*)(familyStatusMgr + 0x54)) {
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_guarding_timer");
            *(undefined4*)(this + 0x110) = 0x510863cd;
        } else {
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_ready");
            *(undefined4*)(this + 0x110) = 0xf3fd04ab;
        }
        break;
    case 4: // Pre-bomb, pre-attack, pre-defend, moving
        if (playerGangster != 0) {
            if (currentAction == 2) {
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_pre_bomb");
                *(undefined4*)(this + 0x110) = 0x8f21f7f4;
            } else if (currentAction == 1) {
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_pre_attack");
                *(undefined4*)(this + 0x110) = 0xfe59e52e;
            } else {
                char* actionString;
                if (currentAction == 4) {
                    actionString = "$pause_family_tree_status_pre_defend";
                } else {
                    actionString = "$pause_family_tree_status_moving";
                }
                FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, actionString);
                *(undefined4*)(this + 0x110) = 0x678ee5c0;
            }
            break;
        }
        goto defaultFallback;
    case 5: // Hospital timer
        FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_hospital_timer");
        *(undefined4*)(this + 0x110) = 0x2f71c418;
        break;
    case 6: // Jail timer
        FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_jail_timer");
        *(undefined4*)(this + 0x110) = 0x7be7b138;
        break;
    default:
        goto defaultFallback;
    case 8: // Crew or wounded
        int leaderCheck = FUN_00791300(); // maybe isPlayerLeader?
        if ((leaderCheck == 0) || (isWoundedFlag = FUN_00690150(0x17), isWoundedFlag == 0)) { // check game option 0x17 (IsWounded?)
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_crew");
            *(undefined4*)(this + 0x110) = 0x259cc091;
        } else {
            FUN_006038a0(localizationContext, buffer_4112, &statusStringReact, "$pause_family_tree_status_wounded");
            *(undefined4*)(this + 0x110) = 0xc3c6a5bc;
        }
        break;
    }

    // Now set the final status text into the UI widget (at this+0xfc)
    {
        char* finalString = (char*)statusStringReact;
        if (statusStringReact == (char*)0x0) {
defaultFallback:
            finalString = (char*)&emptyStringGlobal;
        }
        FUN_005c4660(*(undefined4*)(this + 0xfc), finalString, 0x100, 0); // setWidgetText( textWidget, text, maxLen, flags )
    }

    // Free allocated strings if any
    if (statusStringReact != (char*)0x0) {
        statusDestructor(statusStringReact);
    }
    if (formattedTimeStr != (char*)0x0 && formattedTimeStr != (char*)&emptyStringGlobal) {
        formattedTimeDestructor(formattedTimeStr);
    }

    FUN_00604c00(); // profilingEnd
    return;
}