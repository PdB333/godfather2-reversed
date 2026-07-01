// FUNC_NAME: GameManager::getInstance
class GameManager;

// Global pointer to the singleton GameManager instance (address 0x00e54500)
extern GameManager* g_pGameManager;

// Returns the global singleton GameManager pointer
// This function acts as a simple accessor for the singleton instance.
GameManager* GameManager::getInstance()
{
    return g_pGameManager;
}