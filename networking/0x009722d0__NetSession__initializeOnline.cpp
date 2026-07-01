// FUNC_NAME: NetSession::initializeOnline
void __fastcall NetSession::initializeOnline(int thisPtr)
{
    bool bVar1;
    char *_Source;
    int *piVar2;
    int iVar3;
    int iVar4;
    int *piVar5;
    uint uVar6;
    uint uVar7;
    bool bVar8;
    longlong lStack_8;

    uVar6 = 0;
    if (thisPtr == 0) {
        iVar3 = 0;
    }
    else {
        iVar3 = thisPtr + 0x10;
    }
    // Lock/acquire some resource
    FUN_005c02f0(iVar3, &LAB_0096ee10, 1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);

    // Reset join-in-progress flags
    *(undefined4 *)(thisPtr + 0xb8) = 0;  // +0xB8: joinInProgressTimer
    *(undefined4 *)(thisPtr + 0xbc) = 0;  // +0xBC: joinInProgressCount
    DAT_011308b4 = 1;

    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
    FUN_005c0260(-(uint)(thisPtr != 0) & thisPtr + 0x10U, &LAB_0096ee10, 1);

    // Log platform
    FUN_005a04a0("SetPlatform", 0, &DAT_00d8cdec, 1, &DAT_00d85114);

    // Initialize input/controller
    FUN_008a08c0();

    // Clear skipIntro flag (bit 19)
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xffe8ffff; // +0x6F4: flags
    *(undefined4 *)(thisPtr + 0x700) = 0; // +0x700: someTimer

    // Platform check: if not PC (platform != 8)
    if (*(int *)(DAT_012234b8 + 0x10) != 8) {
        // On console: set bit 19 in flags? Actually clearing bit 19 again? No, it's clearing bit 16? Wait: 0xfff7ffff clears bit 19? 0xfff7ffff = 0b1111 1111 1111 0111 1111 1111 1111 1111? Actually 0xfff7ffff = 0b1111 1111 1111 0111 1111 1111 1111 1111, which clears bit 19 (value 0x80000). Yes.
        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfff7ffff;
        *(undefined4 *)(thisPtr + 0xdc) = 0; // +0xDC: some field
        FUN_0096ef50(); // maybe "startPlatformSpecific"
        DAT_011308b5 = 0;
        goto LAB_009727f4;
    }

    // PC path
    bVar1 = true;
    _Source = (char *)FUN_00564830();  // get player name?
    if (_Source == (char *)0x0) {
        *(undefined1 *)(thisPtr + 0x244) = 0; // +0x244: playerName[0x30]
    }
    else {
        _strncpy((char *)(thisPtr + 0x244), _Source, 0x30);
        *(undefined1 *)(thisPtr + 0x273) = 0; // null terminate
    }
    *(undefined1 *)(thisPtr + 0x27c) = 1; // +0x27C: some boolean

    piVar5 = DAT_01223484; // global singleton for network/online

    if (DAT_01223484 != (int *)0x0) {
        FUN_008a43b0(1); // maybe "enableNetwork"?

        // Check if not host or not multiplayer scenario
        if ((piVar5[3] == 0) || (((uint)piVar5[0xdf] >> 1 & 1) == 0)) {
            // Not host or not waiting for players
            if ((piVar5[10] == 0 && piVar5[0xb] == 0) || (piVar5 == (int *)0xffffffd8)) {
                DAT_011308b5 = 0;
            }
            else if (((*(uint *)(thisPtr + 0x6f4) >> 0x13 & 1) == 0) && // skip intro flag
                     (*(char *)(thisPtr + 0x2e0) == '\0')) { // +0x2E0: some string?
                FUN_009718a0(); // show intro sequence?
            }
        }
        else {
            // Host and waiting for players
            *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfff7ffff; // clear skipIntro
            *(float *)(thisPtr + 0x700) = (float)piVar5[0xf5] + DAT_00e44620; // set timer
            FUN_0095ecd0(); // update timer?
            *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffffffe; // clear bit 0
            *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) | 4; // set bit 2
            bVar1 = false;

            if (piVar5[2] == 0) { // not quickmatch
                FUN_0096cd00(); // maybe "startLobby"?
                uVar7 = FUN_009625a0(); // get player count
                if (uVar7 != 0) {
                    do {
                        iVar3 = FUN_0096afd0(piVar5, uVar6); // get player object
                        piVar2 = (int *)(**(code **)(*(int *)piVar5[3] + 8))(); // get something from scenario
                        iVar4 = (**(code **)(*piVar2 + 0xc))(); // get player id?
                        if (*(int *)(iVar3 + 0x5c) == iVar4) {
                            piVar2 = (int *)FUN_0096aef0(0); // find local player?
                            *piVar2 = iVar3;
                        }
                        else {
                            (**(code **)(*(int *)(thisPtr + 0x378) + 0x88))(iVar3); // spawn player? +0x378: spawn handler
                        }
                        uVar6 = uVar6 + 1;
                    } while (uVar6 < uVar7);
                }
                if (((uint)piVar5[0xdf] >> 6 & 1) == 0) {
                    FUN_00963050("$mp_waiting_for_host_return", 0); // show waiting message
                }
                else {
                    FUN_00964580(**(undefined4 **)(thisPtr + 0x3c4)); // +0x3C4: some pointer
                    FUN_009645f0(); // start match?
                }
            }
            else {
                // Quickmatch path
                bVar8 = false;
                piVar2 = (int *)FUN_00ad8d40(); // get GodfatherGameManager?
                if ((piVar2 != (int *)0x0) && (iVar3 = (**(code **)(*piVar2 + 0x34))(), iVar3 != 0)) {
                    piVar2 = (int *)(**(code **)(*piVar2 + 0x34))();
                    piVar2 = (int *)(**(code **)(*piVar2 + 0x3c))();
                    if (piVar2 != (int *)0x0) {
                        piVar2 = (int *)(**(code **)(*piVar2 + 0x78))();
                        iVar3 = (**(code **)(*piVar2 + 0x30))("DonFlow", 4);
                        bVar8 = iVar3 == 1;
                    }
                }
                FUN_008a3c40(thisPtr + 0x1a8); // init career?
                if (*(char *)(thisPtr + 500) != '\0') { // +0x1F4? Actually offset 500 = 0x1F4
                    // Check funds
                    *(uint *)(thisPtr + 0x1e4) = (-(uint)bVar8 & 0xfffffffd) + 4;
                    lStack_8 = (longlong)ROUND(*(float *)(DAT_01129908 + 0x14));
                    *(uint *)(thisPtr + 0x1e8) = (uint)lStack_8;
                    if ((uint)lStack_8 < *(uint *)(thisPtr + 0x1e0)) {
                        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffffffb; // clear bit 2
                        (**(code **)(*piVar5 + 0x80))(); // deactivate?
                        iVar3 = FUN_009c8e50(0xf0); // allocate popup
                        if (iVar3 == 0) {
                            iVar3 = 0;
                        }
                        else {
                            iVar3 = FUN_00982280(0);
                        }
                        FUN_00981eb0("$mp_insufficient_funds_play");
                        *(undefined4 *)(iVar3 + 0xc) = 8; // popup type
                        *(code **)(iVar3 + 0x14) = FUN_00982b30; // callback
                        FUN_00982e10(); // show popup
                        goto LAB_00972713;
                    }
                }
                FUN_0095cf20(); // maybe "startMatch"?
                *(undefined1 *)(thisPtr + 0x220) = 1; // +0x220: matchStarted
                FUN_0095c280(1); // set ready
                FUN_008a3be0(thisPtr + 0x1a8); // save career?
                FUN_0095c760(); // sync?
                if ((DAT_0112b9b4 != 0) && // some global
                   (iVar3 = FUN_00963f80(*(undefined4 *)(thisPtr + 0x1b8)), iVar3 != 0)) {
                    // Iterate over player objects
                    uVar6 = *(uint *)(iVar3 + 8);
                    uVar7 = 0;
                    if (uVar6 != 0) {
                        do {
                            iVar4 = *(int *)(*(int *)(iVar3 + 4) + uVar7 * 4);
                            if (iVar4 != 0) {
                                lStack_8 = FUN_0095c290(iVar4 + 0x17c, iVar4 + 0x180);
                                FUN_0095e000(&lStack_8); // send sync data?
                            }
                            uVar7 = uVar7 + 1;
                        } while (uVar7 < uVar6);
                    }
                }
                FUN_00969720(); // maybe "finalizeMatch"
                uVar6 = FUN_009625a0(); // get player count again
                if (uVar6 != 0) {
                    uVar7 = 0;
                    do {
                        iVar3 = FUN_0096afd0(piVar5, uVar7);
                        piVar2 = (int *)(**(code **)(*(int *)piVar5[3] + 8))();
                        iVar4 = (**(code **)(*piVar2 + 0xc))();
                        if (*(int *)(iVar3 + 0x5c) == iVar4) {
                            piVar2 = (int *)FUN_0096aef0(0);
                            *piVar2 = iVar3;
                        }
                        else {
                            (**(code **)(*(int *)(thisPtr + 0x2ec) + 0x88))(iVar3); // spawn player? +0x2EC: different handler
                            *(undefined1 *)(iVar3 + 0x59) = 1; // mark as spawned?
                        }
                        uVar7 = uVar7 + 1;
                    } while (uVar7 < uVar6);
                }
                FUN_009644b0(); // finalize sync?
            }
        }
    }

