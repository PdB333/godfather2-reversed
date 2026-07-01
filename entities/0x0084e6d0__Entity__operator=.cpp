// FUNC_NAME: Entity::operator=
// Function at 0x0084e6d0 calls an internal copy method at 0x0084e670 and returns this pointer.
// This pattern is typical of a copy assignment operator that delegates to a helper function.

Entity* __thiscall Entity::operator=(Entity* this, const Entity& other)
{
    // Internal copy helper that likely duplicates the state from 'other'
    FUN_0084e670(&other);
    return this;
}