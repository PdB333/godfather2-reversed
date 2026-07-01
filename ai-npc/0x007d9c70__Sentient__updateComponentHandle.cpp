// FUNC_NAME: Sentient::updateComponentHandle
void __fastcall Sentient::updateComponentHandle(Sentient* this)
{
    // +0x58: pointer to global game data structure (likely GameManager)
    GameManager* pGameMgr = *(GameManager**)((char*)this + 0x58);
    // Initialise smart pointer system (thunk to null check)
    initializeSmartPtrSystem();

    // Check if all four component IDs are empty (no existing component to adopt)
    if (pGameMgr->componentIDs[0] == 0 &&
        pGameMgr->componentIDs[1] == 0 &&
        pGameMgr->componentIDs[2] == 0 &&
        pGameMgr->componentIDs[3] == 0)
    {
        // Allocate a new component (size 0x1b0, params {type=2, arg1=0x10, arg2=0})
        AllocationParams params = {2, 0x10, 0};
        void* pAlloc = allocateMemory(0x1b0, &params);
        ComponentBase* pNewComp = (pAlloc != 0) ? constructComponent(pAlloc) : 0;
        // +0x48 offset moves from base to the handle subobject
        ComponentBase* pHandleSub = (pNewComp != 0) ? (ComponentBase*)((char*)pNewComp + 0x48) : 0;

        ComponentBase** ppSlot = (ComponentBase**)((char*)this + 0x90);
        if (*ppSlot != pHandleSub)
        {
            if (*ppSlot != 0)
                releaseSmartPtr(ppSlot);   // release old handle
            *ppSlot = pHandleSub;
            if (pHandleSub != 0)
                *(int*)((char*)this + 0x94) = *(int*)((char*)pHandleSub + 4); // copy field at +4
        }
    }
    else
    {
        // Adopt an existing component by ID lookup
        ComponentBase* pFound = findComponentByID(pGameMgr->componentIDs, 0);
        ComponentBase* pHandleSub = (pFound != 0) ? (ComponentBase*)((char*)pFound + 0x48) : 0;

        ComponentBase** ppSlot = (ComponentBase**)((char*)this + 0x90);
        if (*ppSlot != pHandleSub)
        {
            if (*ppSlot != 0)
                releaseSmartPtr(ppSlot);
            *ppSlot = pHandleSub;
            if (pHandleSub != 0)
                *(int*)((char*)this + 0x94) = *(int*)((char*)pHandleSub + 4);
        }
    }

    // Derive base component from the stored handle (reverse offset -0x48)
    ComponentBase* pBase = (*(ComponentBase**)((char*)this + 0x90) != 0)
        ? (ComponentBase*)((char*)*(ComponentBase**)((char*)this + 0x90) - 0x48)
        : 0;
    assignSmartPtr(pBase + 0x68);   // copy into temporary handle (offset +0x68)

    // Extract flag bit (bit 2 of pGameMgr->flags)
    uint8_t flag = (uint8_t)((pGameMgr->flags >> 2) & 1);

    // Temporary handle for internal reference
    ComponentHandle* pOtherSlot = (ComponentHandle*)((char*)pGameMgr + 0x48);
    ComponentHandle* tempHandle = 0;
    if (tempHandle != pOtherSlot)
    {
        if (tempHandle != 0)
            releaseSmartPtr(&tempHandle);
        tempHandle = pOtherSlot;
        if (pOtherSlot != 0)
            // Write address of local variable into pGameMgr+0x4c (self-reference)
            *(ComponentHandle***)((char*)pGameMgr + 0x4c) = &tempHandle;
    }

    char tempBuffer[40]; // stack buffer for smart ptr copy
    assignSmartPtr(tempBuffer);

    if (tempHandle != 0)
        releaseSmartPtr(&tempHandle);

    return;
}