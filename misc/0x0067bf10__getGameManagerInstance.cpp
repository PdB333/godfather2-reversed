// FUNC_NAME: getGameManagerInstance
// Address: 0x0067bf10
// Returns a global pointer to the game manager singleton (EA EARS engine).
// The global is stored at 0x01129804.
GodfatherGameManager* getGameManagerInstance() {
    // Global pointer to the main game manager instance.
    // This is used throughout the codebase to access game state.
    return (GodfatherGameManager*)DAT_01129804; 
}