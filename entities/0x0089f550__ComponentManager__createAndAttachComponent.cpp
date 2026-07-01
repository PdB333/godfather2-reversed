// FUNC_NAME: ComponentManager::createAndAttachComponent
void __fastcall ComponentManager::createAndAttachComponent(void* parent) {
    // Get the global game manager singleton
    GameManager* gameMgr = getGameManager();
    if (gameMgr != nullptr) {
        // Compute the player object pointer from the game manager's internal offset
        // The game manager stores a pointer to the player at offset 0x58? Actually,
        // we subtract 0x58 to get the containing object (common pattern for member pointers)
        Player* player = reinterpret_cast<Player*>(reinterpret_cast<char*>(gameMgr) - 0x58);
        if (player != nullptr) {
            // Check if the player is in a controllable state (e.g., alive, not in menu)
            if (isPlayerControllable()) {
                // Allocate a new component of size 0x38 (56 bytes)
                Component* newComp = static_cast<Component*>(allocateMemory(0x38));
                if (newComp != nullptr) {
                    // Construct the component with the parent pointer (passed in ecx)
                    newComp = constructComponent(newComp, parent);
                }
                // Register the component with the system (e.g., attach to player)
                registerComponent(newComp);
            }
            // Call a method on the player object (e.g., update component list)
            updatePlayerComponent(player);
        }
    }
}