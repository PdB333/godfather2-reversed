// FUNC_NAME: Player::resetTargetingState
void __thiscall Player::resetTargetingState(Player *this) {
    // +0x1c4: uint32 aimAssistState?
    *(int *)((int)this + 0x1c4) = 0;
    // +0x1c8: uint32 lockOnTarget?
    *(int *)((int)this + 0x1c8) = 0;
    // +0x1cc: uint32 targetingFlags?
    *(int *)((int)this + 0x1cc) = 0;
    // +0x1d0: uint32 currentTargetAngle?
    *(int *)((int)this + 0x1d0) = 0;
    // +0x1d4: uint32 aimSensitivity?
    *(int *)((int)this + 0x1d4) = 0;
    // +0x1d8: uint32 lockOnTimer?
    *(int *)((int)this + 0x1d8) = 0;
    // +0x1dc: uint32 targetSwitchCooldown?
    *(int *)((int)this + 0x1dc) = 0;
    // +0x1e0: uint32 autoAimStrength?
    *(int *)((int)this + 0x1e0) = 0;
}