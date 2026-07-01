//FUNC_NAME: GameManager::canPerformAction
bool GameManager::canPerformAction(int entityId, int actionType, int extraData) {
    if (actionType != 10) {
        return checkActionPermission(this, entityId, actionType, extraData);
    }
    if (!isGamePaused()) {
        if (getGameState() != 2) {
            return false;
        }
    }
    return true;
}