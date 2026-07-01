// FUNC_NAME: Entity::checkActionFlag
bool __fastcall Entity::checkActionFlag(uint actionFlag)
{
    bool result = false;

    // Check if actionFlag bit 0x10000 is allowed: requires bit2 of flags1 to be set
    if (((actionFlag & 0x10000) == 0) || ((*(uint32*)(this + 0x8E8) >> 2 & 1) == 0))
    {
        // Check if actionFlag bit 0x20000 is allowed: requires bit0 of flags2 to be set
        if (((actionFlag & 0x20000) == 0) || ((*(byte*)(this + 0x8E3) & 1) == 0))
        {
            // Check actionFlag bit 0x40000: requires bit10 of flags3 to be set, then call external function
            if ((actionFlag & 0x40000) != 0 && ((*(uint32*)(this + 0x8E0) >> 10 & 1) != 0))
            {
                int extResult = FUN_00800ad0(); // external check
                if (extResult != 0)
                    goto setTrue;
            }

            // Check actionFlag bit 0x80000: requires bit10 of flags3 set, and state pointer at +0x74C not null and not 0x48
            if ((actionFlag & 0x80000) != 0 && ((*(uint32*)(this + 0x8E0) >> 10 & 1) != 0))
            {
                int statePtr = *(int*)(this + 0x74C);
                if (statePtr != 0 && statePtr != 0x48)
                {
                    int stateBase = (statePtr == 0) ? 0 : (statePtr - 0x48);
                    if (*(char*)(stateBase + 0x1A8) == 2)
                        goto setTrue;
                }
            }
        }
    }

    // If no condition triggered, result remains false
    goto end;

setTrue:
    result = true;

end:
    // If bit31 is set in actionFlag, invert the result
    if ((actionFlag & 0x80000000) == 0x80000000)
        return !result;
    return result;
}