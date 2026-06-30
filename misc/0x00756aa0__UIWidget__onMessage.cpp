// FUNC_NAME: UIWidget::onMessage
uint8_t __thiscall UIWidget::onMessage(int* thisPtr, uint32_t arg1, uint32_t arg2, uint32_t arg3, int32_t messageId, uint32_t arg5) {
    uint8_t result;
    uint32_t tempUint;
    int32_t tempInt;
    uint32_t stack0[5];
    // local_30, local_2c, local_28, local_24, local_20, local_1c[5], local_8, local_4
    uint32_t local_30;
    void*** local_2c;
    uint8_t local_28;
    void** local_24;
    uint32_t local_20;
    int32_t local_1c[5];
    uint8_t local_8;
    uint32_t local_4;

    switch (messageId) {
    case 10: // eAccept
        playAcceptSound(0);
        return 1;
    case 11: // eDecline
        playDeclineSound();
        return 1;
    case 12: // eCancel
    {
        if ((*(byte *)(thisPtr + 0x1b) & 1) != 0) { // bit0: interaction enabled
            tempInt = getSomething(); // likely get current context
            doSomething(tempInt + 0x30, 0); // clear timer or state
            (**(code **)(*thisPtr + 0x2c))(0x46b13011, 1, 1, 0, 1.0f, 1.0f); // play confirm sound?
            playGlobalEffect(1, 0, gGlobalData_0xd5ef90);
            *(byte *)(thisPtr + 0x1b) |= 2; // mark as handled
            return 1;
        }
        break;
    }
    case 13: // eOption1
    {
        if ((*(byte *)(thisPtr + 0x1b) & 1) != 0) {
            tempInt = getSomething();
            doSomething(tempInt + 0x30, 0);
            (**(code **)(*thisPtr + 0x2c))(0xd755f672, 1, 1, 0, 1.0f, 1.0f);
            playGlobalEffect(1, 0, gGlobalData_0xd5ef90);
            *(byte *)(thisPtr + 0x1b) |= 2;
            return 1;
        }
        break;
    }
    case 15: // eSkip
        playSkipSound(0);
        return 1;
    case 16: // eCustomAction
    {
        // Build structure for dialog creation
        local_1c[4] = 0;
        local_1c[3] = 0;
        local_1c[2] = 0;
        local_24 = &gFunctionPtr_0xd5dbbc; // some callback table
        local_1c[0] = 0;
        local_1c[1] = 0;
        local_8 = 0;
        local_4 = gData_0x1205228;
        local_20 = 0x7c9a0ecd; // hash or ID
        resetTimer(thisPtr + 0x15);
        local_2c = &local_24;
        local_30 = gData_0x112ad8c;
        local_28 = 0;
        if (thisPtr[0x14] == 0) {
            tempInt = 0;
        } else {
            tempInt = thisPtr[0x14] + 0x3c; // +60 frames?
        }
        createUIElement(&local_30, tempInt, 0);
        if (local_1c[0] == 0) {
            return 1;
        }
        destroyUIElement(local_1c);
        return 1;
    }
    default:
        // Delegate to base class
        return baseClassHandler(arg1, arg2, arg3, messageId, arg5);
    }

    // Default fallback: play failure animation/sound and set flag
    doSomething(thisPtr + 0x18, 0); // clear another timer
    tempInt = *thisPtr;
    tempUint = triggerVFX(1, 1, 0, 1.0f, 1.0f);
    (**(code **)(tempInt + 0x2c))(tempUint);
    *(byte *)(thisPtr + 0x1b) |= 4; // mark as failed/invalid
    (**(code **)(*(int *)thisPtr[0x14] + 0x290))(0, 1); // call method on child object
    return 1;
}