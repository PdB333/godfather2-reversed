// FUNC_NAME: SimManager::processPendingCallbacks
void __fastcall SimManager::processPendingCallbacks(SimManager* this)
{
    struct PendingList {
        SimManager** array;   // +0x00: pointer to array of SimManager pointers? (actually callback objects)
        int count;            // +0x04: number of entries
    }* pendingList;

    // Check re-entrancy guard (bit 25 of flags) and that pending list is valid
    if (((this->flags >> 0x19) & 1) == 0 && this->pendingList != nullptr)
    {
        // Set re-entrancy flag (bit 25) to prevent recursion
        this->flags |= 0x2000000;

        // Iterate through pending list in reverse order
        pendingList = reinterpret_cast<PendingList*>(this->pendingList);
        int count = pendingList->count;
        for (int i = count - 1; i >= 0; i--)
        {
            SimManager* callbackObj = pendingList->array[i];
            if (callbackObj != nullptr)
            {
                // Call virtual method at vtable offset 0x0C (index 3): likely a callback like onUpdate
                (*(void(__thiscall**)(SimManager*))(*callbackObj + 0x0C))(this);
            }
        }

        // Post-update cleanup function
        FUN_007909d0();
    }
}