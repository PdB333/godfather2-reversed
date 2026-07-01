// FUNC_NAME: OnlineMenuManager::createMapUnavailableScreen
void OnlineMenuManager::createMapUnavailableScreen()
{
    // Allocate screen object (size 0xF0 = 240 bytes)
    OnlineMenuScreen* screen = (OnlineMenuScreen*)allocateMemory(0xF0);
    
    // Initialize screen if allocation succeeded
    if (screen != nullptr) {
        screen = (OnlineMenuScreen*)constructScreen(0);
    }
    
    // Set the localized text for "map unavailable" in online menu
    setScreenText("$mp_online_menu_map_unavailable");
    
    // Set screen type (offset +0x0C) to 3 (likely a specific menu type)
    screen->type = 3;
    
    // Set callback function (offset +0x14) for button press or update
    screen->callback = &screenCallback; // FUN_00982b30
    
    // Finalize and show the screen
    showScreen();
}