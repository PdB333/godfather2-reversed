// FUNC_NAME: ActionCapabilityManager::canPerformAction
bool __thiscall ActionCapabilityManager::canPerformAction(ActionCapabilityManager* this, uint actionId)
{
    // +0x68: pointer to capability data structure
    CapabilityData* capData = *(CapabilityData**)((char*)this + 0x68);
    
    // Get the required capability mask for this action (e.g. which global capability bits it needs)
    uint requiredCapMask = getActionCapabilityMask(actionId);  // FUN_007e04a0
    
    // Mask for action types that are checked against global capabilities
    const uint ACTION_TYPE_MASK = 0xffff502f;
    uint actionTypeBits = actionId & ACTION_TYPE_MASK;
    
    // First check: if action has relevant type bits, ensure they are all set globally
    if (actionTypeBits != 0 && ((capData->globalCapabilityMask & actionTypeBits) == actionTypeBits))
    {
        // Second check: retrieve the current capability mask for this entity
        // and verify it exactly matches the given action ID
        uint currentCapMask = getCurrentCapabilityMask(requiredCapMask);  // FUN_007e0790
        if (currentCapMask == actionId)
        {
            return true;
        }
    }
    return false;
}