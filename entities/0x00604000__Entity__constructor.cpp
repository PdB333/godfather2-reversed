// FUNC_NAME: Entity::constructor
void Entity::constructor(Entity* this, undefined4 param2, undefined4 param3)
{
    // Call base class constructor (likely EARSObject or similar)
    FUN_00603d30(this, param2, param3);
    
    // Initialize entity-specific data
    FUN_00604060(param2);
}