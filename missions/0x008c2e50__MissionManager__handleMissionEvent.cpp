// FUNC_NAME: MissionManager::handleMissionEvent
void __thiscall MissionManager::handleMissionEvent(int missionId, int eventData)
{
  int missionData;
  char flag;
  int difficulty;
  int actionType;
  int rewardParam;

  missionData = missionId;
  validateEntity(missionId); // FUN_006b3c40
  difficulty = getGameDifficulty(); // FUN_00791750
  if (difficulty < 3) {
    setGameState(0); // FUN_00790110
    flag = isPlayerInMission(); // FUN_00791230
    if (flag != '\0') {
      startMission(missionId); // FUN_00792d80
      return;
    }
  }
  else {
    missionData = findMission(missionId); // FUN_008c12a0
    if (missionData != 0) {
      if ((*(byte *)(missionId + 0x5f) & 1) == 0) {
        if (*(int *)(this + 0x54) == *(int *)(eventData + 0x40)) {
          rewardParam = *(undefined4 *)(this + 0x1e0);
          actionType = 3;
          if (*(int *)(this + 0x54) == 0x637b907) {
            actionType = 1;
            rewardParam = 0;
          }
          executeMissionAction(missionData, actionType, *(undefined4 *)(eventData + 0x38), rewardParam); // FUN_008bd860
          markMissionComplete(missionId, 1); // FUN_006b4730
          return;
        }
        handleMissionFailure(eventData, missionData); // FUN_008bda10
      }
      else if (*(int *)(missionData + 4) != 7) {
        showMessage(0); // FUN_008c80d0
        playSound(1, 0); // FUN_008c8a20
        return;
      }
    }
  }
  return;
}