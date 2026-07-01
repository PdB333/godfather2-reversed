// FUNC_NAME: Entity::setActive
bool Entity::setActive(undefined4 param_1, undefined4 param_2, char param_3)
{
    int entityPtr;
    
    entityPtr = Entity::getEntityByHandle(param_1); // FUN_00893470 - resolve handle to entity pointer
    if (entityPtr != 0) {
        Entity::setActiveInternal(entityPtr, param_2, param_3 != '\0', 0); // FUN_00894d00
    }
    return entityPtr != 0;
}