// FUNC_NAME: PlayerSM::canPerformAction
bool __thiscall PlayerSM::canPerformAction() {
    // Check if global condition is met (e.g., game not paused, player alive)
    bool globalCondition = checkGlobalCondition(); // FUN_00410eb0
    if (globalCondition && (this->cooldownTimer <= globalCooldownThreshold)) {
        // If global condition is true and cooldown hasn't expired, cannot perform action
        return false;
    }
    // Otherwise, action is allowed
    return true;
}