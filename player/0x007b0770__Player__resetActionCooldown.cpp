// FUNC_NAME: Player::resetActionCooldown
bool __fastcall Player::resetActionCooldown(int this) {
    char checkResult = FUN_00410eb0(); // likely checks if game is active or player is alive
    if (checkResult != 0 && DAT_00d6bfe0 < *(float *)(this + 0x1e0)) {
        *(int *)(this + 0x1c4) = 0;   // +0x1c4: actionTimer1
        *(int *)(this + 0x1c8) = 0;   // +0x1c8: actionTimer2
        *(int *)(this + 0x1d8) = 0;   // +0x1d8: actionTimer3
        *(int *)(this + 0x1dc) = 0;   // +0x1dc: actionTimer4
        *(float *)(this + 0x1e0) = 0.0f; // +0x1e0: cooldownTimer (compared against global)
        *(int *)(this + 0x1cc) = 0;   // +0x1cc: stateFlag1
        *(int *)(this + 0x1d0) = 0;   // +0x1d0: stateFlag2
        *(int *)(this + 0x1d4) = 0;   // +0x1d4: stateFlag3
        *(int *)(this + 0x1e8) = _DAT_00d5c458; // +0x1e8: defaultActionState
        return true;
    }
    return false;
}