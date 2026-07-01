//FUNC_NAME: Player::handleEvent
void __fastcall Player::handleEvent(int thisPtr) {
    bool bIsSpecial = false;
    int gameManager = getGameManager(); // FUN_00791300
    int flagsPtr = *(int *)(thisPtr + 0x10);
    if (flagsPtr != 0) {
        uint flagIndex1 = *(uint *)(flagsPtr + 0x5c);
        if (flagIndex1 != 0) {
            bIsSpecial = (*(uint *)(gameManager + 0x2188 + (flagIndex1 >> 5) * 4) & (1 << (flagIndex1 & 0x1f))) != 0;
        }
        uint flagIndex2 = *(uint *)(flagsPtr + 0x60);
        if ((flagIndex2 != 0) &&
            (bIsSpecial || ((*(uint *)(gameManager + 0x2188 + (flagIndex2 >> 5) * 4) & (1 << (flagIndex2 & 0x1f))) != 0))) {
            bIsSpecial = true;
        }
    }

    if (bIsSpecial) {
        playSpecialAnimation(*(int *)(thisPtr + 8)); // FUN_008c1350
        playSoundWithHash(*(int *)(thisPtr + 0xc), 0x6a194e56); // FUN_007e8ff0
        if (*(int *)(*(int *)(thisPtr + 0xc) + 0x54) != 0x637b907) goto LAB_008c888f;
        uint eventId = 0x39;
    } else {
        if ((((gameManager != 0) &&
              (int *manager = (int *)getManagerFromGlobal(DAT_01131018); // FUN_0043b870
               manager != 0)) &&
             (int vtableResult = (**(int (__thiscall **)(int))(*(int *)manager + 0x34))(manager); // virtual call
              vtableResult != 0)) &&
            ((*(int *)(vtableResult + 0xc) != 0 && (*(int *)(vtableResult + 0xc) != 0x48)))) {
            int adjustedPtr = (*(int *)(vtableResult + 0xc) == 0) ? 0 : (*(int *)(vtableResult + 0xc) - 0x48);
            int hashResult = lookupHash(adjustedPtr, 0x55859efa); // FUN_006b1c70
            if ((hashResult != 0) && (getSomeState() == 2)) { // FUN_00806440
                playAlternativeAnimation(*(int *)(thisPtr + 8)); // FUN_008bf3d0
                if (*(int *)(*(int *)(thisPtr + 0xc) + 0x54) != 0x637b907) goto LAB_008c888f;
                uint eventId = 0x38;
                goto LAB_008c8888;
            }
        }
        playDefaultAnimation(*(int *)(thisPtr + 8)); // FUN_008bf340
        if (*(int *)(*(int *)(thisPtr + 0xc) + 0x54) != 0x637b907) goto LAB_008c888f;
        uint eventId = 0x3a;
    }
LAB_008c8888:
    triggerEvent(eventId); // FUN_007e7df0

LAB_008c888f:
    if ((*(int *)(thisPtr + 8) != 0) && (gameManager = getGameManager(), gameManager != 0)) {
        sendTelemetry(0x53504750, (-(uint)bIsSpecial & 0x2f9) + 0x4d4d4853, gameManager); // FUN_009085c0
        char *namePtr;
        getStringFromHash(local_10, 1, &DAT_00d5db54, *(int *)(*(int *)(thisPtr + 8) + 0xc4)); // FUN_004d4a60
        namePtr = local_10[0];
        if (local_10[0] == 0) {
            namePtr = &DAT_0120546e;
        }
        sendTelemetryString(0x53504750, 0x4d4d4944, namePtr); // FUN_009085a0
        if (local_10[0] != 0) {
            (*local_4)(local_10[0]); // likely a destructor or free
        }
    }
    if (*(int *)(thisPtr + 0x10) == 0) {
        return;
    }
    cleanupSomething(); // FUN_008fe9c0
}