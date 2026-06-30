// FUNC_NAME: SomeGameObject::isActionAllowed

bool __thiscall SomeGameObject::isActionAllowed(uint actionId) // param_2 is likely an action identifier/context
{
    char secondaryResult;

    // Check if the disable flag (bit 0 at +0x114) is set → reject immediately
    if ((*(byte*)(this + 0x114) & 1) != 0)
        return false;

    // Check if state counter (short at +0x8c) is already at or above threshold (+0xb4)
    // AND secondary condition fails (function returns 0)
    if (*(short*)(this + 0x8c) <= *(short*)(this + 0xb4))
    {
        secondaryResult = FUN_007273a0(actionId); // checkSecondaryCondition
        if (secondaryResult == '\0')
            return false;
    }

    // Check spatial bounds: reject if current vertical component (+0x88) exceeds a global maximum
    // and sum of horizontal and vertical components (+0x84 + +0x88) exceeds another bound
    if (g_minHeight < *(float*)(this + 0x88) &&
        g_maxSum <= *(float*)(this + 0x84) + *(float*)(this + 0x88))
    {
        return false;
    }

    // Examine flag word at +0x110
    uint flags = *(uint*)(this + 0x110);

    // Bit 7: if clear, check bit 6
    if ((flags >> 7 & 1) == 0)
    {
        // Bit 6: if clear → fully allowed
        if ((flags >> 6 & 1) == 0)
            return true;

        // Bit 6 set → check global game state
        return FUN_00726040() != '\0'; // returns true only if game state is valid
    }

    // Bit 7 set: check a global integer threshold (range 8 to 19)
    int globalCounter = *(int*)(g_someGlobal + 100);
    if (globalCounter > 7 && globalCounter < 20)
        return false;

    return true;
}