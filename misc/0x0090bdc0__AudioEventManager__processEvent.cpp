// FUNC_NAME: AudioEventManager::processEvent
void __fastcall AudioEventManager::processEvent(AudioEventManager* this)
{
    char someFlag;
    int currentGlobalState;
    int additionalData;
    int eventId;
    int eventHash;
    int resolvedValue;
    undefined4 uVar5;
    undefined1* eventString;
    int iVar7;
    int tempLocal;
    undefined4 local_14;
    undefined1* local_10;
    undefined4 local_c;
    undefined4 local_8;
    code* local_4;

    // Get global audio manager or context
    int audioCtx = getAudioManager();
    if (audioCtx == 0) {
        return;
    }

    currentGlobalState = getCurrentAudioState();  // FUN_007e0710
    additionalData = getSomeOtherState();         // FUN_0079d7c0

    eventId = 0;
    resolvedValue = 0;
    local_14 = 0;

    // Check if current global state is a specific event ID (0x1000 or 0x40000000)
    if ((currentGlobalState == 0x1000 || currentGlobalState == 0x40000000) &&
        (additionalData == 0 ||
         (someFlag = checkSomeCondition(), someFlag == '\0' ||
          (getSomeData(audioCtx, additionalData, &local_14, &resolvedValue), eventId = resolvedValue, resolvedValue == 0)))) {
        currentGlobalState = setAudioState(0x1000);
    }

    // Check if the event is the same as previous and flags allow skipping
    if ((currentGlobalState == *(int*)(this + 0x1c)) && ((*(uint*)(this + 0x10) >> 1 & 1) == 0) &&
        ((additionalData == *(int*)(this + 0x20) || (currentGlobalState != 0x1000)))) {
        goto updateStoredData;   // LAB_0090c3c3
    }

    // Clear bit 1 of flags
    *(uint*)(this + 0x10) = *(uint*)(this + 0x10) & 0xfffffffd;

    local_10 = (undefined1*)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code*)0x0;

    uVar5 = getEventNameById(currentGlobalState);  // FUN_007e04a0

    // Large switch on event ID (currentGlobalState)
    if (0x8000 < currentGlobalState) {
        if (currentGlobalState < 0x400001) {
            if (currentGlobalState == 0x400000) {
                if (*(int*)(DAT_011299bc + 0x1c) != 0) goto skipAndCheckHash;  // switchD_0090c0e5_caseD_c
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0xCAEAAAB3;   // -0x3512554d
            }
            else if (currentGlobalState < 0x80001) {
                if (currentGlobalState == 0x80000) {
                    uVar5 = formatString(uVar5);
                    debugOutput(uVar5);
                    someFlag = isSomeModeActive();
                    eventHash = (someFlag != '\0' ? 0x76ca305b : 0) + 0x11b13058;
                }
                else if (currentGlobalState == 0x10000) {
                    uVar5 = formatString(uVar5);
                    debugOutput(uVar5);
                    eventHash = 0x2e715d56;
                }
                else {
                    if (currentGlobalState == 0x20000) {
                        int musicManager = getMusicManager();   // FUN_007e0da0
                        if (musicManager != 0) {
                            uVar5 = formatString(uVar5);
                            debugOutput(uVar5);
                            eventHash = *(int*)(musicManager + 0x1b0);
                        }
                        goto skipAndCheckHash;
                    }
                    if (currentGlobalState != 0x40000) goto defaultCase;
                    uVar5 = formatString(uVar5);
                    debugOutput(uVar5);
                    eventHash = 0x667e11bc;
                }
            }
            else if (currentGlobalState == 0x100000) {
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0x55d642ff;
            }
            else {
                if (currentGlobalState != 0x200000) goto defaultCase;
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0xE7C97CE1;   // -0x1836831f
            }
        }
        else if (currentGlobalState < 0x4000001) {
            if (currentGlobalState == 0x4000000) {
                iVar7 = getAudioFocus();   // FUN_007e0ca0
                if ((iVar7 == 0) || (someFlag = checkSceneActivation(audioCtx, 1), someFlag == '\0'))
                    goto skipAndCheckHash;
                eventHash = 0xDDFC02A0;   // -0x2213fd60
            }
            else {
                if (currentGlobalState == 0x800000) goto case_0x10;  // switchD_0090bed4_caseD_10
                if (currentGlobalState == 0x1000000) {
                    uVar5 = formatString(uVar5);
                    debugOutput(uVar5);
                    eventHash = 0x2074337f;
                }
                else {
                    if (currentGlobalState != 0x2000000) goto defaultCase;
                    uVar5 = formatString(uVar5);
                    debugOutput(uVar5);
                    eventHash = 0xA4E5E422;   // -0x5b1a1bde
                }
            }
        }
        else if (currentGlobalState == 0x10000000) {
            uVar5 = formatString(uVar5);
            debugOutput(uVar5);
            eventHash = 0xDF7845D7;   // -0x2087ba29
        }
        else {
            if (currentGlobalState != 0x20000000) goto defaultCase;
            uVar5 = formatString(uVar5);
            debugOutput(uVar5);
            eventHash = 0x4e132258;
        }
        goto afterSwitch;  // LAB_0090c067
    }

    // Handle event IDs <= 0x8000
    if (currentGlobalState == 0x8000) {
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0xA0680822;   // -0x5f97f7de
        goto afterSwitch;
    }

    if (0x100 < currentGlobalState) {
        if (currentGlobalState < 0x1001) {
            if (currentGlobalState == 0x1000) {
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                // fall through to skipAndCheckHash
skipAndCheckHash:
                if (eventHash == 0) goto handleDefault;  // LAB_0090c3a4
            }
            else if (currentGlobalState == 0x200) {
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0xE0487B0B;   // -0x1fb784f5
            }
            else if (currentGlobalState == 0x400) {
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0xFEF8D1B8;   // -0x1072e48
            }
            else {
                if (currentGlobalState != 0x800) goto defaultCase;
                uVar5 = formatString(uVar5);
                debugOutput(uVar5);
                eventHash = 0xD1FD8915;   // -0x2e0276eb
            }
        }
        else if (currentGlobalState == 0x2000) {
            // Set bit 1 of flags
            *(uint*)(this + 0x10) = *(uint*)(this + 0x10) | 2;
            // Switch on a field at offset 0x1ec4 in the audio context
            switch (*(undefined1*)(audioCtx + 0x1ec4)) {
            case 8:
            case 9:
                eventHash = 0xC0FD7E3E;   // -0x3f0281c2
                break;
            case 10:
            case 0xb:
                eventHash = 0xC0FD7E40;   // -0x3f0281c0
                break;
            default:
                goto skipAndCheckHash;
            case 0x10:
            case 0x11:
                eventHash = 0x809FCE4B;   // -0x7f6031b5
                break;
            case 0x1a:
            case 0x1b:
                eventHash = 0xC0FD7E3F;   // -0x3f0281c1
                break;
            case 0x1c:
            case 0x1d:
                eventHash = 0xC0FD7E41;   // -0x3f0281bf
                break;
            case 0x22:
            case 0x23:
                eventHash = 0x809FCE4A;   // -0x7f6031b6
            }
        }
        else {
            if (currentGlobalState != 0x4000) goto defaultCase;
            uVar5 = formatString(uVar5);
            debugOutput(uVar5);
            eventHash = 0xA7AABF7F;   // -0x58554081
        }
        goto afterSwitch;
    }

    // Handle event IDs <= 0x100
    if (currentGlobalState == 0x100) {
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x5f67d541;
        goto afterSwitch;
    }

    switch (currentGlobalState) {
    case 1:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x253764d8;
        break;
    case 2:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x2ed0f76b;
        break;
    default:
defaultCase:
        if ((*(byte*)(this + 0x10) & 1) != 0) {
            debugOutput("[b=RDUp]");   // Debug flag
            eventHash = 0xD5AFFAA9;   // -0x2a520557
            currentGlobalState = 0x8000000;
            break;
        }
handleDefault:
        handleDefaultEvent();   // FUN_00939e80
        goto endFunction;       // LAB_0090c3af

    case 8:
        iVar7 = getAudioFocus();
        if (iVar7 == 0) goto skipAndCheckHash;
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x18244c20;
        break;
    case 0x10:
case_0x10:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x467e2e8c;
        break;
    case 0x20:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x401f4b22;
        break;
    case 0x40:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0x6bf7e2df;
        break;
    case 0x80:
        uVar5 = formatString(uVar5);
        debugOutput(uVar5);
        eventHash = 0xc9223c3;
    }

afterSwitch:
    // Resolve event path string
    resolveEventPath(currentGlobalState, &local_10);
    eventString = local_10;
    if (local_10 == (undefined1*)0x0) {
        eventString = &DAT_0120546e;  // Some default string
    }

    // Trigger audio event with hash and additional data
    playAudioEvent(eventString, eventHash, local_14);

endFunction:
    // Free allocated string if any
    if (local_10 != (undefined1*)0x0) {
        local_4(local_10);   // Probably a deallocation function via function pointer
    }

updateStoredData:   // LAB_0090c3c3
    *(int*)(this + 0x1c) = currentGlobalState;
    *(int*)(this + 0x20) = additionalData;
    return;
}