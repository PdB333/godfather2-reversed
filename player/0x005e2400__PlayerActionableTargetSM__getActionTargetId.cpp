// FUNC_NAME: PlayerActionableTargetSM::getActionTargetId
uint __thiscall PlayerActionableTargetSM::getActionTargetId(uint* outHandle)
{
    // Check if targeting is active (flag at +0x1744)
    if (*(char*)(this + 0x1744) != 0) {
        // Get the current target object (e.g., Player or target SM)
        uint targetObj = getActiveTarget(); // renamed from FUN_005e2150
        if (targetObj != 0) {
            // Read the target handle from the object (+0x250)
            uint handle = *(uint*)(targetObj + 0x250);
            *outHandle = handle;
            // Return the handle with the low byte forced to 1 (success indicator)
            return (handle & 0xFFFFFF00) | 1;
        }
    }
    // No target or inactive – return this pointer with low byte zeroed
    return ((uint)this) & 0xFFFFFF00;
}