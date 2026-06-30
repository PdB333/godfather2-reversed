// FUNC_NAME: GameEngine::frameUpdate
void GameEngine::frameUpdate(bool bFirstCall) {
    // +0x04: list head pointer (int*)
    // +0x0c: list tail pointer (int*)
    // +0x14: current count? (int)
    // +0x1c: expected count? (int)
    // +0x2c: next node pointer
    // +0x40: some ID field in object

    int* pNode;
    uint originalResourceId;
    uint idx;
    uint var1;
    int iVar6;
    LARGE_INTEGER frameTime;

    originalResourceId = DAT_011f38f8;  // Global resource ID tracker?
    DAT_01163cf6 = false;               // Some pending flag

    uint resourceIdToFind = 0;
    if (bFirstCall) {
        resourceIdToFind = 0;
        // Scan array gResourceRegistry (DAT_01218e50, entry size 2 ints)
        // Looking for an entry where first field == 0
        do {
            if (gResourceRegistry[resourceIdToFind * 2] == 0) {
                if (resourceIdToFind < 0x14) {
                    // Clear bottom 2 bits of second field (lock flags?)
                    gResourceRegistry[resourceIdToFind * 2 + 1] &= 0xFFFFFFFC;
                }
                break;
            }
            resourceIdToFind++;
        } while (resourceIdToFind < 0x14);

        iVar6 = DAT_011f38fc;
        bool bWasIdle = (originalResourceId != 0) || (iVar6 != 0);
        DAT_011f38f8 = 0;
        DAT_011f38fc = 0;

        if (bWasIdle) {
            // Notify main engine singleton (vtable+0x94) of idle change
            (*(void(__thiscall*)(void*, int, int))(*DAT_01205750 + 0x94))(DAT_01205750, 1, 0);
        }
    }

    // Capture start of frame time
    QueryPerformanceCounter(&frameTime);
    gFrameStartLow = (int*)frameTime.LowPart;
    gFrameStartHigh = frameTime.HighPart;

    if (bFirstCall) {
        gDeltaTimeLow = 0;
        gDeltaTimeHigh = 0;
        DAT_01163cf5 = true; // First-frame flag

        if (gSkipUpdate == false) { // DAT_012054eb, some skip flag
            gObjectListDirty = false; // DAT_01194d00
            gPendingAddCount = 0; // DAT_01194a9c, maybe counter for pending adds

            // Iterate object list (starting from this+4, ending at this+0xc)
            iVar6 = *(int*)((char*)this + 4);
            if (iVar6 != *(int*)((char*)this + 0xc)) {
                do {
                    // Check if object's count doesn't match expected
                    if (*(int*)(iVar6 + 0x14) != *(int*)(iVar6 + 0x1c)) {
                        // Wait until object's ID matches its expected ID
                        do {
                            iVar6 = FUN_005246b0(); // Likely allocateObject/getObject
                        } while (*(int*)(iVar6 + 0x40) != *(int*)(iVar6 + 0x1c));
                    }
                    iVar6 = *(int*)(iVar6 + 0x2c);
                } while (iVar6 != *(int*)((char*)this + 0xc));

                if (gObjectListDirty) {
                    // Add object to render list
                    FUN_0042ed50(*(undefined4*)(DAT_012233a8 + 4), gObjectListDirty);
                }
            }
        }
    }

    // Main object update loop
    iVar6 = *(int*)((char*)this + 4);
    if (iVar6 != *(int*)((char*)this + 0xc)) {
        do {
            FUN_0051fc90(bFirstCall); // Update object (first pass)
            iVar6 = *(int*)(iVar6 + 0x2c);
        } while (iVar6 != *(int*)((char*)this + 0xc));
    }

    if (DAT_01163cf6) {
        FUN_0051ead0(); // Process deferred tasks
    }

    if (bFirstCall == false) {
        if ((gSkipUpdate == false) &&
            (iVar6 = *(int*)((char*)this + 4), iVar6 != *(int*)((char*)this + 0xc))) {
            do {
                FUN_0051fc40(); // Post-update objects (second pass)
                iVar6 = *(int*)(iVar6 + 0x2c);
            } while (iVar6 != *(int*)((char*)this + 0xc));
        }
        return;
    }

    // --- Resource management for first call ---
    idx = 0;
    do {
        // Find resource entry that matches originalResourceId
        if (gResourceRegistry[idx * 2] == originalResourceId) {
            if (idx < 0x14) {
                gResourceRegistry[idx * 2 + 1] &= 0xFFFFFFFC; // Clear lock bits
            }
            break;
        }
        idx++;
    } while (idx < 0x14);

    iVar6 = DAT_011f38fc;
    DAT_011f38fc = 0;

    if ((originalResourceId != DAT_011f38f8) || (DAT_011f38f8 = originalResourceId, iVar6 != 0)) {
        if (originalResourceId == 0) {
            DAT_011f38f8 = originalResourceId;
            // Notify idle
            (*(void(__thiscall*)(void*, int, int))(*DAT_01205750 + 0x94))(DAT_01205750, 1, 0);
        } else {
            // Retrieve resource description from gResourceTable (DAT_011a0f28, entry size 0x38)
            uint8_t* pResDesc;
            if (originalResourceId < 0x1000) {
                pResDesc = (uint8_t*)(&gResourceTable) + originalResourceId * 0x38;
            } else {
                pResDesc = nullptr;
            }

            uint parentId = *(uint*)(pResDesc + 0x1c);
            if (parentId != 0) {
                if (parentId < 0x1000) {
                    pResDesc = (uint8_t*)(&gResourceTable) + parentId * 0x38;
                } else {
                    pResDesc = nullptr;
                }
            }

            frameTime.LowPart = 0; // Reuse as handle
            if ((*(uint*)(pResDesc + 0xc) & 2) == 0) {
                DAT_011f38f8 = originalResourceId;
                if ((*(uint*)(pResDesc + 0xc) & 4) == 0) {
                    int* pCallback = *(int**)(pResDesc + 0x14);
                    if (pCallback == nullptr) {
                        pCallback = *(int**)(pResDesc + 0x18);
                        if (pCallback != nullptr) {
                            frameTime.LowPart = (DWORD)pCallback;
                            (*(void(__thiscall*)(int*))(*pCallback + 4))(pCallback);
                        }
                    } else {
                        (*(void(__thiscall*)(int*, int, LARGE_INTEGER*))(*pCallback + 0x48))(pCallback, 0, &frameTime);
                    }
                }
            } else {
                DAT_011f38f8 = originalResourceId;
                (*(void(__thiscall*)(int*, int, LARGE_INTEGER*))(*& unknown global, + 0x48))
                  (*(int**)(pResDesc + 0x14), gSomeGlobal, 0, &frameTime);
                // Note: DAT_00f158f0 used as second argument
            }

            // Notify main engine with resulting handle
            (*(void(__thiscall*)(void*, int, int))(*DAT_01205750 + 0x94))(DAT_01205750, 1, frameTime.LowPart);

            if ((int*)frameTime.LowPart != nullptr) {
                (*(void(__thiscall*)(int*))(*frameTime.LowPart + 8))((int*)frameTime.LowPart);
            }
        }
    }

    // --- End of frame: compute delta time ---
    QueryPerformanceCounter(&frameTime);
    if ((gFrameStartHigh <= (uint)frameTime.HighPart) &&
        ((gFrameStartHigh < (uint)frameTime.HighPart || (gFrameStartLow < frameTime.LowPart)))) {
        gDeltaTimeLow = frameTime.LowPart - (int)gFrameStartLow;
        gDeltaTimeHigh = (frameTime.HighPart - gFrameStartHigh) - (uint)(frameTime.LowPart < gFrameStartLow);
    } else {
        // Handle overflow/wrap (frameStart > current)
        gDeltaTimeLow = ~((int)gFrameStartLow - frameTime.LowPart) + 1;
        gDeltaTimeHigh = ~((gFrameStartHigh - frameTime.HighPart) - (uint)(gFrameStartLow < frameTime.LowPart)) +
                         (uint)(0xfffffffe < (uint)~((int)gFrameStartLow - frameTime.LowPart));
    }
}