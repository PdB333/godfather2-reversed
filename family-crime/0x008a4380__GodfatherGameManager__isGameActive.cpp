// FUNC_NAME: GodfatherGameManager::isGameActive
bool GodfatherGameManager::isGameActive(void)
{
    // Check if the game state pointer at +0xc is null and if the bit at offset +0x37c, bit 5 is clear.
    // If both conditions are true, the game is not active.
    if ((*(int *)(DAT_01223484 + 0xc) == 0) && ((*(uint *)(DAT_01223484 + 0x37c) >> 5 & 1) == 0)) {
        return false;
    }
    return true;
}