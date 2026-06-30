// FUNC_NAME: Player::clearInputFlags
int Player::clearInputFlags(void* unused, uint flagMask)
{
    // Check global game manager flag at offset 0x1744 (e.g., m_bIsActive)
    if (*(char*)((int)g_pGameManager + 0x1744) != '\0')
    {
        // Get current player object via helper function
        int* playerObj = getCurrentPlayer();
        if (playerObj != 0)
        {
            // Clear specified bits from input flags at offset 0x250
            *(uint*)(playerObj + 0x250) &= ~flagMask;
            return 1;
        }
    }
    return 0;
}