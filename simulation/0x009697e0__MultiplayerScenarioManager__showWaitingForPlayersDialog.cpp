// FUNC_NAME: MultiplayerScenarioManager::showWaitingForPlayersDialog
void MultiplayerScenarioManager::showWaitingForPlayersDialog(void)
{
  char *formattedString;
  char *local_10;
  int local_c;
  int local_8;
  void *local_4;
  
  local_10 = (char *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (void *)0x0;
  FUN_004d4ad0(&local_10,"{%s}\\n\\n{%s}","$mp_online_waiting_for_returning_players",
               "$mp_press_to_cancel");
  formattedString = local_10;
  if (local_10 == (char *)0x0) {
    formattedString = &DAT_0120546e;
  }
  FUN_00983120(formattedString,&LAB_00964190,0);
  if (local_10 != (char *)0x0) {
    (*local_4)(local_10);
  }
  return;
}