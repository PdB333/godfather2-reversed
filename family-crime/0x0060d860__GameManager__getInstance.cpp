// FUNC_NAME: GameManager::getInstance

// Function address: 0x0060d860
// Returns a global singleton pointer to the game manager.
// This is a simple accessor used throughout the codebase to obtain the active GameManager instance.

GameManager* GameManager::getInstance()
{
    // Global variable holding the singleton instance pointer
    // DAT_012058a4 is set during game initialization and never changes
    return reinterpret_cast<GameManager*>(DAT_012058a4);
}