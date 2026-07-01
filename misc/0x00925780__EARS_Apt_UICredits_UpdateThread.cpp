// Xbox PDB: EARS_Apt_UICredits_UpdateThread
// FUNC_NAME: CreditManager::updateCredits
int __fastcall CreditManager::updateCredits(int *thisPtr) {
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    int *node;
    int *prevNode;
    int iVar5;
    int iVar6;
    uint uVar7;
    uint uVar8;
    float fVar9;
    float fVar10;
    char buf[256];
    char *strPtr;
    int intVal;
    char charFlag;
    uint numIndex;

    // Check if credits are already finished and global state not in "3"
    if (((char)thisPtr[0x4e9] == '\0') && (*(int *)(DAT_01129814 + 0x10) != 3)) {
        // Time threshold, probably max duration for a credit
        float minRemaining = (float)thisPtr[0x1b];
        float deltaTime = (float)thisPtr[0x4e6] * DAT_01206800; // speed factor
        thisPtr[0x2c] = (int)((float)thisPtr[0x2c] + DAT_01206800); // advance game time

        // Process active list: update remaining time, move expired credits to free list
        node = (int *)thisPtr[0x4e1];
        prevNode = nullptr;
        while (node != nullptr) {
            node[5] = (int)((float)node[5] + deltaTime); // increase elapsed time
            thisPtr[0x1a] = node[0];  // current ID
            thisPtr[0x18] = node[5];  // current elapsed
            sendEvent("MoveCredit", 0, &DAT_00d87730, 0);

            // Remaining life = node[5] - node[9] (total - threshold)
            fVar1 = (float)node[5] - (float)node[9];
            if (fVar1 < minRemaining) {
                minRemaining = fVar1; // track the minimum remaining
            }
            if (fVar1 <= (float)thisPtr[0x1b] * _DAT_00d5c458) {
                // Expired: remove from active list
                node = (int *)node[10]; // next
                prevNode = node; // keep reference? Actually, we will move node, but prevNode becomes current for next iteration? Wait, this logic needs care.
                // In the original: piVar5 = piVar4[10]; piVar2 = piVar4;
            } else {
                // Not expired: move node to free list? Actually, above else block moves to free list.
                if (prevNode == nullptr) {
                    thisPtr[0x4e1] = node[10]; // head = next
                } else {
                    prevNode[10] = node[10];
                }
                node[10] = thisPtr[0x4e0]; // link to free list
                thisPtr[0x4e0] = (int)node; // free list head = this node

                thisPtr[0x1a] = node[0];
                sendEvent("RemoveCredit", 0, &DAT_00d87730, 0);

                // Clear node data
                node[7] = 0;
                node[6] = 0;
                node[5] = 0;
                node[4] = 0;
                node[8] = 0;
                node[9] = 0;

                if (prevNode == nullptr) break; // After moving first node, break? Original breaks after moving if prev == 0.
                node = (int *)prevNode[10];
            }
        }

        fVar2 = DAT_00e44718; // multiplier for credit generation threshold
        if (thisPtr[0x4e2] == 0) {
            minRemaining = (float)thisPtr[0x1b] * DAT_00e44718;
            thisPtr[0x4e2] = 1;
        }

        // Generate credits while minimum remaining is below threshold * max time
        while ((float)thisPtr[0x1b] * fVar2 <= minRemaining) {
            if ((uint)thisPtr[0x4e4] < (uint)thisPtr[0x4e2]) break;

            // Look up credit template name
            sprintf(buf, 0xff, "CREDITS_%d", thisPtr[0x4e2]);
            buf[255] = 0;
            int templateHandle = lookupString(buf);
            intVal = 0;
            charFlag = 0;
            getStringFromHandle(templateHandle, &intVal, &charFlag);
            iVar4 = intVal;
            if (intVal == 0) {
                thisPtr[0x4e3] = 0;
                goto nextCredit;
            } else {
                // Get the "Num" field
                sprintf(buf, 0xff, "%s_Num", iVar4);
                buf[255] = 0;
                templateHandle = lookupString(buf);
                strPtr = nullptr;
                getStringFromHandle(templateHandle, &strPtr, &charFlag);
                if ((strPtr == nullptr) || (numIndex = atol(strPtr), numIndex == 0)) {
                    // No number: generate one credit of type 1
                    int handle = lookupString(iVar4); // reuse template name
                    int val = getIntFromHandle(handle);
                    // Get a node from free list
                    node = (int *)thisPtr[0x4e0];
                    thisPtr[0x4e0] = node[10];
                    node[10] = thisPtr[0x4e1]; // add to front of active list
                    int duration = thisPtr[0x1d];
                    thisPtr[0x4e1] = (int)node;
                    node[0] = thisPtr[0x4e5]; // assign ID
                    thisPtr[0x4e5]++;
                    node[9] = duration;
                    node[8] = 1; // type 1
                    node[4] = 0;
                    node[6] = 0;
                    node[5] = (int)minRemaining; // set elapsed time
                    node[7] = _DAT_00d5780c; // some flag? maybe start time?
                    thisPtr[0x19] = 1;
                    thisPtr[0x1a] = node[0];
                    thisPtr[0x18] = node[5];
                    thisPtr[0x17] = node[4];
                    sendEvent("AddCredit", 0, &DAT_00d87730, 1, val);

                    minRemaining = (float)node[5] - (float)node[9];
                    goto nextCredit;
                }
                // Num field exists and non-zero
                if (thisPtr[0x4e3] == 0) {
                    // First in this sub-series: generate one credit of type 2
                    int handle = lookupString(); // empty string? original: FUN_004dafd0()
                    int val = getIntFromHandle(handle);
                    node = (int *)thisPtr[0x4e0];
                    thisPtr[0x4e0] = node[10];
                    node[10] = thisPtr[0x4e1];
                    int duration = thisPtr[0x1e];
                    thisPtr[0x4e1] = (int)node;
                    node[0] = thisPtr[0x4e5];
                    thisPtr[0x4e5]++;
                    node[9] = duration;
                    node[8] = 2; // type 2
                    node[4] = 0;
                    node[6] = 0;
                    node[5] = (int)minRemaining;
                    node[7] = _DAT_00d5780c;
                    thisPtr[0x19] = 2;
                    thisPtr[0x1a] = node[0];
                    thisPtr[0x18] = node[5];
                    thisPtr[0x17] = node[4];
                    sendEvent("AddCredit", 0, &DAT_00d87730, 1, val);

                    minRemaining = (float)node[5] - (float)node[9];
                    thisPtr[0x4e3]++;
                } else {
                    // Multiple columns: generate credits based on Cols/Num pattern
                    sprintf(buf, 0xff, "%s_Cols", iVar4);
                    buf[255] = 0;
                    templateHandle = lookupString(buf);
                    strPtr = getStringFromHandle(templateHandle);
                    if ((strPtr == nullptr) || (uVar7 = atol(strPtr), uVar7 == 0)) {
                        uVar7 = 1;
                    }
                    float curMin = minRemaining;
                    uVar8 = uVar7;
                    if (uVar7 == 0) {
                        minRemaining = curMin;
                    } else {
                        do {
                            sprintf(buf, 0xff, "%s_%d", iVar4, thisPtr[0x4e3]);
                            buf[255] = 0;
                            templateHandle = lookupString(buf);
                            strPtr = nullptr;
                            getStringFromHandle(templateHandle, &strPtr, &charFlag);
                            if (strPtr == nullptr) {
                                uVar8++;
                            } else {
                                // Compute credit amount using a formula
                                int remainingCol = uVar7 - uVar8 + 1;
                                float fracRem = (float)remainingCol;
                                if (remainingCol < 0) fracRem += DAT_00e44578;
                                float totalCols = (float)(int)uVar7;
                                if ((int)uVar7 < 0) totalCols += DAT_00e44578;
                                float twoCol = (float)(int)(uVar7 * 2);
                                if ((int)(uVar7 * 2) < 0) twoCol += DAT_00e44578;
                                float factor = (fracRem / totalCols - 1.0f / twoCol) - _DAT_00d5c458;
                                float creditAmount = computeCreditAmount((uVar7 > 1) + 3, strPtr, minRemaining, factor * (float)thisPtr[0x1c]);
                                curMin = creditAmount; // not sure if min or reset
                            }
                            thisPtr[0x4e3]++;
                            if ((uint)numIndex < (uint)thisPtr[0x4e3]) {
                                thisPtr[0x4e2]++;
                                thisPtr[0x4e3] = 0;
                                curMin = minRemaining; // ??
                            }
                            uVar8--;
                        } while (uVar8 != 0);
                        minRemaining = curMin;
                    }
                }
            }
nextCredit:
            thisPtr[0x4e2]++;
        }

        // After credit generation, check if all credits have been generated and active list empty
        if (((uint)thisPtr[0x4e4] < (uint)thisPtr[0x4e2]) && (thisPtr[0x4e1] == 0)) {
            // Check restart flag
            if (*(char *)((int)thisPtr + 0x13b2) != '\0') {
                thisPtr[0x4e9] = 1; // mark finished
                if (*(char *)((int)thisPtr + 0x13a5) != '\0') {
                    // Fire some event
                    int eventVar[3] = {DAT_0112ddd8, 0, 0};
                    someEventHandler(&eventVar, 0);
                }
                // Call virtual function at offset 0x2c (e.g., onFinish)
                (*(void (**)(void))(*thisPtr + 0x2c))();
                return 0;
            }
            // Show legal screen if not yet shown
            if ((char)thisPtr[0x4ec] == '\0') {
                thisPtr[0x4ea] = thisPtr[0x2c];
                sendEvent("ShowLegal", 0, &DAT_00d87730, 0);
                thisPtr[0x4ec] = 1;
                return 0;
            }
            // Hide legal after duration
            if ((*(char *)((int)thisPtr + 0x13b1) == '\0') &&
                ((float)thisPtr[0x4ea] + (float)thisPtr[0x4eb] < (float)thisPtr[0x2c])) {
                *(char *)((int)thisPtr + 0x13b1) = 1;
                sendEvent("HideLegal", 0, &DAT_00d87730, 0);
                if ((float)thisPtr[0x4eb] == DAT_00d5ccf8) {
                    *(char *)((int)thisPtr + 0x13b2) = 1; // trigger finish on next tick
                }
            }
        }
    }
    return 0;
}