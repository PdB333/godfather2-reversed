// FUNC_NAME: GodfatherGameManager::setMaxWantedLevel
void GodfatherGameManager::setMaxWantedLevel(uint level)
{
    // Clamp the wanted level to the maximum allowed (5)
    if (5 < level) {
        *(uint *)(DAT_0122350c + 0x174c) = 5;
        return;
    }
    *(uint *)(DAT_0122350c + 0x174c) = level;
    return;
}