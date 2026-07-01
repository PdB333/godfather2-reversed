// FUNC_NAME: DonViewManager::handleEvent

void __thiscall DonViewManager::handleEvent(int eventId, int* param_2)
{
    float deltaTime;
    char isSuccess;
    undefined4 luaState;
    uint* pManager;
    char* pString;
    int local_luaState;
    undefined4 local_resultStr;
    int local_status;

    luaState = gGlobalLuaState; // DAT_012234a4

    int eventType = *param_2;
    if (eventType == kEventTimerTick) {
        updateMissionTimers(); // FUN_008bf5e0
        if ((((this->missionActive == 0) && ((this->flags & 0x40) == 0)) && (this->currentMission != 0)) &&
           ((this->flags & 0x20) == 0 && (gGameSettings->enableDonView != 0))) {
            this->missionTimer1 += gFrameDelta; // DAT_012067e8
            if (this->isTwoPhaseMission != 0) {
                this->missionTimer2 += gFrameDelta;
            }
            float timer1 = this->missionTimer1;
            if ((this->missionTimerLimit1 <= timer1 && timer1 != this->missionTimerLimit1) ||
               ((this->isTwoPhaseMission != 0 &&
                (this->missionTimerLimit2 <= this->missionTimer2 && this->missionTimer2 != this->missionTimerLimit2)) &&
                (this->missionHardLimit <= timer1 && timer1 != this->missionHardLimit))) {
                onMissionTimerExpired(); // FUN_008c6740
                return;
            }
        }
    }
    else if (eventType == kEventReserveBoat) { // DAT_0112fdf8
        int* pSingleton = *(int**)(gManagerBase + 4); // DAT_012233a0
        int localPlayerIndex;
        if (pSingleton == 0) {
            localPlayerIndex = 0;
        } else {
            localPlayerIndex = *pSingleton - 0x1f30;
        }
        if ((param_2[1] != 0) && (localPlayerIndex != 0)) {
            char isDead = checkPlayerDead(1, param_2[1]); // FUN_007a8c50
            if (isDead == 0) {
                luaState = getLuaVM(); // FUN_007351c0
                uint* pReserveManager = (uint*)getReserveManager(luaState); // FUN_008bd3c0
                if (pReserveManager != 0) {
                    *pReserveManager |= 8;
                    return;
                }
            }
        }
    }
    else {
        if (eventType == this->eventId1) { // +0x1b0
            handleEvent1(); // FUN_008c13a0
            return;
        }
        if (eventType == this->eventId2) { // +0x1b8
            local_luaState = 0;
            local_resultStr = 0;
            local_status = 0;
            isSuccess = checkJailbreakResult(); // FUN_008bf460
            if (isSuccess == 0) {
                pString = "$dv_jailbreak_fail";
            } else {
                pString = "$dv_jailbreak_success";
            }
        }
        else if (eventType == this->eventId3) { // +0x1c0
            local_luaState = 0;
            local_resultStr = 0;
            local_status = 0;
            isSuccess = checkQuickRecoveryResult(); // FUN_008bf4d0
            if (isSuccess == 0) {
                pString = "$dv_quickrecovery_fail";
            } else {
                pString = "$dv_quickrecovery_success";
            }
        }
        else {
            if (eventType != this->eventId4) { // +0x1c8
                if (eventType == this->eventId5) { // +0x1d8
                    handleEvent5(); // FUN_008c3f70
                    return;
                }
                if (eventType != kEventExitToMenu) { // DAT_0112fe38
                    return;
                }
                handleExitToMenu(); // FUN_008c55b0
                return;
            }
            local_luaState = 0;
            local_resultStr = 0;
            local_status = 0;
            isSuccess = checkUnionHelpResult(); // FUN_008bf570
            if (isSuccess == 0) {
                pString = "$dv_unionhelp_fail";
            } else {
                pString = "$dv_unionhelp_success";
            }
        }
        callLuaFunction(luaState, &local_luaState, pString); // FUN_006038f0
        char* resultStr = (char*)local_luaState;
        if (local_luaState == 0) {
            resultStr = (char*)gEmptyString; // DAT_0120546e
        }
        logMessage(resultStr); // FUN_00891290
        if (local_luaState != 0) {
            ((void (*)(char*))local_status)(resultStr); // call release? likely free
            return;
        }
    }
    return;
}