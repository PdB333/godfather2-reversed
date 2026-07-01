// FUNC_NAME: WeaponWheelManager::handleInput
undefined4 __thiscall WeaponWheelManager::handleInput(int thisPtr, int actionId) {
    char cVar1;
    int currentMode;
    undefined4 result;

    result = 1; // Default: not handled
    currentMode = getCurrentMode(); // FUN_00466840
    if (actionId == currentMode) {
        // If same as current mode, handle special cancel
        if (((*(uint *)(thisPtr + 0x5c) >> 0xf & 1) != 0) && (*(int *)(thisPtr + 0xcc) < 1)) {
            FUN_00939ba0(0); // Possibly clear weapon wheel or exit
            return 1;
        }
    }
    else {
        switch(actionId) {
        case 0: // Activate weapon wheel?
            cVar1 = isWeaponWheelOpen(); // FUN_00911f40(0)
            if (cVar1 != '\0') {
                // If wheel is open and certain flags allow
                if ((((*(byte *)(thisPtr + 0x5c) & 1) != 0) && (*(int *)(thisPtr + 0xa0) != 0)) &&
                   (cVar1 = isWeaponWheelOpen(), cVar1 != '\0')) {
                    // Possibly close wheel or cancel
                    FUN_0093f300(thisPtr + 0x84);
                    return 0;
                }
                // Check if input should be ignored
                cVar1 = isInputAllowed(); // FUN_0093efe0
                if (cVar1 != '\0') {
                    result = 0;
                }
            }
            break;
        case 2: // Clear weapon wheel slots
            if (((*(uint *)(thisPtr + 0x5c) >> 3 & 1) == 0) &&
                (cVar1 = canClearWeaponWheel(), cVar1 == '\0')) { // FUN_0093a760
                debugPrint("ClearWeaponWheelSlots", 0, &DAT_00d8a64c, 0); // FUN_005a04a0
                clearWeaponWheel(); // FUN_0093a6c0
                *(undefined4 *)(thisPtr + 0xd0) = 0;
                registerCallback(thisPtr + 0x10, &LAB_0093d750, 1); // FUN_005c0260 -> schedule action
                return 0;
            }
            break;
        case 7:
        case 8:
        case 9: // Weapon slot selection?
            if ((*(uint *)(thisPtr + 0x5c) >> 3 & 1) != 0) {
                selectWeaponSlot(actionId); // FUN_0093c2a0
                return 0;
            }
        }
    }
    return result;
}