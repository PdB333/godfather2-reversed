// FUNC_NAME: BehaviorManager::update
// Address: 0x006fdaf0
// Reconstructed method of BehaviorManager class, called to update behavior per frame.
// this offsets: +0x18 = pBehavior (Behavior*), +0x28 = currentStateId (int), +0x2c = flags (byte), +0x35 = updatePending (byte)
// param_2 = UpdateContext* (with bool at +0xc indicating special condition, e.g. bProcessInput)
// Global pointer at 0x0112a9f4 + 0x208 is a global active state ID tracker (e.g., g_pGlobalStateManager->activeStateId)

void __thiscall BehaviorManager::update(BehaviorManager* thisPtr, UpdateContext* updateContext)
{
    // Check if this manager has a current state assigned and if it matches the globally active state
    if ((thisPtr->currentStateId != -1) &&
        (*(int*)(DAT_0112a9f4 + 0x208) == thisPtr->currentStateId))
    {
        // Deactivate global state: set to -1 and call global state change handler
        *(int*)(DAT_0112a9f4 + 0x208) = -1;
        BehaviorManager::deactivateGlobalState(); // Originally FUN_005e6640 with &LAB_006fd640 as argument
    }

    // If the manager has an active behavior object, update it
    if (thisPtr->pBehavior != 0)
    {
        // Update the behavior with the context (passes through to child)
        Behavior::update(thisPtr->pBehavior, updateContext); // Originally FUN_005e2ad0

        // Check flag bit 3 (0x08) in this manager's flags
        if ((thisPtr->flags & 0x08) != 0)
        {
            BehaviorManager::onFlagTrigger(); // Originally FUN_006fd240
        }

        // If the update context indicates a special condition (e.g., input processed)
        if (updateContext->bSpecialCondition) // offset +0xc != 0
        {
            BehaviorManager::handleSpecialCondition(); // Originally FUN_006fd030
        }

        // Clear the pending update flag
        thisPtr->updatePending = 0; // offset +0x35
    }

    return;
}

// Helper function declarations (placeholders for actual implementations):
// void BehaviorManager::deactivateGlobalState(void); // Sets global state to -1 and possibly triggers deactivation logic
// void Behavior::update(Behavior* pBehavior, UpdateContext* context); // Called on child behavior
// void BehaviorManager::onFlagTrigger(void); // Called when flag bit 3 is set
// void BehaviorManager::handleSpecialCondition(void); // Called when updateContext->bSpecialCondition is true

// Note: Offsets are deduced from code:
// this + 0x28: int currentStateId
// this + 0x18: Behavior* pBehavior
// this + 0x2C: byte flags (bit 3 = 0x08)
// this + 0x35: byte updatePending (set to 0 at end)
// updateContext + 0x0C: boolean bSpecialCondition (likely 1 byte char)