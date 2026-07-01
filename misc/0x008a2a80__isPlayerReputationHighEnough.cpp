// FUNC_NAME: isPlayerReputationHighEnough
// Address: 0x008a2a80
// Role: Checks if the player's reputation level is above 2 (i.e., at least 3).
// Calls a global singleton (likely GodfatherGameManager) and retrieves the player object,
// then queries the reputation level from the player's vtable (offset 0x50).
// Returns true if the level is > 2, or if any intermediate pointer is null (default permissive).

// Forward declarations / vtable layouts (inferred)
class PlayerReputationTracker; // class with vtable, slot 0x50 = getReputationLevel()
class Player; // class with vtable, slot 0x30 = getReputationTracker() returning PlayerReputationTracker*
class GodfatherGameManager; // global singleton, vtable slot 0x30 = getPlayer() returning Player*

// Function that returns the global singleton (e.g., GodfatherGameManager::getInstance())
GodfatherGameManager* __fastcall GetGodfatherGameManager(void);

bool isPlayerReputationHighEnough()
{
    GodfatherGameManager* gameMgr = GetGodfatherGameManager();
    if (gameMgr != nullptr)
    {
        // Call virtual function at vtable offset 0x30 (getPlayer)
        Player* player = gameMgr->getPlayer();
        if (player != nullptr)
        {
            // Call virtual function at vtable offset 0x50 (getReputationLevel)
            uint reputationLevel = player->getReputationLevel();
            return (reputationLevel > 2);
        }
    }
    // Default to true if any object missing (allows actions to proceed without crash)
    return true;
}