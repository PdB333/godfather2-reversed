// FUNC_NAME: LeaderboardState::toggleLeaderboardType
void __fastcall LeaderboardState::toggleLeaderboardType(int thisPtr)
{
  char *leaderboardTitle;
  bool isFriendLeaderboard;
  
  isFriendLeaderboard = *(char *)(thisPtr + 0x94) == '\0';  // +0x94 flag: 0=global, 1=friend
  *(bool *)(thisPtr + 0x94) = isFriendLeaderboard;
  
  leaderboardTitle = "$mp_online_leaderboards_friend_leaders";
  if (!isFriendLeaderboard) {
    leaderboardTitle = "$mp_online_leaderboards_global_leaders";
  }
  
  FUN_005a04a0("ChangeLeaderTitle", 0, &DAT_00d8510c, 1, leaderboardTitle);
  return;
}