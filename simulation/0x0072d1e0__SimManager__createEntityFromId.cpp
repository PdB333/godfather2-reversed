// FUNC_NAME: SimManager::createEntityFromId

int __thiscall SimManager::createEntityFromId(uint entityId)
{
    // Call global factory/registry function to get or create an entity by its ID.
    // Returns a pointer to the entity or zero if creation fails.
    int* entity = (int*)createOrGetEntityById(entityId);

    if (entity != nullptr)
    {
        // Call virtual method at vtable offset 0x24c (likely onEntityCreated or addEntity).
        // This method is responsible for attaching the entity to the manager's internal lists,
        // performing post-creation setup, etc.
        (this->*(void(__thiscall*)(int*)))(*(int**)(this) + 0x24c / 4)(entity);
    }

    // Return the entity pointer (or zero if creation failed).
    return (int)entity;
}