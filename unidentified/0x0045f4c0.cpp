// FUN_0045f4c0: InputManager::activateController
bool __thiscall InputManager::activateController(Controller* pController)
{
    bool bResult = false;
    // +0x218: pointer to active controller slots array
    if ((pController != nullptr) && (this->m_pActiveControllers != nullptr))
    {
        int iSlotIndex = getCurrentControllerSlot(); // FUN_00577d30
        if (iSlotIndex == -1)
        {
            iSlotIndex = allocateNewControllerSlot(); // FUN_00571b00
            return (iSlotIndex != -1);
        }
        bResult = true;
    }
    return bResult;
}