// FUNC_NAME: GameModeManager::setModeToThree
void GameModeManager::setModeToThree(void) {
    int modeData[3]; // buffer likely for mode parameters or combined effect
    modeData[0] = 3; // set specific mode ID to 3
    this->applyModeData(modeData); // call internal function to apply the mode
}