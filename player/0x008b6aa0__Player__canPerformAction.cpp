// FUNC_NAME: Player::canPerformAction
bool __thiscall Player::canPerformAction(Player* thisPlayer) {
    // Check global condition (maybe game paused or cinematic)
    bool isGlobalConditionMet = FUN_004709e0();
    if (isGlobalConditionMet) {
        return false;
    }

    // +0x194: likely pointer to current interaction target (non-null means something)
    // +0x290: flags field; bit 0x20 = kFlag_Active, bit 0x100 = kFlag_Disabled
    uint flags = *(uint*)((char*)thisPlayer + 0x290);
    int* currentTarget = *(int**)((char*)thisPlayer + 0x194);

    return (currentTarget != nullptr) &&
           ((flags & 0x20) != 0) &&
           ((flags & 0x100) == 0);
}