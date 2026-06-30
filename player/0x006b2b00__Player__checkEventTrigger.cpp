// FUNC_NAME: Player::checkEventTrigger
// Function address: 0x006b2b00
// Called from Player::update (0x006b3cc0)
// Checks if a state flag is clear, then triggers events based on a lookup and comparison with a global manager.

void __thiscall Player::checkEventTrigger(void)
{
    // +0xC4: m_bStateFlag (likely a boolean or bitfield indicating some state)
    if (*(int*)(this + 0xC4) == 0)
    {
        // Trigger event with hash 0x8441d639 (e.g., EVENT_ENTER_COMBAT)
        FUN_00894c90(0x8441d639); // likely triggerEvent or sendMessage

        // Look up an object by hash 0x637b907 (e.g., a mission or target ID)
        int* obj = (int*)FUN_008c74d0(0x637b907); // likely getObjectByID
        if (obj != nullptr)
        {
            // +0x118: m_pTarget or m_pCurrentMission
            // DAT_0112a558: gGameManager (global singleton)
            // +0x40: m_pActivePlayer or m_pPlayer
            if (*(int*)(obj + 0x118) == *(int*)(*(int*)0x0112a558 + 0x40))
            {
                // Trigger another event with hash 0xdfa40562 (e.g., EVENT_LEAVE_COMBAT)
                FUN_00894c90(0xdfa40562);
            }
        }
    }
}