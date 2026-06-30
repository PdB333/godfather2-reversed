// FUNC_NAME: GodfatherGameManager::isGameActive
// Address: 0x0072d260
// Checks if the game is active by testing whether the pointer at offset 0x2040 is non-null.
bool __thiscall GodfatherGameManager::isGameActive(GodfatherGameManager* this) {
    // Offset 0x2040: likely pointer to active game state or in-game flag
    return *(int*)((char*)this + 0x2040) != 0;
}