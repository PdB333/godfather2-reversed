// FUNC_NAME: Player::checkMissionTrigger
void Player::checkMissionTrigger(Player* thisPlayer, int param_2) {
    // param_2 is unused except for null check
    if (thisPlayer == nullptr || param_2 == 0) {
        return;
    }

    // Global pointer at DAT_012233a0 + 4 points to a sub-object of a larger structure
    int* subObjectPtr = *(int**)(DAT_012233a0 + 4);
    if (subObjectPtr == nullptr) {
        return;
    }

    // Get parent structure by subtracting offset 0x38 (common pattern for member pointer to parent)
    int* parentPtr = subObjectPtr - 0x1f30; // Actually subObjectPtr - 0x1f30, but likely a different offset
    if (parentPtr == nullptr) {
        return;
    }

    // Compare player's mission state (offset +0x1ef8) with parent's mission ID (offset +0x38)
    if (*(int*)(thisPlayer + 0x1ef8) == *(int*)(parentPtr + 0x38)) {
        // Trigger mission event
        MissionEvent::trigger(parentPtr);
        // Prepare dialog with global text buffer
        DialogManager::prepare(&DAT_0112ebec, local_c, 0);
        // Show the dialog
        DialogManager::show();
    } else if (*(char*)(thisPlayer + 0x311c) != '\0') {
        // Player is in a special state (e.g., paused or cutscene)
        Player::handleSpecialState();
    }
}