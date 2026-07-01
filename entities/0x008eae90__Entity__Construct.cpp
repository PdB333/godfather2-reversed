// FUNC_NAME: Entity::Construct
Entity* __thiscall Entity::Construct()
{
    // Calls internal initialization routine (likely sets up default state)
    ConstructInternal();
    return this;
}