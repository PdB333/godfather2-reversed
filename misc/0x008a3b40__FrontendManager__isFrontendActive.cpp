// FUNC_NAME: FrontendManager::isFrontendActive
bool FrontendManager::isFrontendActive(void)
{
    // DAT_0112980c: pointer to global ApplicationStateManager
    // +0x04: current state ID
    ApplicationStateManager* stateMgr = DAT_0112980c;
    
    // Get the state ID for "FrontendMainLoop"
    uint frontendStateId = StateManager::getStateByName("FrontendMainLoop");
    uint currentStateId = StateManager::getCurrentStateId(frontendStateId);
    
    // If the current state doesn't match the stored state ID, not in frontend
    if (currentStateId != stateMgr->currentStateId) {
        return false;
    }
    
    // DAT_01129930: pointer to global FrontendManager singleton
    FrontendManager* frontend = DAT_01129930;
    if (frontend == nullptr) {
        return false;
    }
    
    // +0x48: active flag (bool)
    // +0x49: transition flags (bits 0x0A = fade in progress)
    if (frontend->active && (frontend->transitionFlags & 0x0A) == 0) {
        return true;
    }
    
    return false;
}