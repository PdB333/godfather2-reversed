// FUNC_NAME: Player::resetPendingActions
bool __thiscall Player::resetPendingActions(void)
{
    // Check if there are pending actions stored at offset 0x2c0 and 0x2c4
    if (*(int *)(this + 0x2c0) != -1 || *(int *)(this + 0x2c4) != -1) {
        // Call a method on the game object (offset 0x14) via vtable entry 0x80
        // This likely checks if the player is in a state that allows resetting
        bool (*isActionAllowed)(void*) = *(bool (**)(void*))(*(int*)0x01223510 + 0x80);
        if (!isActionApproved(*(void**)(this + 0x14))) {
            return false;
        }
        // Reset pending action indices to -1 (invalid/cleared)
        *(int *)(this + 0x2c0) = -1;  // pending action 1
        *(int *)(this + 0x2c4) = -1;  // pending action 2
    }
    return true;
}