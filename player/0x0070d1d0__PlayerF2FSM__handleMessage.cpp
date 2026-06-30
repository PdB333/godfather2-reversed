// FUNC_NAME: PlayerF2FSM::handleMessage
void __thiscall PlayerF2FSM::handleMessage(uint thisPtr, void* message) {
    int *msgIdPtr;
    char cVar2;
    byte bVar3;
    int iVar4;
    undefined4 local_18;
    undefined1 *local_14;
    undefined1 local_10;
    undefined1 local_c[12];

    // Call base handler
    FUN_007097d0(message);

    iVar4 = *(int*)message;
    if (iVar4 == eMsgEnter) {
        // Enter message
        FUN_0070b7b0(); // onStateEnter?
        FUN_00440590(&eMsgEnter, -(uint)(thisPtr != 0x3c) & thisPtr, DAT_00d5eee4, 0, 4);
        goto LAB_0070d25d;
    }
    if (iVar4 != eMsgExit) {
        // Not enter, not exit
        if (iVar4 != *(int*)(thisPtr + 0x34c)) {
            // Message does not match current state ID, skip
            goto LAB_0070d25d;
        }
        if (*(char*)(thisPtr + 0x360) == '\0') {
            // State is not active
            FUN_0070c860(0);
            goto LAB_0070d25d;
        }
    } else {
        // Exit message
        cVar2 = FUN_00481620(); // isGamePaused?
        if (cVar2 != '\0') {
            FUN_0070ce60(0); // handle pause
        }
    }

LAB_0070d25d:
    iVar4 = *(int*)message;
    if ((iVar4 == eMsgUpdate) || (iVar4 == eMsgUpdateSecondary)) {
        cVar2 = FUN_0070c650(); // some condition check
        int* pDynamicBuffer = (int*)(thisPtr + 0x338);
        iVar4 = *pDynamicBuffer;
        if (cVar2 == '\0') {
            // Condition false
            if ((((iVar4 != 0) && (iVar4 != 0x48)) &&
                (bVar3 = (byte)*(undefined2*)(thisPtr + 0x362), (bVar3 >> 3 & 1) == 0)) &&
               ((*(int*)message != eMsgUpdate || ((bVar3 >> 5 & 1) == 0)))) {
                if (*pDynamicBuffer == 0) {
                    iVar4 = 0;
                } else {
                    iVar4 = *pDynamicBuffer + -0x48;
                }
                FUN_00402050(iVar4 + 0x1d8, 0); // memset or reset
                if (*pDynamicBuffer == 0) {
                    iVar4 = 0;
                } else {
                    iVar4 = *pDynamicBuffer + -0x48;
                }
                FUN_004088c0(iVar4 + 0x3c); // destructor?
                if (*pDynamicBuffer != 0) {
                    FUN_004daf90(pDynamicBuffer); // operator delete
                    *pDynamicBuffer = 0;
                }
                FUN_004088c0(thisPtr);
            }
        } else if (((iVar4 != 0) && (iVar4 != 0x48)) &&
                   ((*(int*)message != eMsgUpdate || ((*(byte*)(thisPtr + 0x362) >> 5 & 1) == 0)))) {
            // Condition true
            if ((*(byte*)(thisPtr + 0x362) >> 3 & 1) == 0) {
                FUN_0045ca00(thisPtr - 0x3c); // some operation on base object
                if (*pDynamicBuffer == 0) {
                    iVar4 = 0;
                } else {
                    iVar4 = *pDynamicBuffer + -0x48;
                }
                local_18 = *(undefined4*)(iVar4 + 0x1d0);
                local_14 = local_c;
                local_10 = 0;
                FUN_00408a00(&local_18, 0);
                FUN_0045cac0();
            }
            if (*pDynamicBuffer == 0) {
                iVar4 = 0;
            } else {
                iVar4 = *pDynamicBuffer + -0x48;
            }
            FUN_004088c0(iVar4 + 0x3c);
            if (*pDynamicBuffer != 0) {
                FUN_004daf90(pDynamicBuffer);
                *pDynamicBuffer = 0;
                return;
            }
        }
    } else if ((iVar4 == eMsgSpecial) && (cVar2 = FUN_0043c6c0(thisPtr - 0x3c, 9), cVar2 != '\0')) {
        // Special message handling
        FUN_004088c0(thisPtr);
        return;
    }
    return;
}