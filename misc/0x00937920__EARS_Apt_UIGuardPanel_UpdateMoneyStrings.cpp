// Xbox PDB: EARS_Apt_UIGuardPanel_UpdateMoneyStrings
// FUNC_NAME: DebugMenu::updateGuardCostHint
void __fastcall DebugMenu::updateGuardCostHint(int this)
{
    undefined4 uVar1;
    int iVar2;
    int iVar3;
    undefined1 *puVar4;
    int iVar5;
    int iVar6;
    float10 fVar7;
    float fVar8;
    float *pFloatData;
    undefined1 *local_1028;
    undefined4 local_1024;
    undefined4 local_1020;
    code *local_101c;
    int local_1018;
    undefined1 local_1014[4112];
    undefined4 uStack_4;

    uVar1 = DAT_012234a4; // Global data handle
    uStack_4 = 0x93792a; // Return address for debug

    // Retrieve pointer to some data object from this+0x6c->+0x40,
    // then grab float pointer at offset 0x230 of that object.
    iVar2 = getEntityHandle(*(undefined4 *)(*(int *)(this + 0x6c) + 0x40));
    if (iVar2 == 0) {
        pFloatData = (float *)0x0;
    }
    else {
        pFloatData = *(float **)(iVar2 + 0x230);
    }

    if (pFloatData != (float *)0x0) {
        // Likely reading a random/timing value
        fVar7 = (float10)getRandomFloat();
        getRandomFloat();
        local_1018 = getRandomInt(); // e.g. rand()

        // Possibly map the random value into a small integer offset
        if ((float)fVar7 == (float)local_1018) {
            fVar7 = (float10)getRandomFloat();
            fVar8 = (float)fVar7;
        }
        else {
            fVar7 = (float10)getRandomFloat();
            if (fVar7 <= (float10)0) {
                getRandomFloat();
                iVar2 = getRandomInt();
                iVar2 = iVar2 + -1;
            }
            else {
                getRandomFloat();
                iVar2 = getRandomInt();
                iVar2 = iVar2 + 1;
            }
            fVar8 = (float)iVar2;
        }
        iVar6 = (int)fVar8;

        // Additional RNG state updates
        seedRandom();
        seedRandom();
        local_1018 = getRandomInt();
        advanceRandom();
        advanceRandom();
        iVar3 = getRandomInt();

        // Fetch a count from this+0x58
        iVar2 = *(int *)(this + 0x58);
        if (iVar2 < 1) {
            iVar5 = 0;
        }
        else {
            iVar5 = iVar2 * iVar6;
        }

        fVar8 = *pFloatData; // base float from the data object

        // Begin string construction
        local_1028 = (undefined1 *)0x0;
        local_1024 = 0;
        local_1020 = 0;
        local_101c = (code *)0x0;
        formatString(iVar6, &local_1028, 1);
        concatString();
        puVar4 = local_1028;
        if (local_1028 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        prependString(0x70, puVar4);
        formatStringWithKey(uVar1, local_1014, &local_1028, "$strat_guard_cost_hint");
        puVar4 = local_1028;
        if (local_1028 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        // Output to four display slots
        outputTextToDisplay(*(undefined4 *)(this + 0x68), puVar4, 0x80, local_1024);
        formatString(iVar2 * iVar6 + iVar3, &local_1028, 1);
        puVar4 = local_1028;
        if (local_1028 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        outputTextToDisplay(*(undefined4 *)(this + 0x5c), puVar4, 0x10, local_1024);
        formatString(local_1018, &local_1028, 1);
        puVar4 = local_1028;
        if (local_1028 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        outputTextToDisplay(*(undefined4 *)(this + 0x60), puVar4, 0x10, local_1024);
        formatString((int)fVar8 - iVar5, &local_1028, 1);
        puVar4 = local_1028;
        if (local_1028 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
        }
        outputTextToDisplay(*(undefined4 *)(this + 100), puVar4, 0x10, local_1024);
        cleanUpString();
        if (local_1028 != (undefined1 *)0x0) {
            (*local_101c)(local_1028);
        }
    }
    return;
}