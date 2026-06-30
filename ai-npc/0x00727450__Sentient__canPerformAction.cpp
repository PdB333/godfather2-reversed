// FUNC_NAME: Sentient::canPerformAction
bool __thiscall Sentient::canPerformAction(int thisPtr, int targetPtr) {
    byte localResult = 0; // local_1
    byte tempLocal = 0;   // uVar2
    int playerIndex = getActivePlayerIndex(); // FUN_0077dd80
    // Check if this->playerSlotsMask (offset 0x115) allows this player
    if ((*(byte *)(thisPtr + 0x115) & (1 << (playerIndex & 0x1f))) != 0) {
        // Check if this->state (offset 0xbc) is 0 or 0x48, or target is alive
        if (*(int *)(thisPtr + 0xbc) == 0 || *(int *)(thisPtr + 0xbc) == 0x48 ||
            isEntityAlive(targetPtr)) { // FUN_0078f170
            bool allowed = true; // cVar4
            // Evaluate the first big condition block
            bool condition1 = ( ( (*(uint *)(thisPtr + 0x110) >> 0x19) & 1) == 0 ) ||
                              (*(int *)(targetPtr + 0x24c4) == 0) ||
                              (*(int *)(targetPtr + 0x24c4) == 0x48);
            bool condition2 = ( (*(uint *)(thisPtr + 0x110) & 0x900) == 0 );
            if (!condition2) {
                // Check input manager conditions
                if (targetPtr != 0) {
                    int* inputMgr = (int*)getSingleton(DAT_01131040); // FUN_0043b870
                    if (inputMgr != 0) {
                        if (isControllerConnected()) { // FUN_006eb940
                            allowed = true; // reset
                            if ((*(uint *)(thisPtr + 0x110) & 0x100) != 0) {
                                // Call method at +0x1c of inputMgr with param 0x100
                                int (*func)(int) = (int (*)(int))(*inputMgr + 0x1c);
                                allowed = func(0x100) != 0;
                            }
                        } else {
                            allowed = false; // implied? Actually the structure: only if isControllerConnected returns non-zero does it allow; else allowed may stay 0 from initial? But allowed was set to 1 at start. Actually the decompiled sets cVar4=1 initially, then in the if block it sets cVar4=1 again conditionally. We need to follow the logic exactly.
                        }
                    } else {
                        allowed = false;
                    }
                } else {
                    allowed = false;
                }
            }
            if (condition1 && condition2) {
                // This block corresponds to the inner if where condition1 and condition2 are both true
                allowed = true; // start of block
                // Check bit 0xC (offset 0x110 >> 0xC)
                if ((*(uint *)(thisPtr + 0x110) >> 0xC) & 1) {
                    if (targetPtr != 0) {
                        int* inputMgr = (int*)getSingleton(DAT_01131040);
                        if (inputMgr != 0 && isControllerConnected()) {
                            int (*func)(int) = (int (*)(int))(*inputMgr + 0x1c);
                            if (func(0x100) != 0) {
                                return false;
                            }
                        }
                    }
                    allowed = true; // continues
                }
                // Check bit 0x9
                if ((*(uint *)(thisPtr + 0x110) >> 9) & 1) {
                    if (targetPtr != 0) {
                        int* someMgr = (int*)getSingleton(DAT_01131070);
                        if (someMgr != 0 && *(int *)(someMgr + 0x14) != 0 &&
                            (*(byte *)(*(int *)(someMgr + 0x14) + 0x4e) & 2) != 0) {
                            allowed = true;
                        }
                    }
                }
                // Check bit 0xA
                if ((*(uint *)(thisPtr + 0x110) >> 10) & 1) {
                    int* gameMgr;
                    if (targetPtr == 0) {
                        gameMgr = 0;
                    } else {
                        gameMgr = (int*)getSingleton(DAT_01131018);
                    }
                    if (gameMgr != 0) {
                        (*(void (*)())(*gameMgr + 0x30))(); // call method +0x30
                        if (*(float *)DAT_00d5ef88 <= some_float_result) {
                            return false;
                        }
                    }
                    allowed = true;
                }
                // Check bit 0xD
                if ((*(uint *)(thisPtr + 0x110) >> 0xD) & 1) {
                    allowed = !someCheck(); // FUN_007273f0
                }
            }
            // After the inner block, check bit 0xE
            if (allowed) {
                if ((*(uint *)(thisPtr + 0x110) >> 0xE) & 1) {
                    allowed = someCheck(); // FUN_007273f0
                }
                if (allowed) {
                    localResult = 1;
                }
            }
        }
    }
    return localResult;
}