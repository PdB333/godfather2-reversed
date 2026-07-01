// FUNC_NAME: GameEventManager::processEvent

void __thiscall GameEventManager::processEvent(void *this, uint param_2, void *param_3, int param_4)
{
    char *localStrPtr;
    int localFlag;
    void *localCallback;
    char *defaultStr = "(null)"; // &DAT_0120546e
    void *globalMgr;
    void *objFromParam3;

    // Begin event processing
    FUN_00604be0();

    // Initialize and log first message (code 0x66)
    if (*(int *)((int)this + 0xb0) == 0) {
        FUN_00603330(*(void **)((int)this + 0x80), (int)this + 0xac);
    }
    localStrPtr = *(char **)((int)this + 0xac);
    if (localStrPtr == 0) {
        localStrPtr = defaultStr;
    }
    FUN_00604c10(0x66, localStrPtr);

    // Initialize and log second message (code 0x46)
    if (*(int *)((int)this + 0xa0) == 0) {
        FUN_00603330(*(void **)((int)this + 0x7c), (int)this + 0x9c);
    }
    localStrPtr = *(char **)((int)this + 0x9c);
    if (localStrPtr == 0) {
        localStrPtr = defaultStr;
    }
    FUN_00604c10(0x46, localStrPtr);

    // Initialize and log third message (code 0x61) – repeats first initialization? Or different?
    if (*(int *)((int)this + 0xb0) == 0) {
        FUN_00603330(*(void **)((int)this + 0x80), (int)this + 0xac);
    }
    localStrPtr = *(char **)((int)this + 0xac);
    if (localStrPtr == 0) {
        localStrPtr = defaultStr;
    }
    FUN_00604c10(0x61, localStrPtr);

    // If param_3 is provided, process additional object
    if (param_3 != 0) {
        globalMgr = FUN_006b2160(); // get global manager singleton
        localStrPtr = *(char **)(globalMgr); // dereference for a string
        if (localStrPtr == 0) {
            localStrPtr = defaultStr;
        }
        FUN_00604c10(0x76, localStrPtr);

        objFromParam3 = FUN_008c74d0(*(int *)((int)param_3 + 0x40)); // get object by ID
        if (*(int *)((int)objFromParam3 + 0xb0) == 0) {
            FUN_00603330(*(void **)((int)objFromParam3 + 0x80), (int)objFromParam3 + 0xac);
        }
        localStrPtr = *(char **)((int)objFromParam3 + 0xac);
        if (localStrPtr == 0) {
            localStrPtr = defaultStr;
        }
        FUN_00604c10(100, localStrPtr);
    }

    // If param_4 is nonzero, iterate over a message list
    if (param_4 != 0) {
        void *list = FUN_00604d20(100);
        FUN_004d3bc0(list); // sets localFlag and localStrPtr via callback
        if (localFlag != 0) {
            localStrPtr = (char *)&localStrVar; // ?? Actually the local used is local_1024, but he code sets puVar1 from local_1024, which is set by the loop
            // Re-express: the loop fills local_1024 (buffer) and local_1020 (flag)
            // For simplicity we assume the loop sets localFlag = local_1020 and localStrPtr = local_1024
            if (localStrPtr == 0) {
                localStrPtr = defaultStr;
            }
            FUN_00604c10(100, localStrPtr);
        }
        if (localStrPtr != 0) {
            localCallback(localStrPtr); // call function pointer
        }

        list = FUN_00604d20(0x76);
        FUN_004d3bc0(list);
        if (localFlag != 0) {
            localStrPtr = (char *)&localStrVar;
            if (localStrPtr == 0) {
                localStrPtr = defaultStr;
            }
            FUN_00604c10(0x76, localStrPtr);
        }
        if (localStrPtr != 0) {
            localCallback(localStrPtr);
        }
    }

    FUN_00604c00(); // end event processing
}