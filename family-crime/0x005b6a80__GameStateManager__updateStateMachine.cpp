// FUNC_NAME: GameStateManager::updateStateMachine
int GameStateManager::updateStateMachine(int arg, uint32_t* outParam2)
{
    // If outParam2 is not a special flag (1) and condition fails, return early
    if ((outParam2 != (uint32_t*)0x1) && (checkGameStateCondition(0) != '\0')) {
        return g_globalState; // DAT_0119cbbc
    }

    uint32_t* currentStateObj = (uint32_t*)getCurrentGameStateObject(); // FUN_0059c3b0
    resetStateTracker(0); // FUN_005a0d00

    outParam2 = 0;
    uint32_t localState = 0;
    char cond1 = checkGameStateCondition(0);
    if (cond1 == '\0') {
        char cond2 = isModeActive(); // FUN_005a3c40
        if (cond2 == '\0') {
            char cond3 = isTransitionPending(); // FUN_005a7d30
            if (cond3 == '\0')
                goto LAB_005b6c43;
            // Transition is pending
            uint32_t* outRef = &outParam2;
            uint32_t* localRef = &localState;
            uint32_t key = 0;
            uint32_t* transitionInfo = getTransitionInfo(0, localRef, outRef); // FUN_005a8fe0
            int playerObj = getPlayerObject(transitionInfo); // FUN_005a19c0
            setGameState(*(uint32_t*)(playerObj + 0x1c), transitionInfo, key, localRef, outRef); // FUN_005b1f80
            outParam2 = outParam2; // dummy
        }
        else {
            // No transition, maybe normal update
            uint8_t buffer[24]; // local_20, local_1c, local_14, local_c etc.
            uint32_t* bufPtr = (uint32_t*)&buffer[8]; // approximate
            buffer[0] = 0; // local_20
            buffer[4] = 0; // local_1c
            buffer[8] = 0; // local_14
            buffer[12] = 0; // local_c
            getSomeStringOrID(&buffer[0]); // FUN_005a92b0
            uint32_t* outRef = &outParam2;
            uint32_t* localRef = &localState;
            uint32_t key = 0;
            int playerObj = getPlayerObject(0, bufPtr, localRef, outRef); // FUN_005a19c0 with extra params
            setGameState(*(uint32_t*)(playerObj + 0x1c), key, bufPtr, localRef, outRef); // FUN_005b1f80
            outParam2 = outParam2;
            if ((bufPtr != &buffer[8]) && (bufPtr != (uint32_t*)0x0)) {
                g_free(bufPtr); // *DAT_0119caf4 likely a free function
                outParam2 = outParam2;
            }
        }
    }
    else {
        outParam2 = (uint32_t*)getCurrentGameStateObject(); // FUN_0059c3b0
    }

    // Check if outParam2 is valid and has a specific flag (0x8000)
    if ((outParam2 != (uint32_t*)0x0) && ((*outParam2 & 0x8000) != 0)) {
        int currentObj = getCurrentGameStateObject(); // FUN_0059c3b0
        uint32_t temp = *(uint32_t*)(currentObj + 0x30);
        int otherObj = getCurrentGameStateObject(); // maybe another? But same function
        *(uint32_t*)(otherObj + 0x30) = currentStateObj[0xc]; // currentStateObj pointer from earlier
        currentStateObj[0xc] = temp;
        getPlayerObject(); // FUN_005a19c0
        updateStateA(); // FUN_005b2380
        getPlayerObject();
        updateStateA();
        getPlayerObject();
        updateStateB(); // FUN_005b22e0
        getPlayerObject();
        updateStateB();
        // Call state-specific handlers via vtable
        (*(void (**)(uint32_t*))(&g_vtableTable + (*currentStateObj & 0x7fff) * 4))(currentStateObj);
        (*(void (**)(uint32_t*))(&g_vtableTable + (*outParam2 & 0x7fff) * 4))(outParam2);
        return g_globalState;
    }

LAB_005b6c43:
    char cond = isTransitionPending(); // FUN_005a7d30
    if (cond != '\0') {
        getPlayerObject(); // FUN_005a19c0
        updateStateA(); // FUN_005b2380
        getTransitionInfo(); // FUN_005a8fe0
        getPlayerObject(); // FUN_005a19c0
        updateStateB(); // FUN_005b22e0
        (*(void (**)(uint32_t*))(&g_vtableTable + (*currentStateObj & 0x7fff) * 4))(currentStateObj);
    }
    return g_globalState;
}