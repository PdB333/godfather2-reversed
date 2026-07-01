// FUNC_NAME: Player::handleMissionExitEvent
void Player::handleMissionExitEvent(void* thisPtr, int missionId, char exitToFreeroam)
{
    if (missionId != 0) {
        FUN_009823b0(); // Likely: AudioManager::clearMissionSoundState()
        FUN_009c8eb0(missionId); // Likely: MissionManager::stopMission(int missionId)
    }
    if (exitToFreeroam == '\0') {
        FUN_0068c590(0); // Likely: GameStateManager::setCurrentState(GameState_FreeRoam)
        FUN_008f44b0(thisPtr); // Likely: Player::resetToFreeroamState()
    }
    return;
}