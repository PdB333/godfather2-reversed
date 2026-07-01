// FUNC_NAME: GodfatherGameManager::toggleFeatureState
// Address: 0x00861ba0
// Role: Toggles a game feature based on internal flag at +0xf2c.
// Calls setGlobalFeature(bool) with opposite of current flag, then updateAfterToggle().

void GodfatherGameManager::toggleFeatureState() {
    // Check the current state of the feature flag (offset +0xf2c)
    if (this->m_featureFlag == 1) {
        // If currently enabled, disable it
        setGlobalFeature(false);  // FUN_0087bc20(0)
        updateAfterToggle();      // FUN_008611a0
        return;
    }
    if (this->m_featureFlag == 0) {
        // If currently disabled, enable it
        setGlobalFeature(true);   // FUN_0087bc20(1)
    }
    // Note: When m_featureFlag is 0, the function falls through to updateAfterToggle()
    updateAfterToggle();          // FUN_008611a0
}