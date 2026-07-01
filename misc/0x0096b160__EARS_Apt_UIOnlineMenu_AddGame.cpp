// Xbox PDB: EARS_Apt_UIOnlineMenu_AddGame
// FUNC_NAME: DonControlManager::processFlowState
void __thiscall DonControlManager::processFlowState(DonFlowState* pFlowState, ContextInterface* pContext)
{
    if (pContext == nullptr) {
        return;
    }

    // Fetch two values from context (likely start and end times or something)
    int val2 = pContext->getValue2(); // vtable+0x10
    int val1 = pContext->getValue1(); // vtable+0x0c
    int currentTime = val2; // saved as uStack_1c

    // Convert to something - returns bool?
    bool bIsActive = ConvertValues(&val1, &currentTime); // FUN_00964230

    // Get the data manager from context
    DataManager* pDataMgr = pContext->getDataManager(); // vtable+0x50

    // Get "DonFlow" setting as a float (likely a timer or threshold)
    float donFlowValue = pDataMgr->getFloatSetting("DonFlow", 0); // vtable+0x30

    // Debug print something
    pContext->debugLog(pContext->getValue2()); // vtable+0x18 -> FUN_004d3bc0

    // Check current state of the flow state machine
    if (pFlowState->state == 1) {
        if (bIsActive) {
            pContext->resetFlow(); // FUN_00960030
            goto cleanup;
        }
        if (donFlowValue != 0.0f) {
            goto cleanup;
        }

        // Check if a specific string field is present (maybe a hash or tag)
        char buffer[12];
        bool hasTag = FUN_00411fd0(buffer, pFlowState->someString); // pFlowState+0x244
        if (hasTag) {
            goto cleanup;
        }

        // Get another time value
        int newTime = pContext->getValue2(); // vtable+0x10
        // Compare with donFlowValue (converted to int?)
        ConvertAndCompare(&donFlowValue, &newTime); // FUN_00968e40
        if (donFlowValue == 0.0f) {
            newTime = pContext->getValue2();
            int* pField = reinterpret_cast<int*>(FUN_0096ad10(&newTime));
            *pField = 0;
        }

        // Allocate a new object (size 0x108) and possibly initialize it
        int* pNewObj = static_cast<int*>(FUN_009c8e50(0x108));
        if (pNewObj == nullptr) {
            newTime = 0;
        } else {
            newTime = pContext->constructObject(pNewObj); // FUN_00962840
        }
    } else {
        // For states between 5 and 8 inclusive
        if ((uint)(pFlowState->state - 5) > 3) {
            goto cleanup;
        }

        if (bIsActive) {
            pContext->resetFlow();
            goto cleanup;
        }

        // Get "MapHash" and process it
        DataManager::MapHash mapHash = pDataMgr->getMapHash("MapHash", 0);
        FUN_0095c760(); // likely clears or initializes something
        MapHashIterator iter = FUN_00963f80(mapHash);
        if (iter != 0) {
            MapHashIterator end = *(MapHashIterator*)(iter + 8);
            MapHashIterator current = 0;
            while (current < end) {
                int* entry = *(int**)(iter + 4); // array of pointers
                if (entry != 0) {
                    uint element = entry[current];
                    if (element != 0) {
                        // Get some coordinates from the hash entry (positions)
                        Vector2 pos = FUN_0095c290(element + 0x17c, element + 0x180);
                        FUN_0095e000(&pos); // process position
                    }
                }
                current++;
            }
        }

        // Get mode-related settings
        int modeRequested = pDataMgr->getIntSetting("ModeRequested", 0);
        int currentMode = *(int*)(g_pSomeGlobal + 0x1b4); // DAT_01129930 + 0x1b4
        int matchTypeIndex = pDataMgr->getIntSetting("MatchTypeIndex", 0);
        uint combinedFlags = 0;
        int someValue = *(int*)(g_pSomeGlobal + 0x1a8); // actually uses unaff_EBX (global DonControlManager)
        if (modeRequested == currentMode || currentMode == 0 || *(int*)(g_pDonControlManager + 0xdc) == 8) {
            combinedFlags = combinedFlags & 0xFFFFFF00 | 1; // set bit 0
        }

        // Check "DonMode" setting
        bool bDonModeEnabled;
        if (*(char*)(g_pDonControlManager + 500) == 0) {
            bDonModeEnabled = true;
        } else {
            bool bDonModeSetting = pContext->getBoolSetting("DonMode", 0); // vtable+0x28
            if (bDonModeSetting && donFlowValue == 0.0f) {
                donFlowValue = *(float*)(g_pGameData + 0x14); // DAT_01129908 + 0x14
                int donWager = pDataMgr->getIntSetting("DonWager", 0);
                if (donWager <= (int)donFlowValue) {
                    bDonModeEnabled = true;
                } else {
                    bDonModeEnabled = false;
                }
            } else {
                bDonModeEnabled = false;
            }
        }

        // Check conditions for transitioning
        if ((combinedFlags & 0xFF) != 0 && matchTypeIndex == *(int*)(g_pDonControlManager + 0x1a8) && bDonModeEnabled) {
            int newTime = pContext->getValue2();
            int* pField = reinterpret_cast<int*>(FUN_0096ad10(&newTime));
            *pField = 0;

            int* pNewObj = static_cast<int*>(FUN_009c8e50(0x108));
            if (pNewObj == nullptr) {
                newTime = 0;
            } else {
                newTime = pContext->constructObject(pNewObj);
            }
        }
    }

    // Finalize the new object allocation
    FUN_0096ac70(&newTime);

cleanup:
    if (buffer[0] != 0) {
        // Call destructor via function pointer
        auto dtorFunc = reinterpret_cast<void (*)(void*)>(pcStack_c);
        dtorFunc(buffer);
    }
}