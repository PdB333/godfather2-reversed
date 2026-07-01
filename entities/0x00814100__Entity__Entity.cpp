// FUNC_NAME: Entity::Entity
Entity::Entity(byte initFlags)
{
    this->initializeBase(); // FUN_00814090
    if (initFlags & 1)
    {
        this->onCreateWithFlag(); // FUN_009c8eb0
    }
    // return this; (implicit constructor behavior)
}