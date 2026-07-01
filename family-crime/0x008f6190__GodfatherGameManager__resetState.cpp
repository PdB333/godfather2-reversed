// FUNC_NAME: GodfatherGameManager::resetState
// Function at 0x008f6190: Resets game state based on flags.
void GodfatherGameManager::resetState(int stateFlag, bool bFullReset)
{
    // If a state flag is provided, update the singleton manager
    if (stateFlag != 0) {
        // FUN_009823b0: Get singleton instance
        // FUN_009c8eb0: Set state on the singleton (e.g., mission state, scenario)
        GodfatherGameManager::getInstance()->setStateFlag(stateFlag);
    }

    // If not a full reset, perform partial clean-up
    if (!bFullReset) {
        // FUN_0068c590: Stop all sounds / audio
        AudioManager::stopAll(0);
        // FUN_008f5fe0: Clear internal data (e.g., mission progress, temporary state)
        this->clearInternalState();
    }
}