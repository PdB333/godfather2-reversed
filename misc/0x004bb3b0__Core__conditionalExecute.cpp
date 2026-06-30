// FUNC_NAME: Core::conditionalExecute
uint Core::conditionalExecute(uint context)
{
    uint result = Core::checkReady();
    if ((char)result != '\0')
    {
        result = Core::performAction(context);
        return result;
    }
    // Mask out lower 16 bits to return status flags
    return result & 0xffff0000;
}