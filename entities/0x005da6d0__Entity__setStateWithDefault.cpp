// FUNC_NAME: Entity::setStateWithDefault
void __fastcall Entity::setStateWithDefault(void* unusedThis, Entity* entity, int state, int unusedParam)
{
    // param_1 (this) is unused; likely a static method or an ignored this pointer.
    // Calls the actual implementation FUN_005dab00 with a default third parameter of 0.
    // This wrapper allows callers to omit the third argument (e.g., a boolean flag).
    Entity::setStateImpl(entity, state, 0);
}