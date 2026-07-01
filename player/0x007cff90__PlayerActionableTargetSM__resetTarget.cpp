// FUNC_NAME: PlayerActionableTargetSM::resetTarget
void __thiscall PlayerActionableTargetSM::resetTarget(void *this)
{
    // Clear bit 0 of the action flag at offset +0xAC (likely 'isActionActive' or 'hasTarget')
    *(unsigned int *)((unsigned int)this + 0xAC) &= 0xFFFFFFFE;
    // Zero out the current target pointer at offset +0x7C (likely 'currentTarget' or 'activeAction')
    *(int *)((unsigned int)this + 0x7C) = 0;
    // Call external functions with argument 0 (likely global singletons or static methods)
    FUN_007ac6f0(0);   // e.g., InputManager::clearBinding or similar
    FUN_007ac770(0);   // e.g., ControllerManager::releaseFocus
    return;
}