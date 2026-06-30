// FUNC_NAME: EntityComponent::updateTimerState
void __fastcall EntityComponent::updateTimerState(void* this) {
    // +0xa4: eventState (int, 0=inactive, non-zero=active)
    // +0x84: flags (uint32, bit 29 = 0x20000000 indicates timer pending)
    // +0x80: timer structure (startTimer/cancelTimer operate on this)

    if (*(int*)((char*)this + 0xa4) != 0) {
        // Event is active
        if ((*(uint32_t*)((char*)this + 0x84) >> 0x1d & 1) == 0) {
            // Timer not yet pending – start it
            *(uint32_t*)((char*)this + 0x84) |= 0x20000000;  // set pending flag
            startTimer((char*)this + 0x80, 50);               // 0x32 = 50 ticks
            return;
        }
        // Timer already pending – nothing to do
        return;
    }

    // Event is inactive
    if ((*(uint32_t*)((char*)this + 0x84) >> 0x1d & 1) != 0) {
        // Timer was pending – cancel it
        cancelTimer((char*)this + 0x80);
        *(uint32_t*)((char*)this + 0x84) &= ~0x20000000;     // clear pending flag
    }
}