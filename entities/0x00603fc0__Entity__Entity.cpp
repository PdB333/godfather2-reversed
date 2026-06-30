// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(int arg1, int arg2, int arg3, int arg4) {
    // Call base class constructor (FUN_00603da0)
    BaseEntity::BaseEntity(arg1, arg2, arg3, arg4);
    // Initialize sub-object at offset 0x74 (FUN_004d4300)
    initializeSubObject(this + 0x74);
    return;
}