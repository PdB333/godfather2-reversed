// FUNC_NAME: MissionObjective::processTimerCompletion
void MissionObjective::processTimerCompletion(void)
{
    // Global mutex used for synchronization
    LockMutex(&gMutex);

    // Check if the timer (double at +0x100) is active
    if (this->timerValue != 0.0)
    {
        // Reset the timer to zero
        this->timerValue = 0.0;

        // Only proceed if the objective state is "ready" (1)
        if (this->objectiveState == 1)
        {
            // Build an event/parameter block
            // First call: initialise message with global pointer, some ID from vtable, and type 4
            BeginEventMessage(gMissionManager, *(int*)((*(int**)this->vtablePtr)[0x10]), 4, &eventBlock);

            // Copy the (now zero) timer and an additional value into the block
            eventBlock.timer = this->timerValue;
            eventBlock.extraValue = this->extraData;

            // Finalise and send the event
            SerializeBlock();
            SendEventMessage(4, &eventBlock);
            EndEventMessage();
        }
    }

    UnlockMutex(&gMutex);
    return;
}