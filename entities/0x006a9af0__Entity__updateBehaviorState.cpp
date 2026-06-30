// FUNC_NAME: Entity::updateBehaviorState
char __fastcall Entity::updateBehaviorState(Entity* entity) // 0x006a9af0
{
    char isSystemActive = isSystemEnabled(); // FUN_00474730 - global system active check
    if (isSystemActive) {
        // Check sub-behavior at offset 0x140 (likely a behavior state machine)
        char isBehaviorReady = FUN_006a8b50((int)entity + 0x140);
        if (isBehaviorReady) {
            // Activate component at offset 0xe8 (e.g., DamageComponent)
            FUN_005e2c20(*(int*)((int)entity + 0xe8));
        } else {
            // Set component state to 4 (e.g., idle/disabled)
            FUN_005e2c60(*(int*)((int)entity + 0xe8), 4);
        }
    }
    return isSystemActive;
}