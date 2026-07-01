// FUNC_NAME: GodfatherGameManager::updateWithStateCheck
void __thiscall GodfatherGameManager::updateWithStateCheck() {
    // +0xF2C: m_gameState (0 = playing, 1 = paused)
    if (*(int*)(this + 0xF2C) == 1) {
        setPauseFlag(0);  // disable pause – resume game logic
        gameManagerUpdate();
        return;
    }
    if (*(int*)(this + 0xF2C) == 0) {
        setPauseFlag(1);  // enable pause – freeze game logic
    }
    gameManagerUpdate();
}