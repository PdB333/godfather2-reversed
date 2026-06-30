// FUNC_NAME: ControllerManager::pollNextSlot
// Address: 0x0043d860
// Role: Checks if there is an active controller slot available; if so, processes it and returns true.
// Calls: getActiveControllerIndex (0x0043db90), processControllerSlot (0x0043db10)

bool __thiscall ControllerManager::pollNextSlot(void)
{
    int activeSlot;
    
    activeSlot = this->getActiveControllerIndex(); // Returns slot index (0-15) or -1 if none
    if (activeSlot >= 0)
    {
        this->processControllerSlot(); // Updates state for the found slot
        return true;
    }
    return false;
}