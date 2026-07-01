// FUNC_NAME: DifficultyManager::getDifficultyLevelForMission
int getDifficultyLevelForMission(int missionIndex)
{
  switch(missionIndex) {
  case 5:
  case 10:
  case 15:
  case 18:
  case 23:
    return 2; // Medium difficulty
  case 6:
  case 11:
  case 16:
  case 19:
  case 24:
    return 3; // Hard difficulty
  case 7:
  case 12:
  case 17:
  case 20:
  case 25:
    return 4; // Very hard difficulty
  default:
    return 0; // Easy or invalid mission
  }
}