// FUNC_NAME: ActionHandler::processActionEvent
// Address: 0x0044fbd0
// Role: Processes an action event (button press/release/hold) for an input action handler.
// Checks per-thread flags, action type, and dispatches to appropriate handler.
// Finally stores this handler into a global list for deferred processing.

void __thiscall ActionHandler::processActionEvent(uint param_1)
{
    // Per-thread data pointer (from TLS: fs:[0x2c])
    ThreadLocalData* pTls = *(ThreadLocalData**)__readfsdword(0x2c);

    // Access global flag array at offset 0x7c, indexed by this->m_actionIndex (+0x18)
    // m_actionIndex is likely an action ID (e.g., controller button index)
    uint flags = pTls->flagArray[this->m_actionIndex]; // Flag array at pTls+8 + 0x7c

    // If the "disabled" flag (0x8000) is set and not already processed (0x200), skip
    if ((flags & 0x8000) == 0 || (flags & 0x200) != 0)
        goto storeThis;

    // Check action type stored at +0x20
    int actionType = this->m_actionType;

    // Handle press (1), hold (2), or release (0xF) actions
    if (actionType == 2 || actionType == 1 || actionType == 0xF)
    {
        ActionHandler::handleDefaultAction(); // 0x0044fdb0
    }
    else
    {
        // Handle special action type (0x12) - e.g., menu or cancel
        if (actionType == 0x12)
        {
            char isBlocked = ActionHandler::isActionBlocked(this); // 0x0044d910
            if (isBlocked != 0)
                goto setProcessedFlag; // Skip normal handling if blocked
        }

        // Dispatch based on flag 0x100 (alternate handler)
        if ((flags & 0x100) == 0)
            ActionHandler::handleActionRaw(this, param_1); // 0x004500a0
        else
            ActionHandler::handleActionMapped(this, param_1); // 0x0044ffe0
    }

setProcessedFlag:
    // Set the "processed" flag (0x200) in the global flag array
    pTls->flagArray[this->m_actionIndex] |= 0x200;

storeThis:
    // Global action handler manager (stored at DAT_01206880 + 0x14)
    // The manager maintains a growing stack of handler objects for deferred execution.
    // It stores a vtable pointer (PTR_LAB_0110b8c8) and then the 'this' pointer.
    ActionHandlerManager* pManager = *(ActionHandlerManager**)(g_globalActionManager + 0x14);
    pManager->vtablePtr = &PTR_LAB_0110b8c8; // Set vtable for the stored item
    pManager->stackTop = (void*)((int)pManager->stackTop + 4);
    void* alignedSlot = (void*)((int)pManager->stackTop & ~3); // Align to 4 bytes
    pManager->stackTop = alignedSlot;
    *(void**)alignedSlot = this; // Store 'this' into the slot
    pManager->stackTop = (void*)((int)pManager->stackTop + 4);
    return;
}