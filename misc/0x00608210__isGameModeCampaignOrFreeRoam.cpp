// FUNC_NAME: isGameModeCampaignOrFreeRoam
bool isGameModeCampaignOrFreeRoam()
{
    // Checks global game mode (likely 1 = campaign, 2 = free roam)
    if (g_gameMode != 1 && g_gameMode != 2) {
        return false;
    }
    return true;
}