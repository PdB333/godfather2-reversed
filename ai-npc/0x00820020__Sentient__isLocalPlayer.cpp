// FUNC_NAME: Sentient::isLocalPlayer
// Address: 0x00820020
// Checks if this sentient entity is the local player controlled by the user.
// Depends on global game manager initialization and current local player ID.
// Reconstructed from Ghidra decompile.

#include <cstdint>

// Forward declarations
struct GodfatherGameManager; // Global singleton at 0x0112af70

// Global pointer to game manager singleton
extern GodfatherGameManager* gGodfatherGameManager;

// GodfatherGameManager offsets:
// +0x48: bool mGameStarted  // Whether game has started
// Methods assumed: getLocalPlayerID() returns int

// Sentinel base class (or Player class) with:
// +0xE4: int mPlayerID       // Unique identifier for this entity

bool Sentient::isLocalPlayer() {
    // Only check if game manager is initialized and game has started
    if (gGodfatherGameManager != nullptr && gGodfatherGameManager->mGameStarted) {
        int localPlayerId = gGodfatherGameManager->getLocalPlayerID();
        return mPlayerID == localPlayerId;
    }
    return false;
}