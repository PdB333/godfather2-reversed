// FUNC_NAME: GodfatherGameManager::updateMissionCompletionTracking
void GodfatherGameManager::updateMissionCompletionTracking(void)

{
  int missionId;
  int currentMissionId;
  int missionIndex;
  undefined4 *iterator;
  int iterResult;
  int iterEnd;
  
  missionId = DAT_00e54400; // Current mission ID being tracked
  if (**(int **)(DAT_012233a0 + 4) == 0) { // Check if player object exists
    currentMissionId = 0;
  }
  else {
    currentMissionId = **(int **)(DAT_012233a0 + 4) + -0x1f30; // Player object offset -0x1f30
  }
  if ((*(int *)(DAT_0112ebb4 + 0x16c) != 0) && (currentMissionId != 0)) { // Check mission manager + player valid
    currentMissionId = *(int *)(currentMissionId + 0x1ef8); // Player's current mission ID (+0x1ef8)
    FUN_004bab20(&iterator,*(int *)(DAT_0112ebb4 + 0x16c),currentMissionId); // Get mission iterator
    while ((iterResult != 0 || (iterEnd != 0))) { // Iterate through mission data
      missionIndex = (*(code *)*iterator)(); // Get mission index
      if ((*(int *)(missionIndex + 8) == missionId) && // Check mission ID matches
         ((*(int *)(missionIndex + 0x10) == currentMissionId && (*(uint *)(missionIndex + 4) < 0xc)))) { // Check mission state < 12 (completed)
        (&DAT_00e56618)[*(uint *)(missionIndex + 4) * 0x18] = 1; // Mark mission as completed in tracking array
      }
      (*(code *)iterator[2])(); // Advance iterator
    }
  }
  DAT_01130504 = 1; // Set flag indicating mission completion tracking updated
  return;
}