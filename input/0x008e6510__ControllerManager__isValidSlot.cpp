// FUNC_NAME: ControllerManager::isValidSlot
bool ControllerManager::isValidSlot(void)
{
    int status = this->getSlotStatus();
    return status >= 0;
}