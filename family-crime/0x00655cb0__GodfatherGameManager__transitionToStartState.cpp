// FUNC_NAME: GodfatherGameManager::transitionToStartState
void GodfatherGameManager::transitionToStartState(GameContext* pContext)
{
    char isFlagSet;
    undefined4 in_EAX; // passed from caller, likely a pointer
    int* pGlobalManager;
    int allocResult;
    int* pSomePtr;
    uint flags[2];

    pGlobalManager = (int*)GetGlobalManager(); // FUN_00655130
    if ((pGlobalManager != (int*)0x0) && (pGlobalManager[0x6d] == 1)) { // state == 1 (likely INTRO/LOADING)
        ClearFlag(0x40, flags); // FUN_0064b9e0
        isFlagSet = IsSomeConditionTrue(); // FUN_006549b0
        if (isFlagSet == '\0') {
            ClearFlag(0x20, flags);
            pGlobalManager[0x53] = flags[0]; // store flag state
            ClearFlag(0x40, (int)pGlobalManager + 0x13b); // clear another flag at offset 0x13b
            ClearFlag(0x20, flags);
            pGlobalManager[0x51] = flags[0]; // store flag state

            if (flags[0] < 0x1b) { // check against some size/limit (27)
                isFlagSet = CheckSomeBoolean(); // FUN_0046d790
                if (isFlagSet != '\0') {
                    isFlagSet = CheckSomeBoolean(); // duplicated check
                    if (isFlagSet == '\0') {
                        // First branch: normal mission start
                        allocResult = AllocateObject(0x24); // FUN_009c8e50
                        if (allocResult != 0) {
                            InitializeMissionObject(in_EAX); // FUN_00654840
                        }
                        ExecuteMissionSetup(); // FUN_00657990

                        if (*(char*)(pGlobalManager[0x54] + 0x20) == '\0') { // pGlobalManager->currentPlayer + 0x20 (some flag)
                            return;
                        }
                        isFlagSet = (**(code**)(*pGlobalManager + 0x1c))(pGlobalManager[0x54], 1); // virtual call on pGlobalManager->vtable+0x1c
                        if (isFlagSet == '\0') {
                            return;
                        }
                    }
                    else {
                        // Second branch: special mission start (maybe tutorial)
                        allocResult = AllocateObject(0x2c); // FUN_009c8e50
                        if (allocResult != 0) {
                            InitializeSpecialObject(in_EAX); // FUN_00654ad0
                        }
                        ExecuteSpecialSetup(); // FUN_00657a10

                        int vehiclePtr = pGlobalManager[0x56]; // pGlobalManager->currentVehicle
                        if (*(char*)(vehiclePtr + 0x24) == '\0') {
                            return;
                        }
                        isFlagSet = (**(code**)(*pGlobalManager + 0x18))(vehiclePtr, 1); // virtual call pGlobalManager->vtable+0x18
                        if (isFlagSet == '\0') {
                            return;
                        }

                        flags[0] = *(uint*)(vehiclePtr + 0x18);
                        if (flags[0] != 0) {
                            *(int*)(flags[0] + 8) = *(int*)(flags[0] + 8) + 1; // ref count increment
                        }
                        ExecutePostSpecialSetup(); // FUN_00657960
                        ExecuteAnotherSetup(); // FUN_00652910
                    }

                    int* pCurrentPlayerPtr = pGlobalManager + 0x54; // pointer to offset 0x54 (currentPlayer ptr)
                    if ((*(int*)(pContext + 0x30) == 0) || 
                        (*(int*)(*(int*)(pContext + 0x30) + 0x10) != *(int*)(*pCurrentPlayerPtr + 0x10))) {
                        // Context mismatch: allocate new player object
                        allocResult = AllocateObject(0x24); // FUN_009c8e50
                        if (allocResult != 0) {
                            InitializePlayerFromData(*(undefined4*)(*pCurrentPlayerPtr + 0x10)); // FUN_0065e100
                        }
                        ExecutePlayerSetup(); // FUN_00657990
                    }
                    else {
                        ExecutePlayerReuse(); // FUN_00657960
                    }

                    // Final setup steps
                    SetupActiveMission(pGlobalManager[0x55], flags, *pCurrentPlayerPtr); // FUN_0065e570
                    FinalizeLoading(); // FUN_006544b0
                    ApplyPendingChanges(); // FUN_00652950
                    ClearBuffer((int)pGlobalManager + 0x162, 0x10); // FUN_0065bf00
                    *(undefined1*)((int)pGlobalManager + 0x131) = 1; // set flag at offset 0x131
                }

                // Transition to state 3 (PLAYING)
                pGlobalManager[0x6d] = 3;
                pGlobalManager[0x67] = 0; // reset some counter
                pGlobalManager[0x52] = 0; // reset another
                pGlobalManager[0x68] = *(int*)(pContext + 100); // store context field at offset 100
                ContinueStartProcess(pContext); // FUN_00655ef0
            }
        }
    }
    return;
}