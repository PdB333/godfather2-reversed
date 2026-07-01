// FUNC_NAME: MultiplayerStrings::getLocalizedStringForError
const char* MultiplayerStrings::getLocalizedStringForError(int errorCode)
{
  // Returns a localized string key for various multiplayer error codes
  switch(errorCode) {
  case 1:
    return FUN_00963050("$mp_teams_balanced", &LAB_0096a190);
  case 2:
    return FUN_00963050("$mp_online_need_more_players", &LAB_0096a190);
  case 3:
    return FUN_00963050("$mp_online_not_enough_fs", &LAB_0096a190);  // Not enough free slots
  case 4:
    return FUN_00963050("$mp_online_not_enough_sc", &LAB_0096a190);  // Not enough SC
  case 5:
    return FUN_00963050("$mp_online_not_enough_dm", &LAB_0096a190);  // Not enough DM
  case 6:
    return FUN_00963050("$mp_one_don_per_team", &LAB_0096a190);      // One Don per team
  case 7:
    return FUN_00963050("$mp_don_min_four_players", &LAB_0096a190);  // Don mode needs 4+ players
  }
  return (const char*)0x0;
}