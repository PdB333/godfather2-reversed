// FUNC_NAME: GodfatherGameManager::update
// Address: 0x008c6db0
// Role: Main update tick for GodfatherGameManager, checks if manager is ready and processing state, then finalizes.

void GodfatherGameManager::update(int this_ /* actually this pointer */)
{
    // Check if the manager object itself is valid (non-null this)
    if (this_ != 0) {
        // Check if the game or manager is in a valid state (e.g., initialized, not paused)
        int stateReady = IsGameActive(); // equivalent to FUN_007915b0, returns non-zero if active
        if (stateReady != 0) {
            // Perform gameplay logic for this tick; param_1 is the this pointer
            int processed = ProcessTickState(this_); // FUN_008c12a0
            if (processed != 0) {
                // Finalize the tick (e.g., update UI, physics sync, network flush)
                FinalizeTick(); // FUN_008c8f60
            }
        }
    }
}

// Note: The callees are assumed to be part of GodfatherGameManager or related global functions.
// IsGameActive() takes no parameters and returns an int (bool).
// ProcessTickState(int obj) returns non-zero if the state was successfully advanced.
// FinalizeTick() is a void function with no parameters.