// Xbox PDB: EARS_Apt_PersonalScreen_PopulateOn
// FUNC_NAME: MultiplayerScoreScreen::buildPersonalScoreTable
void __thiscall MultiplayerScoreScreen::buildPersonalScoreTable(int thisPtr, char* leftColumnBuf, char* rightColumnBuf)
{
    char* valueStr;
    int valInt;
    char* sourceStr;
    int tempInt;
    char* tmpStr;
    int a1;
    char** ppStr;
    int retVal;
    float floatVal;
    char* localBuffer;
    int localSize;
    int localFlags;
    code* localDeleter;
    char* localBuffer2;
    int localSize2;
    int localFlags2;
    code* localDeleter2;

    localBuffer = 0;
    localSize = 0;
    localFlags = 0;
    localDeleter = 0;

    // Round ranking
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_round_ranking", 0x80, 0); // FUN_005c4660
    valInt = getRoundRankingScore(); // FUN_0092e470
    if (valInt == -1) {
        printError(&DAT_00d68478); // FUN_004d3d90
    } else {
        retVal = 1;
        ppStr = &localBuffer;
        a1 = getRoundRankingScore(ppStr, 1); // overload? Actually calls same with args
        formatIntegerToString(a1, ppStr, retVal); // FUN_00603d30
    }
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString; // DAT_0120546e
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, localSize);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0); // FUN_005a04a0

    // Label and value pairing helper (FUN_0092e3f0?) - maybe sync ?
    FUN_0092e3f0(leftColumnBuf, rightColumnBuf); // Likely sets the two columns for a row

    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Top player
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_top_player", 0x80, 0);
    if ((*(int*)(DAT_0112ebb4 + 0xf4) == 0) || (*(int*)(DAT_0112ebb4 + 0x16c) == 0)) {
        sourceStr = "$mp_finalscore_no_top_player";
    } else {
        tempInt = getPlayerFromHandle(*(undefined4*)(DAT_0112ebb4 + 0xf0)); // FUN_004baf60
        if (tempInt == 0) {
            sourceStr = "$mp_finalscore_no_top_player";
        } else {
            tmpStr = (char*)getPlayerName(tempInt); // FUN_004bb600
            sourceStr = (char*)*tmpStr;
            if (sourceStr == 0) {
                sourceStr = &emptyString;
            }
        }
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Most executions
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_most_executions", 0x80, 0);
    if (*(int*)(DAT_0112ebb4 + 0x16c) != 0) {
        retVal = getMostExecutionsPlayer(); // FUN_008a6170
        tempInt = getPlayerFromHandle(retVal); // FUN_004baf60
        if (tempInt != 0) {
            tmpStr = (char*)getPlayerName(tempInt); // FUN_004bb600
            sourceStr = (char*)*tmpStr;
            if (sourceStr == 0) {
                sourceStr = &emptyString;
            }
            goto label_mostExec;
        }
    }
    sourceStr = "$mp_finalscore_no_most_executions";
label_mostExec:
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Kills
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_kills", 0x80, 0);
    retVal = 1;
    ppStr = &localBuffer;
    a1 = getKills(ppStr, 1); // FUN_0092ee80
    formatIntegerToString(a1, ppStr, retVal); // FUN_00603d30
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString;
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Deaths
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_deaths", 0x80, 0);
    retVal = 1;
    ppStr = &localBuffer;
    a1 = getDeaths(ppStr, 1); // FUN_0092ef20
    formatIntegerToString(a1, ppStr, retVal);
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString;
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // KDR
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_kdr", 0x80, 0);
    retVal = 1;
    ppStr = &localBuffer;
    a1 = 2;
    floatVal = (float)getKDR(2, ppStr, 1); // FUN_0092f1e0
    formatFloatToString(floatVal, a1, ppStr, retVal); // FUN_00603da0
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString;
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, localSize);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Executions performed
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_executions_performed", 0x80, 0);
    if (*(int**)(DAT_012233a0 + 4) == 0) {
        tempInt = 0;
    } else {
        tempInt = *(int*)(DAT_012233a0 + 4) - 0x1f30; // offset to something
    }
    if ((*(int*)(DAT_0112ebb4 + 0x16c) != 0) && (tempInt != 0)) {
        valInt = getExecutionsPerformed(*(undefined4*)(tempInt + 0x1ef8)); // FUN_008a6100
    } else {
        valInt = 0;
    }
    formatIntegerToString(valInt, &localBuffer, 1);
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString;
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Headshots
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_headshots", 0x80, 0);
    if (*(int**)(DAT_012233a0 + 4) == 0) {
        tempInt = 0;
    } else {
        tempInt = *(int*)(DAT_012233a0 + 4) - 0x1f30;
    }
    if ((*(int*)(DAT_0112ebb4 + 0x16c) != 0) && (tempInt != 0)) {
        valInt = getHeadshots(*(undefined4*)(tempInt + 0x1ef8)); // FUN_008a6200
    } else {
        valInt = 0;
    }
    formatIntegerToString(valInt, &localBuffer, 1);
    sourceStr = localBuffer;
    if (localBuffer == 0) {
        sourceStr = &emptyString;
    }
    copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Favorite victim
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_favorite_victim", 0x80, 0);
    retVal = getFavoriteVictim(0x80, 0); // FUN_0092e600
    copyLocalizedString(rightColumnBuf, retVal);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Biggest enemy
    copyLocalizedString(leftColumnBuf, "$mp_finalscore_biggest_enemy", 0x80, 0);
    retVal = getBiggestEnemy(0x80, 0); // FUN_0092e680
    copyLocalizedString(rightColumnBuf, retVal);
    addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

    // Player cut / Don's cut (if player is a don)
    if ((DAT_0112ebb4 != 0) && (*(char*)(DAT_0112ebb4 + 0x124) != '\0')) {
        localBuffer2 = 0;
        localSize2 = 0;
        localFlags2 = 0;
        localDeleter2 = 0;

        if (isPlayerDon() == false) { // FUN_0089c630
            copyLocalizedString(leftColumnBuf, "$mp_player_cut", 0x80, 0);
            valInt = *(int*)(thisPtr + 4);
        } else {
            if (*(char*)(thisPtr + 8) == '\0') {
                valInt = -*(int*)(thisPtr + 0x10);
            } else {
                valInt = *(int*)(thisPtr + 0x10) - *(int*)(thisPtr + 0xc);
            }
            copyLocalizedString(leftColumnBuf, "$mp_dons_cut", 0x80, 0);
        }
        formatIntegerToString(valInt, &localBuffer2, 1); // FUN_00604000
        sourceStr = localBuffer2;
        if (localBuffer2 == 0) {
            sourceStr = &emptyString;
        }
        copyLocalizedString(rightColumnBuf, sourceStr, 0x80, 0);
        addRowToTable("AddPersonalRow", 0, &DAT_00d88e88, 0);

        if (localBuffer2 != 0) {
            (*localDeleter2)(localBuffer2); // free the allocated string
        }
    }

    if (localBuffer != 0) {
        (*localDeleter)(localBuffer);
    }
    return;
}