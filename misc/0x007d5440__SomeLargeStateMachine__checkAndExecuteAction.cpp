// FUNC_NAME: SomeLargeStateMachine::checkAndExecuteAction
bool SomeLargeStateMachine::checkAndExecuteAction()
{
    bool result = false;
    // Check bit 4 of flags at offset 0x8e0 (likely a bitfield member)
    if (((*(uint32_t*)(this + 0x8e0) >> 4) & 1) != 0)
    {
        if (checkCondition())   // FUN_007d4200 - probably a per-frame condition check
        {
            doAction();         // FUN_00798480 - likely a global or static action function
            result = true;
        }
    }
    return result;
}