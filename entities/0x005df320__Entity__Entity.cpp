// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity *this, byte allocatedFlag)
{
    // Set vtable pointer for Entity class (0x00e3f2d8)
    this->vtable = &GUID_vtable_00e3f2d8;
    // Call base class constructor (likely SimObject or EARSObject)
    Entity::initializeBase(this);
    // If the object was heap-allocated (param_2 & 1), deallocate it (e.g., on construction failure)
    if ((allocatedFlag & 1) != 0) {
        operatorDelete(this);
    }
}