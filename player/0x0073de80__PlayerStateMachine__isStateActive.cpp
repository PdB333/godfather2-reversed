// FUNC_NAME: PlayerStateMachine::isStateActive
// Function at 0x0073de80: checks if a given state condition is met
// __thiscall, returns bool
// param_1 = this
// param_2, param_3, param_5 = additional args passed to base implementation
// param_4 = state query type (10, 11, 12, others)

bool __thiscall PlayerStateMachine::isStateActive(int param_2, int param_3, int stateType, int param_5)
{
    // this+0x5c = currentStateId? (compared to 0x48)
    // this+0x64 = pointer to sub-state object (offset 0x48 relative to parent)
    int subStateParentPtr;
    int *subStateParent;

    if (stateType == 10) // State query type 10: check if some flag is zero AND currentStateId matches
    {
        if (*(int *)(this + 100) == 0) // +0x64
        {
            subStateParentPtr = 0;
        }
        else
        {
            subStateParentPtr = *(int *)(this + 100) - 0x48; // subtract offset to get parent
        }
        if (*(int *)(subStateParentPtr + 0x84) == 0) // parent flag at +0x84
        {
            return false;
        }
        if (*(int *)(this + 0x5c) != 0) // current state ID
        {
            return *(int *)(this + 0x5c) == 0x48; // check if equals 0x48
        }
        // fallthrough to end: return true
    }
    else if (stateType == 11) // State query type 11: check if flag is non-zero (opposite of type 10's first check)
    {
        if (*(int *)(this + 100) == 0)
        {
            subStateParentPtr = 0;
        }
        else
        {
            subStateParentPtr = *(int *)(this + 100) - 0x48;
        }
        if (*(int *)(subStateParentPtr + 0x84) != 0)
        {
            return false;
        }
        return true;
    }
    else if (stateType != 12) // Unknown type, delegate to base implementation
    {
        return FUN_004ac640(param_2, param_3, stateType, param_5);
    }
    else // State query type 12: check if pointer equals 0x48 (likely state ID)
    {
        if (*(int *)(this + 100) != 0)
        {
            return *(int *)(this + 100) == 0x48;
        }
        // fallthrough to end: return true (if pointer is null)
    }
    return true;
}