// FUNC_NAME: SimNpc::canProcessUpdates
// Function at 0x008fe340: checks if the NPC can continue processing updates.
// Returns 0 (false) if all conditions prevent processing, 1 (true) otherwise.
int __fastcall SimNpc::canProcessUpdates(void)
{
    int state = getCurrentState();               // FUN_008fe1e0 - returns current state ID?
    if ((state == this->m_currentState) &&       // compares with field at +0x58
        (state = isAlive(state), state != 0) &&   // FUN_006b07e0 - checks if state is alive/valid
        ((this->m_flags == 0) ||                 // field at +0xC8 (200)
         ((this->m_flags == 0x48) ||             // flag value 72
          (state = isMenuOpen(), state == 0)))) // FUN_00791300 - check if any menu is open
    {
        return 0;  // all conditions met -> block processing
    }
    return 1;      // can process
}