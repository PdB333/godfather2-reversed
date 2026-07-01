// FUNC_NAME: Entity::setActionTimer
void __thiscall Entity::setActionTimer(float time, int actionType, int actionSubType)
{
    // +0x910: actionFlags (set to 0, indicating timer reset)
    *(int *)(this + 0x910) = 0;
    // +0x914: actionType (e.g., animation or state ID)
    *(int *)(this + 0x914) = actionType;
    // +0x918: actionSubType (e.g., variant or sub-state)
    *(int *)(this + 0x918) = actionSubType;
    // +0x91c: remainingTime = time - startTime (startTime at +0x920)
    *(float *)(this + 0x91c) = time - *(float *)(this + 0x920);
}