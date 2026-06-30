// FUNC_NAME: StreamManager::loadStream
undefined1 __thiscall StreamManager::loadStream(int thisPtr, int resourceId, uint flags, int callbackParam)
{
    int *pChannelIndex;
    int *pChannelState;
    int iVar3;
    char bSuccess;
    int iVar5;
    undefined1 bReturnVal;
    undefined1 local_85;
    undefined4 uStack_80;
    undefined1 *puStack_7c;
    undefined4 uStack_78;
    undefined4 uStack_74;
    code *pcStack_70;
    undefined1 *vtableArray [10];
    undefined1 uStack_43;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined1 auStack_20 [4];
    undefined1 auStack_1c [24];
    int iStack_4;
    
    bReturnVal = 0;
    local_85 = 0;
    if (*(int *)(thisPtr + 0x18) == 0 && resourceId != 0) {
        iVar5 = GetPackageData(resourceId, 0, 0);          // FUN_00455f50
        if (iVar5 != 0) {
            InitStreamSystem();                             // FUN_005e30c0
            bSuccess = GetStreamName(vtableArray, iVar5);   // FUN_004a84d0
            if (bSuccess != '\0') {
                *(uint *)(thisPtr + 0x2c) = flags;          // this->streamFlags = flags
                iVar3 = gChannelStatesBase;                 // DAT_0112a9f4
                vtableArray[0] = &STREAM_CREATOR_FUNC;      // LAB_006fdc30 (vtable entry)
                if ((flags & 0xc4) == 0) {
                    uStack_43 = 0;
                } else {
                    uStack_43 = 1;
                    if ((flags & 0x100) == 0) {
                        if ((flags & 0x10) == 0) {
                            uStack_3c = DEFAULT_VOLUME;     // _DAT_00d5780c
                            uStack_38 = DEFAULT_PITCH;      // DAT_00d5f53c
                        } else {
                            uStack_3c = ALTERNATE_VOLUME;   // DAT_00d5eee4
                            uStack_38 = ALTERNATE_PITCH;    // DAT_00d5efa4
                        }
                    }
                }
                iStack_4 = thisPtr;
                SetupStreamCallback(callbackParam, auStack_20, auStack_1c); // FUN_006fbe70
                if (((flags & 8) != 0) && (bSuccess = IsStreamSystemReady(), bSuccess != '\0')) { // FUN_006fd0a0
                    pChannelIndex = (int *)(thisPtr + 0x28); // this->pChannelIndex
                    bSuccess = IsChannelActive(pChannelIndex); // FUN_006fbef0
                    if ((bSuccess != '\0') &&
                       ((*pChannelIndex != -1 &&
                        (pChannelState = (int *)(*pChannelIndex * 0x58 + 0x78 + iVar3), pChannelState != (int *)0x0)))) {
                        if (*pChannelState == 6) {
                            StopChannel();                 // FUN_006fbd30
                        }
                        if (*pChannelState == 0) {
                            *pChannelState = 1;
                            pChannelState[1] = 0;
                        }
                        pChannelState[9] = callbackParam; // pChannelState->callback = callbackParam
                        StartChannel(*pChannelIndex);      // FUN_006fd660
                    }
                }
                *(undefined4 *)(thisPtr + 0x24) = STREAM_DEFAULT_DATA; // DAT_01205210
                *(undefined1 *)(thisPtr + 0x35) = 1;      // this->isPlaying = true
                puStack_7c = (undefined1 *)0x0;
                uStack_78 = 0;
                uStack_74 = 0;
                pcStack_70 = (code *)0x0;
                bSuccess = GetStreamPath(&puStack_7c, iVar5, 0); // FUN_004a8460
                bReturnVal = local_85;
                if (bSuccess != '\0') {
                    undefined1 *pPath = puStack_7c;
                    if (puStack_7c == (undefined1 *)0x0) {
                        pPath = &STREAM_DEFAULT_PATH;       // DAT_0120546e
                    }
                    bSuccess = CreateStreamInstance(&uStack_80, pPath, vtableArray); // FUN_005e2a50
                    if (bSuccess == '\0') {
                        HandleStreamError();                 // FUN_006fd030
                    } else {
                        *(undefined4 *)(thisPtr + 0x18) = uStack_80; // this->pStreamHandle = streamHandle
                        bReturnVal = 1;
                    }
                }
                if (puStack_7c != (undefined1 *)0x0) {
                    (*pcStack_70)(puStack_7c);               // free path string
                }
            }
        }
        return bReturnVal;
    }
    return 0;
}