// FUNC_NAME: Entity::setContainer
// Address: 0x00591f50
// Role: Sets the container/parent pointer in the given object, with type validation via jump table.

int __thiscall Entity::setContainer(Entity* this, Entity* container)
{
    char typeId = **(char**)(this + 8);  // +0x8: type identifier byte
    if (typeId < 10) {
        // Call type-specific validation function from global table
        bool validationResult = ((bool (*)(Entity*))(&PTR_FUN_0103af90)[typeId])(container);
        if (validationResult) {
            return 0; // Validation failed
        }
    }
    // Set container's back-pointer to this entity
    *(int*)(container + 0xC) = (int)this; // +0xC: container's child pointer
    return 1; // Success
}