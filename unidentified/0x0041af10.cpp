// FUN_0041af10: GameManager::InitStage
void GameManager::InitStage(int stageIndex, void* extraData)
{
    // Step 1: Perform base initialization for the given stage
    this->baseInit(stageIndex);
    // Step 2: Set up engine-wide globals (singleton)
    GlobalEngine::setup();
    // Step 3: Complete initialization with additional context
    this->finalInit(stageIndex, extraData);
}