LAB_00972713:
    if ((*(uint *)(thisPtr + 0x6f4) >> 0x13 & 1) != 0) { // check skip intro flag
        FUN_00967ec0(piVar5[0xe5]); // skip intro?
    }

    if (DAT_00e574a8 != '\0') {
        // Check firewall warning
        DAT_00e574a8 = '\0';
        piVar5 = (int *)FUN_00ad8d40();
        if (((piVar5 != (int *)0x0) &&
            (piVar5 = (int *)(**(code **)(*piVar5 + 0x30))(), piVar5 != (int *)0x0)) &&
           (iVar3 = (**(code **)(*piVar5 + 0x50))(), iVar3 == 0)) {
            iVar3 = FUN_009c8e50(0xf0);
            if (iVar3 == 0) {
                iVar3 = 0;
            }
            else {
                iVar3 = FUN_00982280(0);
            }
            FUN_00981eb0("$ui_online_firewall_warning");
            *(undefined4 *)(iVar3 + 0xc) = 8;
            *(code **)(iVar3 + 0x14) = FUN_00982b30;
            FUN_00982e10();
        }
    }

    if (bVar1) {
        FUN_0095e490(); // maybe "finalizeInitialization"
        *(undefined4 *)(thisPtr + 0x6f8) = 0; // +0x6F8: some flag
    }

    FUN_008b6290(&LAB_00964020, &LAB_0096e700); // setup callbacks?
    FUN_00965720(); // start network thread?

LAB_009727f4:
    FUN_00408680(&DAT_012069c4); // maybe "signalEvent"?
    FUN_0095ecd0(); // update timers?
    return;
}