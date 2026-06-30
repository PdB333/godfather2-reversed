// FUNC_NAME: conditionalUpdate
// Function address: 0x0071e820
// Role: Conditionally executes a game update function based on a flag check.
// Calls isGameActive() to determine whether to run updateGameLogic().

void conditionalUpdate(void)
{
    char activeFlag;
    
    activeFlag = isGameActive();        // Returns non-zero if game is active/not paused
    if (activeFlag == '\0') {
        updateGameLogic();              // Run the core update logic
        return;
    }
    return;
}