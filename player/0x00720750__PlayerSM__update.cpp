// FUNC_NAME: PlayerSM::update
void __fastcall PlayerSM::update(int this)
{
    char cVar1;
    int pPlayerObj;

    // m_pPlayerData at +0x4 holds a pointer to the player's data block (or null/0x48 sentinel)
    int playerDataPtr = *(int*)(this + 4);
    if (playerDataPtr != 0 && playerDataPtr != 0x48)  // 0x48 is a special invalid handle?
    {
        // Derive the actual player object by subtracting the offset of the data block within it
        pPlayerObj = (playerDataPtr == 0) ? 0 : (playerDataPtr - 0x48);
        // Check bit 25 of flags at +0x1f58 (e.g., m_flags & 0x02000000)
        if ((*(unsigned int*)(pPlayerObj + 0x1f58) & (1 << 25)) == 0)
        {
            // Recompute player pointer (redundant, but follows decompiled pattern)
            pPlayerObj = (playerDataPtr == 0) ? 0 : (playerDataPtr - 0x48);
            // Check bit 0 of byte at +0x8e6 (e.g., m_bCanDoAction)
            if ((*(unsigned char*)(pPlayerObj + 0x8e6) & 1) == 0)
            {
                // Reset or prepare something internally
                sub_0072feb0();
                cVar1 = sub_007f7c50();  // Returns 0 if the player is allowed to proceed
                if (cVar1 == '\0')
                {
                    pPlayerObj = (playerDataPtr == 0) ? 0 : (playerDataPtr - 0x48);
                    sub_006f8d40(pPlayerObj, 0);  // Transition the player to a specific state (state 0)
                }
            }
            // Recompute again
            pPlayerObj = (playerDataPtr == 0) ? 0 : (playerDataPtr - 0x48);
            // Check if the player is not stunned (m_bStunned at +0x162) and another condition holds
            if ((*(char*)(pPlayerObj + 0x162) == '\0') && (cVar1 = sub_0071fa90(), cVar1 != '\0'))
            {
                sub_00720560();  // Execute the intended action (e.g., start a grapple or cover transition)
            }
        }
    }
    // Reset timers/cooldowns belonging to this state machine instance
    *(unsigned int*)(this + 0x1c) = 0;
    *(unsigned int*)(this + 0xc) = 0;
}