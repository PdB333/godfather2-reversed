// FUNC_NAME: Application::processCommandLine
void __fastcall Application::processCommandLine(int *thisApp)
{
    char cVar1;
    undefined4 uVar2;
    int iVar3;
    char *_Str1;
    uint uVar4;
    char *_Str1_00;
    uint uVar5;
    undefined1 *puVar6;
    uint uVar7;
    undefined1 *puVar8;
    int aiStack_58 [3];
    code *pcStack_4c;
    int aiStack_48 [3];
    code *pcStack_3c;
    undefined1 auStack_28 [40];

    // Set "FrontendMainLoop" as the current main loop
    uVar2 = stringToId("FrontendMainLoop");
    iVar3 = findObject(uVar2); // might be getObjectById
    if (iVar3 != 0) {
        (**(code **)(*thisApp + 0x14))(uVar2); // likely setCurrentMainLoop
    }

    uVar7 = 0;
    iVar3 = getArgumentCount(); // FUN_0067bf10 -> argc
    if (iVar3 != 0) {
        do {
            _Str1 = (char *)getArgumentString(uVar7); // FUN_0067bf20 -> argv[i]
            if (_Str1 == (char *)0x0) {
                iVar3 = 1;
            }
            else {
                iVar3 = _stricmp(_Str1, "-mainloop");
            }
            if (iVar3 == 0) {
                uVar4 = getArgumentCount();
                if (uVar7 + 1 < uVar4) {
                    uVar2 = getArgumentString(uVar7 + 1);
                    uVar2 = stringToId(uVar2);
                    iVar3 = findObject(uVar2);
                    if (iVar3 != 0) {
                        (**(code **)(*thisApp + 0x14))(uVar2); // setMainLoop
                    }
                }
            }
            else {
                _Str1_00 = (char *)getArgumentString(uVar7);
                if (_Str1_00 == (char *)0x0) {
                    iVar3 = 1;
                }
                else {
                    iVar3 = _stricmp(_Str1_00, "-playerspawn");
                }
                if (iVar3 == 0) {
                    uVar4 = uVar7 + 1;
                    uVar5 = getArgumentCount();
                    if (uVar4 < uVar5) {
                        uVar2 = getArgumentString(uVar4);
                        setPlayerSpawnFile(uVar2); // FUN_004d8f00
                        cVar1 = isPlayerSpawnDataValid(); // FUN_004d8f50
                        uVar7 = uVar4;
                        if (cVar1 != '\0') {
                            uVar2 = getPlayerSpawnData(auStack_28); // FUN_004d8ce0
                            applySpawnData(uVar2); // FUN_008111a0
                        }
                    }
                }
                else {
                    if (_Str1 == (char *)0x0) {
                        iVar3 = 1;
                    }
                    else {
                        iVar3 = _stricmp(_Str1, "-stream");
                    }
                    if (iVar3 == 0) {
                        uVar4 = getArgumentCount();
                        if (uVar7 + 2 < uVar4) {
                            uVar7 = uVar7 + 1;
                            uVar2 = getArgumentString(uVar7);
                            setStreamFile(uVar2); // FUN_004d3d90
                            iVar3 = getArgumentCount();
                            if (uVar7 < iVar3 - 1U) {
                                do {
                                    uVar7 = uVar7 + 1;
                                    uVar2 = getArgumentString(uVar7);
                                    addStreamPackage(uVar2); // FUN_004d4300
                                    setStreamPriority(0x20); // FUN_004d44b0
                                    iVar3 = getArgumentCount();
                                } while (uVar7 < iVar3 - 1U);
                            }
                            finalizeStreamSetup(0x20); // FUN_004d53a0
                            initializeStreamManager(); // FUN_00411e40
                            puVar8 = (undefined1 *)thisApp[6]; // +0x18? field: streamDir1
                            if (puVar8 == (undefined1 *)0x0) {
                                puVar8 = &DAT_0120546e; // default string
                            }
                            puVar6 = (undefined1 *)thisApp[2]; // +0x08? field: streamDir2
                            if (puVar6 == (undefined1 *)0x0) {
                                puVar6 = &DAT_0120546e;
                            }
                            setStreamPaths(puVar6, puVar8); // FUN_0067c9f0
                            iVar3 = *thisApp;
                            uVar2 = stringToId("GameMainLoop");
                            (**(code **)(iVar3 + 0x14))(uVar2); // setMainLoop
                        }
                    }
                    else {
                        if (_Str1 == (char *)0x0) {
                            iVar3 = 1;
                        }
                        else {
                            iVar3 = _stricmp(_Str1, "-juice");
                        }
                        if (iVar3 != 0) {
                            if (_Str1 == (char *)0x0) {
                                iVar3 = 1;
                            }
                            else {
                                iVar3 = _stricmp(_Str1, "-gameid");
                            }
                            if (iVar3 == 0) {
                                uVar7 = uVar7 + 1;
                                uVar2 = getArgumentString(uVar7);
                                setGameId(uVar2); // FUN_004d3bc0
                                parseGameIdArgs(aiStack_58); // FUN_004d3e20
                                if (aiStack_58[0] != 0) {
                                    (*pcStack_4c)(aiStack_58[0]); // callback?
                                }
                                setGameId(uVar2); // again?
                                parseGameIdArgs(aiStack_48);
                                if (aiStack_48[0] != 0) {
                                    (*pcStack_3c)(aiStack_48[0]);
                                }
                            }
                            else if (_Str1 != (char *)0x0) {
                                _stricmp(_Str1, "-autoconnect");
                            }
                        }
                    }
                }
            }
            uVar7 = uVar7 + 1;
            uVar4 = getArgumentCount();
        } while (uVar7 < uVar4);
    }
    DAT_0110ae75 = 0; // global flag
    return;
}