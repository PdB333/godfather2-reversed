// FUNC_NAME: BehaviorState::resolveCurrentTarget
int BehaviorState::resolveCurrentTarget(void)
{
    // this is in_EAX
    // Field offsets (in bytes):
    // +0x00: stateType (int)
    // +0x2c: flags (int)
    // +0x30: something (int) - maybe a pointer or ID
    // +0x34: pData (int*) - pointer to data
    // +0x38: pAltData (int*) - alternative pointer
    // +0x40: directTarget (int) - direct target ID

    int stateType = *(int*)this;                 // +0x00
    int flags = *(int*)((char*)this + 0x2c);     // +0x2c
    int* pData = (int*)*(int*)((char*)this + 0x34); // +0x34 pointer to data
    int* pAltData = (int*)*(int*)((char*)this + 0x38); // +0x38 pointer to alternative data
    int field_0x30 = *(int*)((char*)this + 0x30); // +0x30
    int directTarget = *(int*)((char*)this + 0x40); // +0x40

    if ((flags & 0x20) != 0)  // flag bit 5 set
    {
        if (stateType < 3)
        {
            // Use pAltData path when stateType < 3 and flag set
            if (pAltData != (int*)0x0)
                return *pAltData;
            else
                return -1;
        }
        else if (stateType == 2)  // note: this branch is unreachable due to earlier <3 check? Actually order: first condition checks stateType <3; if not, then check ==2. But stateType cannot be <3 and ==2 simultaneously. Possibly the decompiler ordering is wrong. The original code likely tests flag and then stateType.
        {
            return directTarget;
        }
    }

    // Flag not set, or stateType >=3 with flag set (but stateType==2 handled)
    if (field_0x30 != 0)
    {
        return -1;
    }

    // Use pData pointer
    if (pData != (int*)0x0)
        return *pData;
    else
        return -1;
}