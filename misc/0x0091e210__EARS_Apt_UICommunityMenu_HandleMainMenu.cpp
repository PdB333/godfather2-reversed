// Xbox PDB: EARS_Apt_UICommunityMenu_HandleMainMenu
// FUNC_NAME: UIMultiplayerLeaderboard::updateState
void __fastcall UIMultiplayerLeaderboard::updateState(int this)
{
  char *titleKey;

  // State 0: Show default data (likely recent matches or player stats)
  if (*(int *)(this + 0xb4) == 0) {
    clearScreenBuffer(&gScreenBuffer, 0);
    displayText("ShowData", 0, &gUIManager, 0);
    *(int *)(this + 0xdc) = 0;             // +0xdc: some counter/flag
    *(int *)(this + 0xb8) = 1;             // +0xb8: sub-state indicator
    *(int *)(this + 0xc0) = 0;             // +0xc0: selection or page
    *(int *)(this + 0xb4) = 0;             // +0xb4: state remains 0?
    hideLoadingIndicator(0);               // 0: no animation
    showDataMenu();                        // transition to data screen
  }
  // State 1: Show leaderboards (global or friends)
  else if (*(int *)(this + 0xb4) == 1) {
    clearScreenBuffer(&gScreenBuffer, 0);
    displayText("ShowLeaderboards", 0, &gUIManager, 0);
    titleKey = "$mp_online_leaderboards_friend_leaders";
    if (gIsFriendLeaderboards == '\0') {
      titleKey = "$mp_online_leaderboards_global_leaders";
    }
    displayText("ChangeLeaderTitle", 0, &gUIManager, 1, titleKey);
    *(int *)(this + 0xdc) = 0;             // reset counter
    *(int *)(this + 0xb8) = 10;            // sub-state for leaderboard
    *(int *)(this + 0xc0) = 0;             // default selection
    *(int *)(this + 0xb4) = 0;             // reset state to 0
    hideLoadingIndicator(0);
    showLeaderboardMenu();
    setLeaderboardCallback(&gLeaderboardHandler);
    requestLeaderboardData(1, 0);          // request with page/offset
  }

  // Always push history state for back navigation
  displayText("PushHistory", 0, &gUIManager, 0);
  pushHistoryState();                      // record current screen in history
}