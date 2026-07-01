// FUNC_NAME: GodfatherGameManager::getInstance
// Address: 0x00835950
// Role: Returns the singleton instance of the GodfatherGameManager.
// This function simply returns the value stored in the global pointer DAT_00e53ed8.
// The global is initialized elsewhere (likely during engine startup) and holds a pointer
// to the single GameManager instance for the game session.

class GodfatherGameManager;

// Declare the global variable holding the singleton pointer
extern GodfatherGameManager* DAT_00e53ed8;

class GodfatherGameManager {
public:
    // Returns the singleton instance of GodfatherGameManager.
    static GodfatherGameManager* getInstance() {
        return DAT_00e53ed8;
    }
};