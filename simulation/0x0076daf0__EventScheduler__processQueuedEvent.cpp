// FUNC_NAME: EventScheduler::processQueuedEvent
void __thiscall EventScheduler::processQueuedEvent(int eventParam)
{
    // Check if the pending event flag (bit 1) is set (offset +0x74)
    if ((this->flags & 0x02) != 0) {
        // Call the actual event handler using the stored callback object (+0x5c) and the param
        FUN_0093b460(this->callbackObject, eventParam);
        // Clear the pending flag
        this->flags &= ~0x02;
    }
}