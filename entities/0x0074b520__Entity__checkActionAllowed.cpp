// FUNC_NAME: Entity::checkActionAllowed

bool __thiscall Entity::checkActionAllowed(int param2, int param3, int actionType, int param5)
{
    uint stateFlags = *(uint *)((int)this + 0x70);  // +0x70: bitfield of state flags
    int *actionPtr = *(int **)((int)this + 0x88);   // +0x88: pointer to current action or state

    if (actionType == 0x15)
    {
        // Check bit1 of stateFlags (i.e., flag at bit index 1)
        if (!((stateFlags >> 1) & 1))
            return false;
        // Fall through: if flag set, return whether actionPtr is null
    }
    else if (actionType == 0x16)
    {
        // Check bit2 of stateFlags (inverted logic)
        byte invertedBit = ~(byte)(stateFlags >> 2);
        // Return true iff bit2 is clear (invertedBit & 1 != 0)
        return (invertedBit & 1) != 0;
    }
    else if (actionType != 0x17)
    {
        // Delegate to generic handler for other action types
        return FUN_0074ab00(param2, param3, actionType, param5);
    }
    // For 0x15 (if flag set) and 0x17, return whether actionPtr is null
    return actionPtr == 0;
}