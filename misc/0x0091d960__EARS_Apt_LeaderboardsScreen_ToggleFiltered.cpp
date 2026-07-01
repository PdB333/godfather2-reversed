// Xbox PDB: EARS_Apt_LeaderboardsScreen_ToggleFiltered
// FUNC_NAME: LeaderboardMenu::showLeaderboards
void __fastcall LeaderboardMenu::showLeaderboards(int *this)
{
  char *titleStr;
  
  // If currently showing leaderboards, reset state and hide menus
  if (this[0x2e] != 0) {
    this[0x37] = 0; // some state flag
    this[0x2e] = 0; // leaderboard state
    this[0x30] = 0; // some counter
    this[0x2d] = 0; // another state flag
    FUN_00986240(0); // clear something
    FUN_005a04a0("ShowMenu",0,&DAT_00d8510c,0); // hide menu
    FUN_005a04a0("HighlightSelected",0,&DAT_00d8510c,0); // clear highlight
  }
  
  // Set platform type (e.g., Xbox 360)
  FUN_005a04a0("SetPlatform",0,&DAT_00d8510c,1,&DAT_00d85114);
  
  // Initialize leaderboard display
  FUN_00916ec0(); // setup leaderboard UI
  (**(code **)(*this + 0xc))(); // virtual function call (likely update)
  FUN_00916bc0("$mp_fetching_stats"); // show "fetching stats" message
  FUN_00907c70(&LAB_0091a3c0); // start async fetch
  this[0x2d] = 1; // set fetching flag
  
  // Show leaderboard UI
  FUN_005a04a0("ShowLeaderboards",0,&DAT_00d8510c,0);
  
  // Set title based on friend/global leaderboard toggle
  titleStr = "$mp_online_leaderboards_friend_leaders";
  if (DAT_00e54d1c == '\0') {
    titleStr = "$mp_online_leaderboards_global_leaders";
  }
  FUN_005a04a0("ChangeLeaderTitle",0,&DAT_00d8510c,1,titleStr);
  
  // Reset state and start fetching
  this[0x37] = 0;
  this[0x2e] = 10; // leaderboard state = fetching
  this[0x30] = 0;
  this[0x2d] = 0;
  FUN_00986240(0); // clear data
  FUN_009171f0(); // refresh display
  FUN_0091cd80(1,0); // enable input
}