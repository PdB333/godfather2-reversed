// FUNC_NAME: EventScheduler::cancelEvent
void __fastcall EventScheduler::cancelEvent(EventScheduler* this)
{
    // +0x60: flags (uint32), bit 2 indicates active callback
    // +0x10: callback registration data (structure passed to FUN_005c02f0)
    FUN_004df600(); // likely update or validate state
    if ((this->flags & 0x4) != 0) // check bit 2
    {
        // Remove the callback: FUN_005c02f0(dest, callbackFunc, param)
        FUN_005c02f0(&this->callbackData, FUN_00979ac0, 1);
        this->flags &= ~0x4; // clear bit 2
    }
}