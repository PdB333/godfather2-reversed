// Xbox PDB: EARS_Apt_CrewWeaponsScreen_HandleAdvanceButton
// FUNC_NAME: GodfatherGameManager::handleCrewWeaponPurchase
void __fastcall GodfatherGameManager::handleCrewWeaponPurchase(int thisPtr)
{
    byte bVar1;
    uint uVar2;
    int iVar3;
    uint uVar4;
    char cVar5;
    int iVar7;
    uint uVar10;
    undefined4 uVar11;
    int extraout_EDX;
    int iVar12;
    undefined4 unaff_EBX;
    bool bVar13;
    
    iVar7 = DAT_01129930; // gGameManager
    uVar2 = *(uint *)(DAT_01129930 + 0x2b4); // current weapon index
    if ((uVar2 < *(uint *)(DAT_0112b9b4 + 0x2c)) && (DAT_011308b6 != '\0')) {
        bVar1 = (&DAT_011308a0)[(uint)DAT_011308b7 + *(int *)(DAT_01129930 + 0x2b8)];
        iVar3 = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + uVar2 * 4);
        uVar4 = *(uint *)(&DAT_00d8dcac + (uint)bVar1 * 0x10);
        bVar13 = *(int *)(DAT_01223484 + 0xc) != 0; // isMultiplayer
        if ((bVar13) ||
           ((iVar12 = DAT_0112b9b4,
            *(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0 &&
            ((int *)(DAT_01223484 + 0x28) != (int *)0x0)))) {
            iVar12 = *(int *)(DAT_01129930 + 0x1c0); // playerRank
            uVar10 = 4;
            if (iVar12 == 1) {
                uVar10 = 3;
            }
            else if (iVar12 == 2) {
                uVar10 = 2;
            }
            else if (iVar12 == 3) {
                uVar10 = 1;
            }
            if (uVar10 < uVar4) {
                iVar7 = FUN_009c8e50(0xf0); // allocateHudMessage
                if (iVar7 == 0) {
                    iVar7 = 0;
                }
                else {
                    iVar7 = FUN_00982280(0); // createHudMessage
                }
                FUN_00981eb0("$mp_weapon_rank_too_high"); // setHudMessageText
                *(undefined4 *)(iVar7 + 0xc) = 3; // messageType = ERROR
                *(code **)(iVar7 + 0x14) = FUN_00982b30; // messageCallback
                FUN_00982e10(); // showHudMessage
                return;
            }
            cVar5 = FUN_00962d10(*(undefined4 *)(iVar3 + 0x34),*(undefined4 *)(DAT_01129930 + 0x1bc)); // checkPlayerRank
            iVar12 = extraout_EDX;
            if (cVar5 == '\0') {
                FUN_00963050("$mp_player_rank_too_high",0); // showRankTooHighMessage
                return;
            }
        }
        *(uint *)(iVar12 + 0x34) = uVar2; // setWeaponIndex
        *(uint *)(iVar12 + 0x38) = uVar4; // setWeaponRank
        FUN_008b01c0(*(undefined4 *)(iVar7 + 0x2b4),uVar4,
                     *(undefined4 *)(&DAT_00d8dca8 + (uint)bVar1 * 0x10)); // purchaseWeapon
        if ((bVar13) && (puVar8 = (undefined4 *)FUN_0096a2c0(), puVar8 != (undefined4 *)0x0)) {
            uVar11 = *(undefined4 *)(iVar3 + 0x2c); // weaponId
            *puVar8 = uVar11;
            *(undefined4 *)(iVar7 + 0x2cc) = uVar11; // setWeaponId
            uVar11 = *(undefined4 *)(iVar3 + 0x34); // weaponRank
            puVar8[1] = uVar11;
            *(undefined4 *)(iVar7 + 0x2d0) = uVar11; // setWeaponRank
            if (*(char *)(iVar7 + 0x220) == '\0') {
                FUN_0096f820(*puVar8,puVar8[1]); // equipWeapon
            }
            else {
                FUN_00964500(*puVar8,puVar8[1],puVar8[0x17]); // equipWeaponWithAmmo
            }
        }
    }
    FUN_005a04a0("DestroyCrewWeapons",0,&DAT_00d8cdec,0); // logEvent
    FUN_00402050(&DAT_01130448,0); // clearInput
    switch(*(undefined4 *)(thisPtr + 0x18)) { // gameState
    case 0: // STATE_LOBBY
        if ((*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0) &&
           (DAT_01223484 != -0x28)) {
            iVar3 = *(int *)(iVar7 + 0xdc); // currentScreen
            if (iVar3 != 6) {
                *(undefined4 *)(iVar7 + 0xc4) = 0; // clearScreenFlags
                *(undefined4 *)(iVar7 + 0xd4) = 0;
                switch(iVar3) {
                case 1:
                    uVar11 = 9; // SCREEN_WEAPONS
                    break;
                default:
                    uVar11 = 10; // SCREEN_UPGRADES
                }
                *(undefined4 *)(iVar7 + 0xd8) = uVar11; // setNextScreen
                if (iVar3 == 4) {
                    FUN_005a04a0("HideReadyState",0,&DAT_00d8cdec,0); // hideReadyState
                }
                if (*(int *)(iVar7 + 0xdc) == 1) {
                    FUN_0096adc0(); // resetWeaponSelection
                }
                iVar3 = iVar7 + 0x10; // screenManager
                FUN_005c02f0(iVar3,&LAB_00969090,1); // registerScreenCallback
                FUN_005c02f0(iVar3,&LAB_00963ee0,1);
                FUN_005c02f0(iVar3,&LAB_0096ccb0,1);
                FUN_005c02f0(iVar3,&LAB_0096ee00,1);
                *(undefined4 *)(iVar7 + 0xdc) = 6; // setScreen = SCREEN_WEAPONS
                FUN_00965720(); // updateScreen
            }
            FUN_0089c630(); // updateNetwork
            piVar9 = (int *)thunk_FUN_00b0d810(2,0x10,0x10); // allocateNetworkMessage
            uVar6 = FUN_008a2a80(); // getNetworkType
            (**(code **)(*piVar9 + 0x2c))("JoinerStrictNAT",uVar6); // sendNetworkMessage
            (**(code **)(*piVar9 + 0x2c))("IsPlayerDon",unaff_EBX);
            FUN_00568410(piVar9,0); // freeNetworkMessage
            return;
        }
        iVar7 = *(int *)(thisPtr + 0x1c); // subState
        if (iVar7 == 0) {
            FUN_00970ca0(); // handleLobbyIdle
            return;
        }
        if (iVar7 == 1) {
            FUN_00970de0(); // handleLobbyJoining
            return;
        }
        if (iVar7 == 2) {
            FUN_009709a0(); // handleLobbyReady
            return;
        }
        break;
    case 5: // STATE_WEAPONS
        *(uint *)(iVar7 + 0x6f4) = *(uint *)(iVar7 + 0x6f4) | 4; // setWeaponFlag
        FUN_00969720(); // updateWeaponDisplay
        return;
    case 6: // STATE_UPGRADES
        FUN_00965ea0(); // handleUpgrades
        return;
    case 7: // STATE_LOADOUT
        *(uint *)(iVar7 + 0x6f4) = *(uint *)(iVar7 + 0x6f4) | 4; // setWeaponFlag
        FUN_0096cd00(); // handleLoadout
        return;
    }
    return;
}