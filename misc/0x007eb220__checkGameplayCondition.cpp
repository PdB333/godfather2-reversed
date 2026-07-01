// FUNC_NAME: checkGameplayCondition
uint checkGameplayCondition()
{
    // 0x3f = 63, possibly a manager index or object ID
    void* manager = getManager(0x3f);
    uint condition = isConditionMet(manager);
    if ((char)condition != 0)
    {
        // If condition is true, fetch some value with argument 1
        return getSomeValue(1);
    }
    // Otherwise return the condition with low byte cleared (mask out boolean)
    return condition & 0xffffff00;
}