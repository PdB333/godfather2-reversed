// FUNC_NAME: Player::activate
void __fastcall Player::activate(Player* this)
{
    // Global pointer to the currently active player (or similar singleton)
    if (g_pActivePlayer != nullptr) {
        // Call cleanup/deactivation function on the previous active player
        deactivatePreviousPlayer();
        // Clear the active flag of the previous player (offset +0x90)
        g_pActivePlayer->m_bActive = false;  // +0x90
    }
    // Mark this player as active (offset +0x9)
    this->m_bIsActive = true;  // +0x9
}