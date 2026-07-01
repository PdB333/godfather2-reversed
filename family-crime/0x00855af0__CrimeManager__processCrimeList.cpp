// FUNC_NAME: CrimeManager::processCrimeList
void CrimeManager::processCrimeList(int param_CrimeArray, int param_Count)
{
    int iVar1;
    short uVar2;
    int iVar3;
    char cVar4;
    int iVar5;
    int uVar6;
    char *puVar7;
    int *puVar8;
    int iVar9;
    int local_68;
    int iStack_64;
    int *puStack_60;
    int *puStack_5c;
    char *puStack_58;
    int uStack_54;
    int uStack_50;
    code *pcStack_4c;
    int uStack_48[4]; // 16 bytes
    char auStack_38[16];
    char auStack_28[12];
    char auStack_1c[12];
    float fStack_10;
    
    // Get some singleton/manager object (e.g., CrimeManager or GameManager)
    iVar5 = getManagerSingleton(); // FUN_004a8f00
    if ((iVar5 != 0) && (*(int *)(iVar5 - 0x58) != 0)) {
        local_68 = 0;
        // Virtual call: likely findCrimeByHash or resolveCrimeID
        cVar4 = (**(code **)(*(int *)(iVar5 - 0x58) + 0x10))(0x332d5a20, &local_68);
        iVar5 = local_68;
        if ((cVar4 != 0) && (local_68 != 0)) {
            fStack_10 = globalTimeDelta; // DAT_00d75104
            if (param_Count != 0) {
                // Keep pointers to some manager fields (e.g., resource handle arrays)
                puStack_60 = (int *)(local_68 + 0x498);
                puStack_5c = (int *)(local_68 + 0x490);
                iVar9 = 0;
                iStack_64 = param_Count;
                do {
                    iVar1 = param_CrimeArray + iVar9;
                    // Build some object from the crime array entry
                    uVar6 = buildCrimeObject(iVar1, &localTempVar1, &localTempVar2, *puStack_5c, *puStack_60); // FUN_007079c0
                    uVar6 = finalizeCrimeObject(uVar6); // FUN_007079c0 second call? Actually it's same function with one arg? The decompiler shows FUN_007079c0(uVar6) which might be a different overload.
                    copyToBuffer(auStack_28, uVar6); // FUN_00853880
                    // Check if crime is active or has reward flag
                    if (*(char *)(iVar1 + 0x0d) != '\0') {
                        puStack_58 = 0;
                        uStack_54 = 0;
                        uStack_50 = 0;
                        pcStack_4c = (code *)0x0;
                        // Get crime name/description string
                        getCrimeString(local_68, &puStack_58); // FUN_00852b10
                        puVar7 = puStack_58;
                        if (puStack_58 == 0) {
                            puVar7 = &emptyString; // &DAT_0120546e
                        }
                        // Lookup some resource (e.g., reward item) using the crime's identifier
                        puVar8 = (int *)lookupResourceByString(puVar7, *(short *)(iVar1 + 0x16), 0); // FUN_004352c0
                        // Copy resource data (GUID?) into local stack
                        uStack_48[0] = *puVar8;
                        uStack_48[1] = puVar8[1];
                        uStack_48[2] = puVar8[2];
                        uStack_48[3] = puVar8[3];
                        iVar3 = *(int *)(iVar1 + 0x10); // pointer to some data
                        // Check if this is a completion/apply flag
                        if (*(char *)(iVar1 + 0x19) == '\0') {
                            uVar2 = *(short *)(iVar1 + 0x14);
                            if (iVar3 != 0) {
                                *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1; // increment refcount
                            }
                            applyCrimeReward(&uStack_48, iVar3, uVar2); // FUN_00854be0
                        }
                        else {
                            if (iVar3 != 0) {
                                *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1; // increment refcount
                            }
                            uVar6 = resolveDataFromPointer(iVar3); // FUN_004b5d30
                            setupCrimeProgress(&uStack_48, *(short *)(iVar1 + 0x16), iVar1 + 0x1c, uVar6); // FUN_00853720
                        }
                        if (puStack_58 != 0) {
                            (*pcStack_4c)(puStack_58); // call destructor/deleter
                        }
                    }
                    // Check if crime has a timer/event flag
                    if (*(char *)(iVar1 + 0x0c) != '\0') {
                        initializeTimer(auStack_38); // FUN_007011f0
                        updateCrimeTimer(auStack_38, &localTempVar1, &localTempVar2, &localTempVar3, &localTempVar4, iVar1); // FUN_00854c40
                    }
                    iVar9 = iVar9 + 0x2c; // each crime struct is 0x2C bytes
                    iStack_64 = iStack_64 + -1;
                } while (iStack_64 != 0);
                // Final check: if time delta is less than global and certain pointers are set, run cleanup
                if ((fStack_10 < globalTimeDelta) && (*(int **)(local_68 + 0x48c) != 0) && (*(int **)(local_68 + 0x494) != 0)) {
                    puStack_60 = *(int **)(local_68 + 0x48c);
                    puStack_5c = *(int **)(local_68 + 0x494);
                    finalizeCrimeProcessing(auStack_28, auStack_1c, &puStack_60, &puStack_5c, *(int *)(local_68 + 0x49c)); // FUN_00852a60
                }
            }
        }
    }
    postProcessDebug(); // FUN_00855830
    return;
}