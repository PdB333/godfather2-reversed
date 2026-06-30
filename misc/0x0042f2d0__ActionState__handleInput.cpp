// FUNC_NAME: ActionState::handleInput
// Address: 0x0042f2d0
// This function is called with this in ESI, actionType in EAX (likely 2=press, 4=release), and four stack parameters.
// Parameters: param1 = InputDevice* device, param2 = int actionId, param3 = int controllerIndex, param4 = int extraData

int __thiscall ActionState::handleInput(void* this_esi, int actionType_eax, InputDevice* device, int actionId, int controllerIndex, int extraData)
{
    char bVar1;
    int iVar2;

    // Check device's time threshold; if not between global thresholds, ignore
    if ((g_floatThreshold2 != g_floatThreshold1) &&
        (device->timeSinceLastAction <= g_floatThreshold2 && g_floatThreshold2 != device->timeSinceLastAction)) {
        return 0;
    }

    // If device has debug/overlay flags, remap action type via global array
    if ((device->flags & 0x6000) != 0) {
        actionType_eax = g_actionTypeMap[actionType_eax];
    }

    // Check if controller or action type changed from cached state
    if ((controllerIndex != this->cachedControllerIndex) || (actionType_eax != this->cachedActionType)) {
        // Cancel previous ongoing action if any
        if (this->ongoingActionHandle != 0) {
            FUN_0049e4c0(this->ongoingActionHandle, this->cachedExtraData, extraData);
        }

        // Try to start new action
        iVar2 = FUN_0049e2f0(device->actionResourceId, actionType_eax, extraData);
        if (iVar2 == 0) { // Failure
            this->ongoingActionHandle = 0;
            this->cachedControllerIndex = 0;
            this->cachedActionType = -1;
            if ((actionType_eax != 2) && (actionType_eax != 4)) {
                return 0;
            }
            // Call failure callback (press/release specific)
            g_onActionFailedCallback();
            return 0;
        }
        if (iVar2 == 2) { // Interrupted or repeat
            this->actionInterruptedFlag = 0;
        }
        // Update cached state
        this->ongoingActionHandle = device->actionResourceId;
        this->cachedControllerIndex = controllerIndex;
        this->cachedActionType = actionType_eax;
    }

    // If actionId changed, update and possibly play feedback
    if (actionId != this->cachedActionId) {
        bVar1 = FUN_004166b0(); // Some has/haptic check
        if ((bVar1 != '\0') && ((g_globalFlags & 1) != 0)) {
            FUN_00614a50(); // Play haptic/sound feedback
        }
        this->cachedActionId = actionId;
    }

    // Call virtual update on device
    (*(code **)(*g_engineCore + 0x1c))(device);

    // If press (2) or release (4), perform additional feedback and callback
    if ((actionType_eax == 2) || (actionType_eax == 4)) {
        FUN_006123f0(); // Update UI/overlay
        (*(code *)g_onDeviceActionCallback)(device + 0xa0, device);
    }

    return 1;
}