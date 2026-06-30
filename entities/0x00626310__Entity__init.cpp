// FUNC_NAME: Entity::init
void Entity::init(uint param_1)
{
    baseInit(); // FUN_00638520 - base class initialization
    memberInit(param_1); // FUN_006366f0 - member specific to this entity
}