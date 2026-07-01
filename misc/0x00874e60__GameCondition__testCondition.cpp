// FUNC_NAME: GameCondition::testCondition
// Address: 0x00874e60
// Role: A thin wrapper that delegates to the actual condition evaluation function (FUN_00874ce0).
// The inner function likely performs a specific game logic check (e.g., collision, AI state, or interaction).
bool __thiscall GameCondition::testCondition(int entityId, int conditionType, void* additionalData)
{
    return FUN_00874ce0(entityId, conditionType, additionalData) != 0;
}