// FUNC_NAME: HudManager::displayIntelReward
// Function address: 0x00981ad0
// Displays the intel reward icon on the HUD and marks the player's intel as acquired.

void __thiscall HudManager::displayIntelReward(HudManager* this) {
    // Show reward icon: hash (string resource), icon name, screen position, context param, flags
    DisplayRewardIcon(0x4746eca8, "icon_reward_intel", &someLabel, *(int*)(this + 0x54), 0);

    // Retrieve the game manager singleton (e.g., GodfatherGameManager)
    GodfatherGameManager* gameMgr = GetGameManager();
    if (gameMgr) {
        // Get the local player
        Player* player = gameMgr->getPlayer();
        if (player) {
            // Set bit 7 (0x80) on player's flags at offset 0x84 – likely "intel reward shown"
            player->flags |= 0x80;
        }
    }
}