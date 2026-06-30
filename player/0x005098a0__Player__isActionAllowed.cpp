// FUNC_NAME: Player::isActionAllowed
__thiscall bool FUN_005098a0(void)
{
    float fVar1;
    
    // +0x24: PlayerMovementState*, +0xcc: some timer or flag (e.g., actionCooldown)
    fVar1 = *(float *)(*(int *)(in_EAX + 0x24) + 0xcc);
    // If cooldown is active (positive and within threshold DAT_00e2e714)
    if ((0.0f < fVar1) && (fVar1 <= DAT_00e2e714)) {
        return false;
    }
    return true;
}