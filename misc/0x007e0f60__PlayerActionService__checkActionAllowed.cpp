// FUNC_NAME: PlayerActionService::checkActionAllowed
// Address: 0x007e0f60 - Checks if a given action can be performed based on player state.
// Called from 0x007e3e30 (likely PlayerActionService::updateActions).
// param_1: this pointer to PlayerActionService
// param_2: pointer to an ActionContext (has vtable with virtual methods)
// The function queries the action's readiness, then validates required items from player data.

bool __thiscall PlayerActionService::checkActionAllowed(int this, int* actionContext)
{
    // vtable offset +0x14c -> IsReady() virtual method
    typedef bool (__thiscall *ActionContextIsReady)(int*);
    ActionContextIsReady isReady = *(ActionContextIsReady*)(*actionContext + 0x14c);
    if (!isReady(actionContext)) {
        return false;
    }

    // this+0x58: pointer to large player state structure (e.g., PlayerState or GodfatherGameManager)
    int* playerData = *(int**)(this + 0x58);

    // Check if the action's first required item (from playerData+0x1f68) is present
    if (!validateActionItem(actionContext, *(int*)(playerData + 0x1f68))) {
        return false;
    }

    // Check if the action's second required item (from playerData+0x1f6c) is present
    if (!validateActionItemSecondary(actionContext, *(int*)(playerData + 0x1f6c))) {
        return false;
    }

    // Check a flag at playerData+0x8e3, bit 0 (maybe cooldown or state lock)
    if ((*(unsigned char*)(playerData + 0x8e3) & 1) != 0) {
        return false;
    }

    return true;
}