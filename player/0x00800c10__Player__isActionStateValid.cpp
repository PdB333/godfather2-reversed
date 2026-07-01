//FUNC_NAME: Player::isActionStateValid
bool __thiscall Player::isActionStateValid(Player* this)
{
    // +0x74c: pointer to current state machine (e.g., PlayerSM, CombatState)
    int* stateMachine = *(int**)((char*)this + 0x74c);
    bool result = false;

    // Check: stateMachine is valid (not null and not sentinel 0x48)
    // 0x48 likely represents an invalid/uninitialized state pointer
    if (stateMachine != nullptr && stateMachine != (int*)0x48 &&
        // +0x8e0: flags field; check bit 10 (e.g., "isInCombat" or "isActive")
        (*(uint32_t*)((char*)this + 0x8e0) & (1 << 10)) != 0 &&
        // +0x165 of stateMachine: state sub-type (0 or 1 indicates valid state)
        (*(char*)((char*)stateMachine + 0x165) == 0 ||
         *(char*)((char*)stateMachine + 0x165) == 1))
    {
        result = true;
    }
    return result;
}