// FUNC_NAME: Player::canPerformActionOnTarget
bool __thiscall Player::canPerformActionOnTarget(Player* this, GameObject* target) {
    char gameMode = getCurrentGameMode(); // FUN_00800be0
    float interactionRange = (this->vtable->getInteractionRange)(); // vtable+0x214
    bool inRange = isWithinInteractionRange(target, interactionRange); // FUN_007f8120

    if (inRange && (this->actionState == 0 || this->actionState == 0x48) &&
        (FUN_00481660() == false || this->teamID != *(int*)((char*)target + 0x1ef4)) &&
        this->isAlive && this->isAware &&
        gameMode != 0x19 && gameMode != 0x1a && gameMode != 0x1b) {
        return true;
    }
    return false;
}