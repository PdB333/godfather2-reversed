// FUNC_NAME: MissionManager::tryStartMission
char MissionManager::tryStartMission(undefined4 param_1, undefined4 param_2)
{
  char result;
  char found;
  int missionId;
  int *missionList;
  int i;
  undefined4 *missionEntry;
  uint missionHash;
  undefined4 local_48;
  undefined1 local_44 [68];
  
  result = '\0';
  found = FUN_0090b1e0(param_1); // Check if mission is valid/available
  if (found != '\0') {
    missionId = FUN_008c74d0(0x637b907); // Get current mission ID from hash
    result = '\0';
    if (missionId != 0) {
      if ((**(int **)(DAT_012233a0 + 4) == 0) || (**(int **)(DAT_012233a0 + 4) == 0x1f30)) {
        local_48 = 0; // No active mission or specific state
      }
      else {
        local_48 = FUN_0043b870(DAT_01130fa0); // Get current mission state
      }
      missionList = (int *)FUN_0043c2c0(*(undefined4 *)(missionId + 0x88)); // Get mission list from mission data (+0x88)
      missionEntry = (undefined4 *)*missionList;
      result = '\0';
      found = '\0';
      if (missionEntry != (undefined4 *)0x0) {
        do {
          result = found;
          missionHash = 0;
          found = (**(code **)(*(int *)*missionEntry + 0x10))(0x369ac561, &missionHash); // Get mission hash from entry
          if ((((found != '\0') && (missionHash != 0)) &&
              (found = FUN_009a9b40(missionHash), found == '\0')) && // Check if mission is not completed
             (((missionId = FUN_007351c0(), missionId != 0 && (i = FUN_0090b0a0(missionId), i == -1)) && // Check if player is not in a mission
              (result = FUN_0090b4e0(param_1, missionId, param_2, 0xffffffff, 0), result != '\0')))) { // Try to start mission
            return result;
          }
          missionEntry = (undefined4 *)missionEntry[1]; // Next entry in linked list
          found = result;
        } while (missionEntry != (undefined4 *)0x0);
        if (result != '\0') {
          return result;
        }
      }
    }
    FUN_0078ec90(0x637b907, param_1); // Fallback mission start
    missionId = FUN_00792900(local_44); // Get mission from queue
    if (missionId != 0) {
      result = FUN_0090b4e0(param_1, missionId, param_2, 0xffffffff, 0); // Start mission with default parameters
    }
    FUN_0078ecf0(); // Cleanup
  }
  return result;
}