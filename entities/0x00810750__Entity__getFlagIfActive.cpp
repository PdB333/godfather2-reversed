// FUNC_NAME: Entity::getFlagIfActive
uint Entity::getFlagIfActive(uint flag)
{
    uint output;
    char conditionResult;
    
    output = 0;
    // Call virtual function at vtable+0x10 (likely isActive or checkState)
    conditionResult = (this->vtable->checkState)(flag, &output);
    // Return flag if condition is true, otherwise 0
    return (conditionResult != '\0') ? flag : 0;
}