// FUNC_NAME: Player::setActionFlag
// Address: 0x005e2390
// Checks if the player is active (byte at +0x1744), then retrieves an action info object via getActionableInfo(),
// sets the given flag bits into the action flags (uint at +0x250), and returns true on success.

bool Player::setActionFlag(uint flagMask)
{
    if (m_bIsActive)  // byte at this+0x1744 (player active flag)
    {
        PlayerActionableInfo* pActionInfo = getActionableInfo(); // FUN_005e2150
        if (pActionInfo != nullptr)
        {
            pActionInfo->m_actionFlags |= flagMask; // uint at +0x250
            return true;
        }
    }
    return false;
}