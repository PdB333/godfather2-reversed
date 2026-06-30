// FUNC_NAME: GameStateManager::setActiveLevel
void __thiscall GameStateManager::setActiveLevel(uint param_2)
{
    // +0x1f3c stores the active level identifier
    this->activeLevelId = param_2;

    // Trigger global state update (0x0071ed30)
    updateGameState();
}