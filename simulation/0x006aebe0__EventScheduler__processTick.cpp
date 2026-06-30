// FUNC_NAME: EventScheduler::processTick
void __thiscall EventScheduler::processTick(EventScheduler* this, EventManager* eventMgr)
{
    // Increment internal tick counter (offset +0x1d4)
    this->tickCounter++;

    // If counter reached threshold (offset +0x1d8) and an active event handle exists (offset +0x1dc)
    if ((uint32_t)this->tickCounter >= this->tickThreshold)
    {
        if (this->activeEvent != 0)
        {
            int eventHandle = this->activeEvent;
            // Destroy the event (FUN_00408a00 is likely a destructor/callback)
            FUN_00408a00(&eventHandle, 0);
            // Clear the pointer at +0x1dc
            FUN_00408310(&this->activeEvent);
        }
    }

    // Try to fetch an event from the manager using a GUID string (0x6a8acf44)
    int* newEvent = nullptr;
    // vtable call at offset 0x10 – likely EventManager::getOrCreateEvent(const char* guid, int** outEvent)
    bool hasEvent = ((bool (__thiscall*)(EventManager*, int, int**))(*(void***)eventMgr)[4])(eventMgr, 0x6a8acf44, &newEvent);
    if (hasEvent && this != 0)
    {
        newEvent = nullptr;
        int oldHead = 0;

        // Check if the manager's linked list node at +0x12 exists (head pointer)
        if (&eventMgr->headNode != 0) // +0x12 is a pointer to a node
        {
            // Store current next pointer (offset +0x13)
            oldHead = eventMgr->nextNode; // +0x13
            // Replace next pointer with address of local newEvent (intrusive list manipulation)
            eventMgr->nextNode = (int)&newEvent;
            // Point local newEvent to the manager's head node
            newEvent = &eventMgr->headNode; // +0x12
        }

        // Use a global string (DAT_0112ade8) for some debug/log output
        int stringArg = 0x112ade8;
        char stackBuf = 0;
        FUN_00408a00(&stringArg, 0);

        // Clean up the local list node if it was set
        if (newEvent != 0)
        {
            FUN_004daf90(&newEvent);
        }
    }
}