// Xbox PDB: EARS_Apt_UIOnlineMenu_HandleMainMenu
// FUNC_NAME: LobbyManager::tick
// Function address: 0x009733d0
// Role: Main state machine for multiplayer lobby session (host/join, wager, ready states)
// Note: Uses __fastcall (this in ECX), param_1 is 'this' pointer

void __fastcall LobbyManager::tick(int *thisPtr)
{
    bool bSuccess;
    char cResult;
    uint uIdx;
    int iVar4;
    int iVar5;
    char *pcVar6;
    int iVar7;
    uint uVar8;
    char *pcVar9;
    int *piVar10;
    uint uVar11;
    longlong *plVar12;
    char *pcVar13;
    uint uVar14;
    longlong local_40_struct;
    int local_38_val;
    code *local_34_func;
    char *local_30_ptr;
    int local_2c_val;
    int local_28_val;
    code *local_24_func;
    char *local_20_ptr;
    int *local_1c_ptr;
    int local_18_val;
    code *local_14_func;
    char *local_10_ptr;
    char *pcStack_c;
    int uStack_8;
    code *local_4_func;

    // Guard: only proceed if global session phase is 8
    if (*(int *)(DAT_012234b8 + 0x10) != 8)
        return;

    switch (thisPtr[0x37])  // offset +0xDC: lobbyState
    {
    case 0:  // Initial / lobby setup
        switch (thisPtr[0x31])  // offset +0xC4: substate
        {
        case 0: // Substate: create lobby / host setup
            uStack_8 = 0;
            pcStack_c = (char *)&DAT_01130448;   // some debug string
            local_10_ptr = (char *)0x973225;
            FUN_00402050();   // likely printf or log

            iVar4 = thisPtr[0x37];   // re-read state? (still 0)
            if (iVar4 != 8) {
                // Transition to active states
                thisPtr[0x31] = 0;
                thisPtr[0x35] = 0;
                switch (iVar4) {
                case 1:
                case 6:
                    iVar7 = 9;
                    break;
                default:
                    iVar7 = 10;
                }
                thisPtr[0x36] = iVar7;  // some counter/timer

                if (iVar4 == 4) {
                    uStack_8 = 0;
                    pcStack_c = "onli";
                    local_10_ptr = 0x0;
                    local_14_func = (code *)0xd8f2f4;
                    local_18_val = 0x973284;
                    FUN_005a04a0();  // debug trace
                }
                if (thisPtr[0x37] == 1) {
                    uStack_8 = 0x97329b;
                    FUN_0096adc0();  // likely create network session
                }

                // Register 5 callbacks? (using some UI setup)
                pcStack_c = (char *)0x1;
                piVar10 = thisPtr + 4;
                local_10_ptr = (char *)0x969090;
                local_18_val = 0x9732ae;
                local_14_func = (code *)piVar10;
                FUN_005c02f0();  // UI callback registration

                pcStack_c = (char *)0x1;
                local_10_ptr = (char *)0x963ee0;
                local_18_val = 0x9732bd;
                local_14_func = (code *)piVar10;
                FUN_005c02f0();

                pcStack_c = (char *)0x1;
                local_10_ptr = (char *)0x96fba0;
                local_18_val = 0x9732cc;
                local_14_func = (code *)piVar10;
                FUN_005c02f0();

                pcStack_c = (char *)0x1;
                local_10_ptr = (char *)0x96ccb0;
                local_18_val = 0x9732db;
                local_14_func = (code *)piVar10;
                FUN_005c02f0();

                pcStack_c = (char *)0x1;
                local_10_ptr = (char *)0x96ee00;
                local_18_val = 0x9732ea;
                local_14_func = (code *)piVar10;
                FUN_005c02f0();

                thisPtr[0x37] = 8;
                pcStack_c = "^j";
                FUN_00965720();  // some network send?
            }

            // Further initialization
            uStack_8 = 0;
            pcStack_c = "onli";
            local_10_ptr = 0x0;
            local_14_func = (code *)0xd8ec00;
            local_18_val = 0x97330f;
            FUN_005a04a0();

            local_18_val = 0;
            local_1c_ptr = (int *)&DAT_00d8cdec;
            local_20_ptr = 0x0;
            local_24_func = (code *)0xd8f338;
            local_28_val = 0x973322;
            FUN_005a04a0();

            // Set ready state to true
            uStack_8 = 2;
            pcStack_c = (char *)0x0;
            *(char *)(thisPtr + 0x51) = 1;   // offset +0x144
            local_10_ptr = (char *)0x97333b;
            FUN_009710e0();   // UI update
            return;

        case 1: // Substate: waiting for players / join check
            if (DAT_01223484 != 0) {   // online check
                uStack_8 = 0x97334c;
                cResult = FUN_008a2a80();   // is network available?
                if (cResult != '\0') {
                    uStack_8 = 0;
                    pcStack_c = "$mp_host_strict_nat";
                    local_10_ptr = (char *)0x97337d;
                    FUN_00963050();   // show error text
                    return;
                }
            }
            uStack_8 = 0;
            pcStack_c = (char *)&DAT_01130448;
            local_10_ptr = (char *)0x973361;
            FUN_00402050();
            uStack_8 = 1;
            pcStack_c = (char *)0x97336d;
            FUN_00973170();   // start hosting?
            break;

        case 2: // Substate: searching for games
            uStack_8 = 0;
            pcStack_c = (char *)0x973386;
            FUN_00973170();   // continue search?
            return;

        case 3: // Substate: joining a game
            uStack_8 = 0;
            pcStack_c = (char *)&DAT_01130448;
            local_10_ptr = (char *)0x973394;
            FUN_00402050();
            // Indirect virtual call: (**(code **)(*DAT_01130044 + 0x28))();
            // Likely calling a join method on some global manager
            (**(code **)(*(int *)DAT_01130044 + 0x28))();
            return;
        }
        return;

    case 1: // Waiting for players to arrive
        // Check if there are pending players to process
        if ((thisPtr[0x5f] != 0) &&   // count > 0
            ((uint)(thisPtr[0x35] + thisPtr[0x31]) < (uint)thisPtr[0x5f]) &&
            (DAT_01223484 != 0))
        {
            uVar8 = *(int *)(thisPtr[0x5e] + (thisPtr[0x35] + thisPtr[0x31]) * 4);
            FUN_0096c1d0(uVar8);   // process pending player
        }
        break;

    case 2: // Creating game
        uVar8 = 7;
        if (((char)thisPtr[0x7d] == '\0') &&   // not bot
            (iVar4 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4),
             iVar4 != 0))
        {
            uVar8 = *(int *)(iVar4 + 0x34);   // player's client ID
        }
        cResult = FUN_00962d10(uVar8, thisPtr[0x6f]);   // version/rank check
        if (cResult == '\0') {
            FUN_00963050("$mp_player_rank_too_high", 0);
            return;
        }
        if (((thisPtr[0x6a] == 0) &&   // not already hosting
             (thisPtr[0x1bd] = thisPtr[0x1bd] | 0x2000,   // set flag
              DAT_01223484 != 0)) &&   // online
            ((uint)thisPtr[0x6c] < DAT_011307fc))   // player count under max
        {
            FUN_0096f7a0("$mp_creating_game", 0);   // display creating msg
            uVar14 = 0;
            uVar8 = FUN_0095cad0(0);   // get lobby type?
            FUN_008a42b0(thisPtr + 0x6a, uVar8, uVar14);   // start hosting
            // Call virtual method at vtable+0xc (maybe startSession)
            (**(code **)(*thisPtr + 0xc))();
            return;
        }
        break;

    case 3: // Starting game (host)
    {
        local_40_struct = CONCAT44(local_40_struct._4_4_, (int)DAT_01223484);
        if ((DAT_01223484 != 0) && ((uint)thisPtr[0x6c] < DAT_011307fc)) {
            bSuccess = true;
            // Check version/rank for all players
            if (((char)thisPtr[0x7d] == '\0') && (thisPtr[0xcf] != 0)) {
                iVar4 = thisPtr[0x6f];   // host version?
                piVar10 = (int *)thisPtr[0xce];   // player list
                iVar7 = thisPtr[0xcf];   // player count
                do {
                    cResult = FUN_00962d10(*(int *)(*piVar10 + 4), iVar4);
                    if (cResult == '\0') {
                        bSuccess = false;
                    }
                    piVar10 = (int *)((int)piVar10 + 4);
                    iVar7--;
                } while (iVar7 != 0);
                if (!bSuccess) {
                    FUN_00963050("$mp_player_rank_too_high", 0);
                    return;
                }
            }
            // Check max players
            uVar11 = thisPtr[0xcf];
            pcVar13 = *(char **)(thisPtr[0x74] * 0x10 + DAT_01130828);
            if (pcVar13 == (char *)0x0) {
                pcVar13 = (char *)&DAT_0120546e;   // "0"?
            }
            uVar3 = _atol(pcVar13);
            if (uVar3 < uVar11) {
                FUN_00963050("$mp_max_players_less_than_current_number", 0);
                return;
            }
            // Notify online services
            piVar10 = (int *)FUN_00ad8d40();   // get online session?
            if ((piVar10 != (int *)0x0) && (iVar4 = (**(code **)(*piVar10 + 0x34))(), iVar4 != 0)) {
                piVar10 = (int *)(**(code **)(*piVar10 + 0x34))();
                piVar10 = (int *)(**(code **)(*piVar10 + 0x3c))();
                if (piVar10 != (int *)0x0) {
                    iVar4 = *piVar10;
                    uVar8 = FUN_0095cad0();
                    (**(code **)(iVar4 + 0x50))(0, uVar8);   // set lobby type?
                }
            }
            FUN_008a3be0(thisPtr + 0x6a);   // finalize hosting
            // Set each player's state
            uVar11 = 0;
            if (thisPtr[0xcf] != 0) {
                do {
                    iVar4 = *(int *)(thisPtr[0xce] + uVar11 * 4);
                    FUN_009646b0(*(int *)(iVar4 + 0x5c));   // player ID?
                    if (*(int *)(iVar4 + 0x14) == 2) {   // if bot
                        *(int *)(iVar4 + 0x10) = 2;   // set as bot
                        FUN_009642e0(2, *(int *)(iVar4 + 0x5c));   // assign team?
                    }
                    uVar11++;
                } while (uVar11 < (uint)thisPtr[0xcf]);
            }
            FUN_00402050(&DAT_01130448, 0);   // log
            FUN_00969720();   // send ready?
            // Call virtual method at offset +0x94 of some object
            (**(code **)(thisPtr[0xbb] + 0x94))();   // start game?
            return;
        }
        break;
    }

    case 4: // Ready state (all players ready)
        if (((((char)thisPtr[0x88] != '\0') && (DAT_01223484 != 0)) &&
            ((uint)thisPtr[0x6c] < DAT_011307fc)) &&
            ((*(char *)((int)thisPtr + 0x6f1) != '\0' && ((char)thisPtr[0x1bc] != '\0'))))
        {
            thisPtr[0x79] = 4;   // set substate to 4
            FUN_008a3be0(thisPtr + 0x6a);   // finalize
            cResult = FUN_00964460();   // check all ready?
            if (cResult != '\0') {
                *(char *)(thisPtr + 0x1bc) = 0;   // clear client ready
                *(char *)((int)thisPtr + 0x6f1) = 0;   // clear host ready
                // Log ready state false for both
                FUN_005a04a0("SetHostReadyState", 0, &DAT_00d8cdec, 1, "false");
                FUN_005a04a0("SetClientReadyState", 0, &DAT_00d8cdec, 1, "false");
                FUN_00402050(&DAT_01130448, 0);
                FUN_00962d80();   // clear some state
                FUN_00969720();   // send ready false?
                // Call virtual method (same as above)
                (**(code **)(thisPtr[0xbb] + 0x94))();   // transition to game?
                return;
            }
        }
        break;

    case 5: // Disconnect / leave lobby
        FUN_0096dda0();   // cleanup
        return;

    case 6: // Joining game (client side)
        if ((thisPtr[0x5f] != 0) && ((uint)(thisPtr[0x35] + thisPtr[0x31]) < (uint)thisPtr[0x5f])) {
            int index = (thisPtr[0x35] + thisPtr[0x31]) * 4;
            int playerData = *(int *)(thisPtr[0x5e] + index);
            iVar5 = FUN_00964d50(playerData + 0x4d);   // check version?
            if (iVar5 == 0) {
                // Version matches
                if ((((uint)thisPtr[0x1bd] >> 2 & 1) != 0) || (DAT_0112b9b4 == 0)) {
                    goto handle_version_mismatch;
                }
                iVar4 = *(int *)(playerData);   // player struct?
                iVar5 = FUN_00963f80(*(int *)(iVar4 + 0x10));   // check if in game?
                if (iVar5 == 0) {
                    handle_version_mismatch:
                    FUN_009631c0();   // show error?
                    return;
                }
                if ((char)thisPtr[0x7d] != '\0') {
                    // Bot join
                    thisPtr[0x67] = *(int *)(iVar4 + 0x100);   // wager amount?
                    thisPtr[0x68] = *(int *)(iVar4 + 0xfc);
                    int globalPlayer = DAT_01129930;
                    if (*(int *)(iVar4 + 0x38) == 0) {
                        // No wager needed
                        *(uint *)(DAT_01129930 + 0x6f4) = *(uint *)(DAT_01129930 + 0x6f4) | 2;
                        FUN_0096f920(*(int *)(globalPlayer + 0x1a0), *(int *)(globalPlayer + 0x19c));
                        return;
                    }
                    // Wager required
                    iVar7 = FUN_009c8e50(0xf0);   // malloc?
                    if (iVar7 == 0) {
                        iVar7 = 0;
                    } else {
                        iVar7 = FUN_00982280(0);   // UI handle?
                    }
                    DAT_011307f0 = 0;
                    FUN_0095ecd0();   // maybe clear UI?
                    // Round float
                    local_40_struct = (longlong)ROUND(*(float *)(DAT_01129908 + 0x14));
                    if ((uint)local_40_struct < *(uint *)(iVar4 + 0x38)) {
                        // Insufficient funds
                        thisPtr[0x68] = -1;
                        thisPtr[0x67] = -1;
                        FUN_00981eb0("$mp_insufficient_funds_join");
                        *(int *)(iVar7 + 0xc) = 3;
                        *(code **)(iVar7 + 0x14) = FUN_00982b30;   // set callback
                    } else {
                        // Show wager accept dialog
                        FUN_00981ec0("$mp_accept_wager");
                        // Initialize some local strings
                        local_20_ptr = 0x0;
                        local_1c_ptr = 0x0;
                        local_18_val = 0;
                        local_14_func = 0x0;
                        local_30_ptr = 0x0;
                        local_2c_val = 0;
                        local_28_val = 0;
                        local_24_func = 0x0;
                        local_40_struct = 0;
                        local_38_val = 0;
                        local_34_func = 0x0;
                        FUN_00604000(*(int *)(iVar4 + 0x38), &local_30_ptr, 1);   // format wager
                        uVar14 = 1;
                        plVar12 = &local_40_struct;
                        uVar8 = FUN_0095c2a0(plVar12, 1);
                        FUN_00603f90(uVar8, plVar12, uVar14);   // concatenate?
                        // Build description string
                        pcVar6 = (char *)local_40_struct;
                        if (pcVar6 == (char *)0x0) {
                            pcVar6 = (char *)&DAT_0120546e;
                        }
                        pcVar9 = local_30_ptr;
                        if (pcVar9 == (char *)0x0) {
                            pcVar9 = (char *)&DAT_0120546e;
                        }
                        FUN_004d4a60(&local_10_ptr, 1, "{w:%s}{p:%s}{$mp_accept_wager_description}", pcVar9, pcVar6);
                        pcVar6 = local_10_ptr;
                        if (pcVar6 == (char *)0x0) {
                            pcVar6 = (char *)&DAT_0120546e;
                        }
                        FUN_00603970(&local_20_ptr, pcVar6);
                        pcVar6 = local_20_ptr;
                        if (pcVar6 == (char *)0x0) {
                            pcVar6 = (char *)&DAT_0120546e;
                        }
                        FUN_00981eb0(pcVar6);   // show message
                        // Setup UI buttons
                        *(int *)(iVar7 + 0xc) = 9;
                        *(code **)(iVar7 + 0x14) = FUN_00982b30;
                        FUN_00981e70("$mp_online_menu_yes", 1, 0);
                        FUN_00981e70("$mp_online_menu_no", 0, 0);
                        *(char **)(iVar7 + 0x14) = (char *)0x96fb40;   // callback address
                        // Cleanup temporaries
                        if (local_10_ptr != 0x0) {
                            (local_4_func)(local_10_ptr);
                        }
                        if (local_40_struct != 0) {
                            (local_34_func)(local_40_struct);
                        }
                        if (local_30_ptr != 0x0) {
                            (local_24_func)(local_30_ptr);
                        }
                        if (local_20_ptr != 0x0) {
                            (local_14_func)(local_20_ptr);
                        }
                    }
                    FUN_00982e10();   // show dialog?
                    return;
                }
                // Non-bot join
                iVar7 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4);   // client info
                if ((iVar7 == 0) ||
                    (cResult = FUN_00962d10(*(int *)(iVar7 + 0x34), *(int *)(iVar4 + 0x14)),
                     cResult == '\0'))
                {
                    FUN_00963050("$mp_player_rank_too_high", 0);
                    return;
                }
                thisPtr[0x67] = *(int *)(iVar4 + 0x100);
                thisPtr[0x68] = *(int *)(iVar4 + 0xfc);
                thisPtr[0x1bd] = thisPtr[0x1bd] | 2;   // set flag
                FUN_0096f920(thisPtr[0x68], thisPtr[0x67]);   // show wager?
            } else {
                // Version mismatch
                local_40_struct = 0;
                local_38_val = 0;
                local_34_func = 0x0;
                switch (iVar5) {
                case 1:
                    pcVar13 = "$mp_version_host_greater";
                    break;
                case 2:
                    pcVar13 = "$mp_version_host_lower";
                    break;
                case 3:
                    pcVar13 = "$mp_version_host_invalid";
                    break;
                case 4:
                    pcVar13 = "$mp_version_client_invalid";
                    break;
                default:
                    pcVar13 = "$mp_version_unknown_error";
                }
                FUN_004d4ad0(&local_40_struct, pcVar13);
                pcVar6 = (char *)local_40_struct;
                if (pcVar6 == (char *)0x0) {
                    pcVar6 = (char *)&DAT_0120546e;
                }
                FUN_00963050(pcVar6, 0);
                if (local_40_struct != 0) {
                    (local_34_func)(local_40_struct);   // free?
                    return;
                }
            }
        }
        break;

    case 7:
    case 10:
    case 0xc:
        // No-op states (idle?)
        break;

    case 8: // Ready state callback? (substate 2)
        local_4_func = (code *)0x2;
        *(char *)(thisPtr + 0x51) = 1;   // set ready state
        uStack_8 = 0;
        pcStack_c = (char *)0x971ce6;
        FUN_009710e0();   // update UI
        return;

    case 9: // Game started? (store player count)
        thisPtr[0x1be] = thisPtr[0x6c];   // store player count
        FUN_00402050(&DAT_01130448, 0);
        thisPtr[0x1bd] = thisPtr[0x1bd] | 0x2000;   // set flag
        FUN_00965ea0();   // prepare game?
        return;

    case 0xb: // Leave game
        FUN_00971260();   // cleanup
        return;

    default:
        break;
    }
}