// FUNC_NAME: Entity::conditionalUpdate
void __thiscall Entity::conditionalUpdate(Entity* thisPtr) {
    bool isActive = FUN_009ca6b0(thisPtr); // Checks if entity is active (non-zero = active)
    if (!isActive) {
        FUN_00646e60(thisPtr); // Performs update when active flag is false
    }
}