// FUNC_NAME: MultiplayerScenarioManager::showTeamWinMessage
void MultiplayerScenarioManager::showTeamWinMessage(char blueTeamWon)
{
  if (blueTeamWon != '\0') {
    // Blue team won - display the blue team victory message
    FUN_00983120("$mp_online_blue_team_win_uppercase",0,0);
    return;
  }
  // Red team won - display the red team victory message
  FUN_00983120("$mp_online_red_team_win_uppercase",0,0);
  return;
}