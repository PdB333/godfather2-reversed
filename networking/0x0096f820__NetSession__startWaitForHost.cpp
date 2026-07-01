// FUNC_NAME: NetSession::startWaitForHost

// Function at 0x0096f820: Creates a network session object in "waiting for host" state
// Uses global game manager pointer at 0x1223484 (gGameManager)
// Parameters: likely callback objects or session identifiers
void NetSession::startWaitForHost(int param1, int param2)
{
    int gameManager;
    int sessionObj;
    int *vtablePtr;
    int result;

    gameManager = gGameManager;  // DAT_01223484
    if ((gGameManager != 0) && (*(int *)(gGameManager + 0xc) != 0)) {
        sessionObj = allocateMemory(0xf0);  // FUN_009c8e50(0xf0) - allocate session object (240 bytes)
        if (sessionObj == 0) {
            sessionObj = 0;
        } else {
            sessionObj = constructSessionObject(0);  // FUN_00982280(0) - constructor call
        }
        setSessionState(2, 3);  // FUN_00981f10(2,3) - set initial state
        setStatusText("$mp_waiting_for_host");  // FUN_00981eb0 - store localized string key
        *(int *)(sessionObj + 0xc) = 0xc;     // +0x0C: state field
        *(int *)(sessionObj + 0x20) = 0xe8d242ca; // +0x20: some hash or identifier
        *(int *)(sessionObj + 0x14) = &LAB_0096f710; // +0x14: callback function pointer
        initializeSession();  // FUN_00982e10()
        addRefOrStore(param1);  // FUN_008b5c70(param1)
        addRefOrStore(param2);  // FUN_008b5c70(param2)
        vtablePtr = (int *)(**(code **)(**(int **)(*(int *)(gameManager + 0xc) + 8))());  // Get vtable from network manager singleton
        result = (**(code **)(*vtablePtr + 0xc))();  // Call virtual function at offset 0xc (e.g., getScheduler)
        attachResult(result);  // FUN_008b5c90(result) - attach the result to the session
        finalizeSetup();  // FUN_008b5d40()
    }
}