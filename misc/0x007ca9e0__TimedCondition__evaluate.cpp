// FUNC_NAME: TimedCondition::evaluate

bool __thiscall TimedCondition::evaluate(int thisPtr, int param2, int param3, int param4)
{
    int* timer = (int*)(thisPtr + 0x20);
    *timer = *timer - 1;
    int localValue = thisPtr;
    if (*timer < 0)
    {
        *(int*)(thisPtr + 0x20) = 8;
        if ((*(int*)(thisPtr + 0x14) == 0) ||
            (getValueFromSource(*(int*)(thisPtr + 0x14), &localValue) == false) ||
            (localValue <= *(int*)(thisPtr + 0x18)))
        {
            *(int*)(thisPtr + 0x1c) = *(int*)(thisPtr + 0x1c) + 1;
        }
        else
        {
            *(int*)(thisPtr + 0x18) = localValue;
            *(int*)(thisPtr + 0x1c) = 0;
        }
    }
    int conditionType = *(int*)(thisPtr + 4);
    if (conditionType != 0)
    {
        int mode = *(int*)(conditionType + 0x24) & 3;
        if (mode == 0)
        {
            return checkConditionFirst(param2);
        }
        if (mode == 1)
        {
            return checkConditionSecond(param3);
        }
        if (mode == 2)
        {
            return checkConditionSecond(param4);
        }
        if (mode == 3)
        {
            return checkConditionFirst(param2) &&
                   checkConditionSecond(param3) &&
                   checkConditionSecond(param4);
        }
    }
    return true;
}