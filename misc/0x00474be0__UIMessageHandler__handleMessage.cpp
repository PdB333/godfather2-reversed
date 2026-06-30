// FUNC_NAME: UIMessageHandler::handleMessage
void __thiscall UIMessageHandler::handleMessage(int thisPtr, int* message)
{
    uint* puVar1;
    uint uParam;
    int iHash;

    int msgId = *message;
    if (msgId == DAT_0120e93c) {
        if ((*(uint*)(thisPtr + 0xa8) >> 0x1a & 1) != 0) {
            playSound(0);
            setActiveFlag(&DAT_0120e93c);
            *(uint*)(thisPtr + 0xa8) &= 0xfbffffff;
            return;
        }
    }
    else if (msgId == *(int*)(thisPtr + 0x14)) {
        if (((*(uint*)(thisPtr + 0xa8) >> 5 & 1) == 0) || (*(int*)(thisPtr + 0x94) == 0)) {
            uParam = 0;
            int* pData = message[1];
            if (pData != nullptr) {
                int* pInner = *(int**)(pData + 4);
                if (pInner != nullptr) {
                    int innerOffset = (int)(pInner - 72); // -0x48
                    if (innerOffset != 0) {
                        uParam = lookupHash(innerOffset, 0x38523fc3);
                    }
                }
            }
            playSound(uParam);
            if ((*(uint*)(thisPtr + 0xa8) & 0x2000000) != 0) {
                if (*(int*)(thisPtr + 0x94) != 0) {
                    sendMessage(*(int*)(thisPtr + 0x94), 0x79c328b9, message[1]);
                }
                if (*(int*)(thisPtr + 0x94) != 0) {
                    puVar1 = (uint*)(*(int*)(thisPtr + 0x94) + 0xc);
                    *puVar1 |= 0x20000000;
                    return;
                }
            }
        }
    }
    else {
        if (msgId == *(int*)(thisPtr + 0x1c)) {
            if ((*(uint*)(thisPtr + 0xa8) >> 4 & 1) != 0) {
                toggleFeatureA();
                return;
            }
            toggleFeatureB();
            return;
        }
        if (msgId == *(int*)(thisPtr + 0x24)) {
            goto clearFlagsAndReturn;
        }
        if (msgId == *(int*)(thisPtr + 0x2c)) {
            iHash = message[1];
        }
        else {
            if (msgId == *(int*)(thisPtr + 0x34)) {
                executeCommand(0x26ba025e, message[1]);
                return;
            }
            if (msgId == *(int*)(thisPtr + 0x3c)) {
                executeCommand(0x8a1c9390, message[1]);
                return;
            }
            if (msgId == DAT_0120e944) {
                if (message[1] != *(int*)(thisPtr - 0x20)) {
                    return;
                }
                goto clearFlagsAndReturn;
            }
            if (msgId != DAT_0120e94c) {
                return;
            }
            iHash = message[1];
            if (iHash != *(int*)(thisPtr - 0x20)) {
                return;
            }
        }
        executeCommand(0x79c328b9, iHash);
        if (*(int*)(thisPtr + 0x94) != 0) {
            uint* pTargetFlags = (uint*)(*(int*)(thisPtr + 0x94) + 0xc);
            *pTargetFlags |= 0x20000000;
        }
        *(uint*)(thisPtr + 0xa8) |= 0x2000000;
    }
    return;

clearFlagsAndReturn:
    if (*(int*)(thisPtr + 0x94) != 0) {
        puVar1 = (uint*)(*(int*)(thisPtr + 0x94) + 0xc);
        *puVar1 &= 0xdfffffff; // clear bit 29
    }
    *(uint*)(thisPtr + 0xa8) &= 0xfdffffff; // clear bit 25
    return;
}