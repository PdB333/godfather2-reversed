// FUNC_NAME: PlayerActionableInfo::startActionForTarget
void __thiscall PlayerActionableInfo::startActionForTarget(PlayerActionableInfo* this, int targetId)
{
    int originalTarget = targetId;  // preserve original target parameter
    bool canProceed;
    
    // Check if global state (e.g., paused or cutscene) prevents actions
    canProceed = isGlobalActionAllowed();  // FUN_007f47a0
    if (canProceed) {
        return;
    }
    
    targetId = 0;  // reuse as output pointer
    // Look for an existing action entry for this target in the action list at this+0x98
    ActionEntry* existing = findActionByTarget(*(ActionList**)(this + 0x98), originalTarget, &targetId);
    if (existing != nullptr) {
        // Mark the existing action as started (offset +0x08)
        existing->m_started = 1;
        return;
    }
    
    // Check if the current state allows starting a new action (via pointer at this+0x58)
    canProceed = canStartNewAction(*(int*)(this + 0x58));  // FUN_0071f3b0
    if (!canProceed) {
        return;
    }
    
    // Local structure for temporary action data (likely to be processed and freed)
    ActionData actionData = {0};
    actionData.m_init = 0;
    
    // Initialize/reset something related to the target
    resetTargetAction(originalTarget);  // FUN_006e61a0
    
    // Mark that the action has been initialized
    actionData.m_initialized = 1;
    
    // Process the action (may allocate internal memory stored in actionData.ptr)
    processAction(&actionData);  // FUN_007e3720
    
    // Set this object’s action-in-progress flag (offset +0x80)
    *(char*)(this + 0x80) = 1;
    
    // If the processed action allocated memory, free it
    if (actionData.ptr != nullptr) {
        deallocateActionMemory(actionData.ptr);  // FUN_004daf90
    }
}