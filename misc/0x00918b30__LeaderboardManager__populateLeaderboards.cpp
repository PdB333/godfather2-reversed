// FUNC_NAME: LeaderboardManager::populateLeaderboards
void LeaderboardManager::populateLeaderboards(int param_1, int param_2, int param_3, int param_4)
{
    int leaderboardId = FUN_00907680(param_1);  // Convert param_1 to leaderboard ID
    FUN_00916bc0("$mp_populating_leaderboards");  // Show loading message
    
    if (DAT_00e54d1c != '\0') {  // If leaderboard data is already cached
        FUN_00907cc0(DAT_00e54d04, DAT_00e54d08, param_2, param_3, param_4);  // Use cached data directly
        return;
    }
    
    FUN_00907c90(leaderboardId, DAT_00e54d24, DAT_00e54d20, param_2, param_3, param_4);  // Fetch from backend
    return;
}