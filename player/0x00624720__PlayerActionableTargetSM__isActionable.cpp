// FUNC_NAME: PlayerActionableTargetSM::isActionable
bool PlayerActionableTargetSM::isActionable(void)
{
    // Check if the target entity pointer (offset +0x18) is valid,
    // the action data pointer (offset +0x20) is valid,
    // and the flags (offset +0x14) do NOT have bit 2 (0x4) set.
    // If all conditions are met, the target is NOT actionable (returns false).
    // Otherwise, it is actionable (returns true).
    if (((*(int *)(this + 0x18) != 0) && (*(int *)(this + 0x20) != 0)) &&
       ((*(byte *)(this + 0x14) & 4) == 0)) {
        return false;
    }
    return true;
}