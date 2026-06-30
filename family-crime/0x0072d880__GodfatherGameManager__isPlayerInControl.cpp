// FUNC_NAME: GodfatherGameManager::isPlayerInControl
bool __cdecl GodfatherGameManager::isPlayerInControl() {
    bool isCoreReady; // eax
    bool isPlayerActive; // al

    isCoreReady = Core::isInitialized();
    if (isCoreReady) {
        isPlayerActive = Player::isActive();
        if (isPlayerActive) {
            return true;
        }
    }
    return false;
}