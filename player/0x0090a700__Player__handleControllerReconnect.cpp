// FUNC_NAME: Player::handleControllerReconnect
void Player::handleControllerReconnect() {
    // Reset controller state for slot 0
    resetControllerState(0);  // FUN_00791e00(0)

    // Get the local player controller data
    int* playerController = getLocalPlayerController();  // FUN_00791300()

    if (playerController) {
        // Get the game manager instance
        GameManager* gameMgr = getGameManager(DAT_01131040);  // FUN_0043b870(DAT_01131040)
        if (gameMgr) {
            // Check if game state pointer is valid and not equal to 0x48 (some specific state)
            void* gameState = *(void**)((int)gameMgr + 0x1c);
            if (gameState && gameState != (void*)0x48) {
                // Mark that we are about to reconnect a controller
                setPendingReconnect(1);  // FUN_009b1970(1)

                char isControllerConnected = isControllerCurrentlyConnected();  // FUN_007f7c60()
                if (!isControllerConnected) {
                    // Check a specific flag in the controller data at offset 0x8E8 (bit 15 of int array element 0x23a)
                    if (!((playerController[0x23a] >> 0xf) & 1)) {
                        return;  // No reconnection pending, exit
                    }
                } else {
                    // Get input manager instance
                    InputManager* inputMgr = getInputManager();  // FUN_007ff880()
                    if (inputMgr) {
                        // Prepare locals for controller slot info
                        int slotIndex = 0;
                        int unused = 0;

                        // Virtual call: InputManager::getControllerSlotInfo(this, &slotIndex)  (vtable+0x204)
                        (*(code**)(*(int*)inputMgr + 0x204))(inputMgr, &slotIndex);

                        // Virtual call: Player::reinitializeController(this)  (vtable+0x1b4)
                        (*(code**)(*(int*)playerController + 0x1b4))();

                        // Reset controller data at offset 0x3c (playerController+0xf as int* means +0x3c bytes)
                        resetControllerData(playerController + 0xf);  // FUN_004088c0(playerController+0xf)

                        return;
                    }
                }

                // If we reach here, reset the controller data even if not reconnected
                resetControllerData(playerController + 0xf);  // FUN_004088c0(playerController+0xf)
            }
        }
    }
}