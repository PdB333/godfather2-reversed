// FUNC_NAME: OnlineLobbyManager::onJoinLobbyResult
void __thiscall OnlineLobbyManager::onJoinLobbyResult(int *thisPtr, int *joinResult)
{
    char isDonMode;
    int *allocState;
    int *lobbyStatePtr;
    char *nameSrc;
    size_t nameLen;
    int errorState;
    char *errorString;

    initializeLobbyManager(); // FUN_00982c90 - base init

    // Clear flags at offset +0x1bd (bit 19-16? mask 0xfff8ffff)
    thisPtr[0x1bd] = thisPtr[0x1bd] & 0xfff8ffff;

    if (joinResult == nullptr) {
        // Failure path: show error dialog and create error state
        (**(code **)(*thisPtr + 8))(); // virtual call: baseClass::onLeave?
        FUN_00983120(0, 0, 0); // reset state
        if (thisPtr[0x37] == 1) { // offset +0xDC (0x37*4) - flag: isHost?
            errorState = allocateMemory(0xf0); // FUN_009c8e50
            if (errorState == 0) {
                errorState = 0;
                errorString = "$mp_online_enter_donlobby_error";
            }
            else {
                errorState = getErrorStringHandle(0); // FUN_00982280
                errorString = "$mp_online_enter_donlobby_error";
            }
        }
        else {
            errorState = allocateMemory(0xf0);
            if (errorState == 0) {
                errorState = 0;
            }
            else {
                errorState = getErrorStringHandle(0);
            }
            errorString = "$mp_online_create_game_error";
        }
        showErrorDialog(errorString); // FUN_00981eb0
        // Set error state fields (offset +0x0C type, +0x14 callback)
        *(int*)(errorState + 0x0C) = 3;
        *(code**)(errorState + 0x14) = (code*)FUN_00982b30;
        showErrorUI(); // FUN_00982e10
        cleanupLobbyResources(); // FUN_0096a2f0
    }
    else {
        // Success path: extract lobby info from joinResult
        void *lobbyInfo = (void*)(**(code **)(*joinResult + 8))(); // get lobby info interface
        char *lobbyName = (char*)(**(code **)(*(int*)lobbyInfo + 4))(); // get lobby name string
        nameLen = 0x30;
        _strncpy((char*)(thisPtr + 0x91), lobbyName, nameLen); // copy to this->lobbyName at +0x244
        *(char*)((int)thisPtr + 0x273) = 0; // null-terminate (since copy 48 bytes, offset 0x273 is last byte)

        // Retrieve session IDs from joinResult virtual functions at offsets 0x74 and 0x70
        int sessionId = (**(code **)(*joinResult + 0x74))(); // get session ID
        int gameVariant = (**(code **)(*joinResult + 0x70))(); // get game variant
        thisPtr[0xAA] = sessionId;   // offset +0x2A8
        thisPtr[0xA9] = gameVariant; // offset +0x2A4

        *(char*)(thisPtr + 0x88) = 1; // offset +0x88 - set some flag (e.g., isLoading)
        *(char*)((int)thisPtr + 0x221) = 0; // offset +0x221 - clear isDonMode flag

        computeHash(thisPtr + 0x91); // FUN_004d3bc0 - hash lobby name

        // Check global lobby manager singleton (DAT_01223484)
        if ( (DAT_01223484 != 0) && (*(int*)(DAT_01223484 + 0x0C) != 0) ) {
            // Allocate and initialize lobby state object
            lobbyStatePtr = allocateMemory(0x60); // FUN_009c8e50
            if (lobbyStatePtr != 0) {
                lobbyStatePtr = initializeLobbyState(); // FUN_00962740
            }
            registerLobbyState(lobbyStatePtr); // FUN_00969880

            // Get singleton lobby manager
            int *lobbyMgr = getLobbyManager(); // FUN_0096aef0(0) - returns pointer
            *lobbyMgr = (int)lobbyStatePtr;

            // Check DonMode from joinResult's additional data (vtable offset 0x78)
            int *modeData = (int*)(**(code **)(*joinResult + 0x78))(); // get mode data
            isDonMode = (**(code **)(*modeData + 0x28))("DonMode", 0); // check if Don Mode
            if (isDonMode == '\0') {
                *(int*)(lobbyStatePtr + 0x14) = 3; // set state to non-Don mode
            }
            else {
                *(int*)(lobbyStatePtr + 0x14) = 1; // set state to Don mode
                *(char*)((int)thisPtr + 0x221) = 1; // set this->isDonMode flag at +0x221
            }

            pushGlobalState(&DAT_01130448, 0); // FUN_00402050
            pushHistory("PushHistory", 0, &DAT_00d8cdec, 0); // FUN_005a04a0 - history for back button
            startLobbyWaiting(); // FUN_00969720 - show waiting UI
            // Call method on a sub-object at offset +0x2EC (thisPtr[0xBB])
            (**(code **)(thisPtr[0xBB] + 0x94))(); // start lobby session in sub-manager
            initializeUIPart(thisPtr + 0x6A); // FUN_008a3be0 - set up lobby UI
        }

        // Final virtual call (base class routine)
        (**(code **)(*thisPtr + 8))();
        pushGlobalState(&DAT_01130448, 0); // again? maybe for safety

        // Stack cookie check (likely from Ghidra misinterpretation)
        if (iStack_10 != 0) {
            (*pcStack_4)(iStack_10);
            return;
        }
    }
    return;
}