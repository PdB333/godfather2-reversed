// FUNC_NAME: InputDeviceManager::getFirstActivePlayer
int InputDeviceManager::getFirstActivePlayer()
{
    InputDeviceManager* mgr = gInputManager;  // DAT_012233a0
    if (mgr == 0)
        return 0;

    uint slotCount = getControllerCount();  // FUN_0043ff40 - returns number of controller slots
    for (uint i = 0; i < slotCount; i++) {
        ControllerSlot* slot = *(ControllerSlot**)(mgr->m_slots + i * 4);  // mgr + 0x4 is array of pointer slots
        if (slot != 0) {
            int playerId = slot->isActive();  // vtable[0x0c] - returns player index or 0 if not active
            if (playerId != 0 && isInputEnabled()) {  // FUN_00481620 - global input enabled check
                return playerId;
            }
        }
    }
    return 0;
}