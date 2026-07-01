// FUNC_NAME: OnlineServices::handleLoginState
void __thiscall OnlineServices::handleLoginState(int thisPtr, int loginResult)
{
    int *globalManager;
    undefined *puVar2;
    int tmpVar;
    undefined *puVar4;
    undefined *str1;
    int stateCheck;
    undefined *str2;
    code *callbackPtr;
    undefined *str2Copy;
    code *pcStack_4;

    globalManager = DAT_012234b8; // g_onlineServicesManager singleton
    // Check if state transition is to login pending (currentState - previousState == 1)
    if (*(int *)(thisPtr + 0x94) - *(int *)(thisPtr + 0x74) == 1) { // this->currentState, this->previousState
        // Call virtual method at vtable+0x2c (likely OnLoginPending or similar)
        (**(code **)(*(int *)thisPtr + 0x2c))();
        // Some initialization or network call
        FUN_00566a20(); // likely NetworkManager::initLogin()
        tmpVar = DAT_01129928; // g_networkState
        DAT_00e5672c = 0xc; // set login timeout? 
        *(int *)(tmpVar + 0x60) = 0; // clear some flag
        if ((DAT_01130590 & 1) == 0) { // first time
            FUN_005c0d50(tmpVar + 0x14, &LAB_00931e00, 0); // register callback
            DAT_01130590 = DAT_01130590 | 1; // mark flag
            return;
        }
    }
    else {
        // Cleanup previous objects
        FUN_004d3b50(*(int *)(thisPtr + 0x70) + 0x10); // free or release something
        FUN_004d3b50(*(int *)(thisPtr + 0x70) + 0x5c);
        if (stateCheck - 4 < 0xd) { // stateCheck is likely loginResult (0-16?)
            puVar4 = str1;
            if (str1 == (undefined *)0x0) {
                puVar4 = &DAT_0120546e; // empty string
            }
            puVar2 = str2;
            if (str2 == (undefined *)0x0) {
                puVar2 = &DAT_0120546e;
            }
            (**(code **)(*globalManager + 0x6c))(puVar2, puVar4); // set dialog text
            FUN_00983120("$fe_plasma_login_pending", 0, 0); // show pending message
        }
        else {
            tmpVar = FUN_009c8e50(0xf0); // allocate UI element
            if (tmpVar == 0) {
                tmpVar = 0;
            }
            else {
                tmpVar = FUN_00982280(0); // initialize UI manager
            }
            FUN_00981eb0("$mp_online_invalid_password"); // set error text
            *(int *)(tmpVar + 0xc) = 3; // error code
            *(code **)(tmpVar + 0x14) = FUN_00982b30; // callback on OK
            FUN_00982e10(); // show dialog
        }
        if (str1 != (undefined *)0x0) {
            (*callbackPtr)(str1); // release string?
        }
        if (str2 != (undefined *)0x0) {
            (*pcStack_4)(str2);
        }
    }
    return;
}