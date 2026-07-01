// FUNC_NAME: StreamManager::shutdown
void __fastcall StreamManager::shutdown(StreamManager* this)
{
    int previousState = *(int*)((int)this + 0x1c); // +0x1c: state field (0x10 = stopped)
    *(int*)((int)this + 0x1c) = 0;                // reset state to idle

    // Check global game state flags (all must be zero to allow shutdown)
    if ((*(int*)(DAT_011299bc + 0x4c) == 0) &&
        (*(int*)(DAT_011299bc + 0x50) == 0) &&
        (*(int*)(DAT_011299bc + 0x54) == 0) &&
        (*(int*)(DAT_011299bc + 0x58) == 0))
    {
        if (previousState != 0x10) // skip if already stopped
        {
            // Call stop() on the audio interface object (vtable at this+0x2c)
            (**(void (__fastcall**)(void*, int))this->audioInterface)(this->audioInterface, 0);
            // Call deallocate() on the same object via a separate vtable table (this+0x28)
            // Second vtable entry (offset 4) takes the object pointer and a size (0x3c)
            (**(void (__fastcall**)(void*, int, int))this->deallocVtable)(this->audioInterface, 0x3c);
            this->audioInterface = 0; // clear pointer
        }
    }
    else
    {
        // Game state not clean – process pending operations before shutdown
        FUN_0083a080(); // likely StreamManager::processPending()
    }

    // Build a temporary stop info structure and call stop function
    struct { int field0; int field4; char field8; } stopInfo;
    stopInfo.field0 = DAT_0112fe38; // global audio stop info base
    stopInfo.field4 = 0;
    stopInfo.field8 = 0;
    FUN_00408a00(&stopInfo, 0); // stops the pending audio operation

    // Stop/reset a global timer or queue
    FUN_00408680(&DAT_012069c4);
}