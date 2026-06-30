// FUNC_NAME: Player::resetCurrentAction
void Player::resetCurrentAction(void)
{
    int savedActionId;
    int *vtablePtr;
    bool conditionCheck;
    int unaff_ESI; // this pointer

    // Check if there's an active action that hasn't been completed
    if ((*(int *)(unaff_ESI + 0x26c) != 0) &&
        (*(char *)(unaff_ESI + 0x281) != '\0') &&
        (*(char *)(unaff_ESI + 0x282) == '\0'))
    {
        // Trigger a sound/event through the audio manager
        AudioDataManager::playEvent(gAudioManager, *(int *)(unaff_ESI + 0x27c), 7);
    }

    // Reset movement/velocity related fields
    *(int *)(unaff_ESI + 0x1b4) = 0;
    *(int *)(unaff_ESI + 0x1b8) = 0;

    // Handle pending action pointer
    if (*(int *)(unaff_ESI + 0x484) != 0)
    {
        *(int *)(unaff_ESI + 0x484) = 0;
        conditionCheck = this->canReassignAction();
        if (conditionCheck != '\0')
        {
            // Copy the (now zero) pending pointer to current (effectively clearing it)
            *(int *)(unaff_ESI + 0x480) = *(int *)(unaff_ESI + 0x484);
        }
    }

    // Save current action ID and reset input bindings
    savedActionId = *(int *)(unaff_ESI + 0x1cc);
    *(int *)(unaff_ESI + 0x1cc) = -1;      // +0x1cc: lastActionId
    *(int *)(unaff_ESI + 0x1d0) = -1;      // +0x1d0: lastActionId2
    *(int *)(unaff_ESI + 0x1d8) = 0;       // +0x1d8: actionTimer
    *(int *)(unaff_ESI + 0x1dc) = 0;       // +0x1dc: actionTimer2

    vtablePtr = gInputManager; // global input/controller manager
    if (*(int *)(unaff_ESI + 0x1c8) >= 0)  // +0x1c8: activeInputSlot
    {
        *(int *)(unaff_ESI + 0x1ec) = 0;   // +0x1ec: some flag (inputLocked)
        
        // Virtual calls on the manager: release the slot
        (**(code **)(*vtablePtr + 0x6c))(*(int *)(unaff_ESI + 0x1c8), 0);
        // Set the action ID with a timeout of 50 (ms?)
        (**(code **)(*gInputManager + 0x9c))(savedActionId, 50);
        // Remove the slot entirely
        (**(code **)(*gInputManager + 0xa0))(*(int *)(unaff_ESI + 0x1c8));

        InputManager::debugLog("Input slot released");
    }
    return;
}