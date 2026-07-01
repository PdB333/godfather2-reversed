// FUNC_NAME: Entity::Entity
Entity* __fastcall Entity::Entity(Entity* this)
{
    // Set vtable to base class (EARSObject) vtable (originally PTR_LAB_00d74620)
    this->vtable = (void**)&g_EARSObjectVTable;
    // Call base class constructor (originally FUN_00598d50)
    EARSObject::EARSObject((EARSObject*)this);
    // Set second vtable pointer for second base class (originally PTR_LAB_00d74950)
    this->secondVtable = (void**)&g_NetReflectableVTable;
    // Override vtable with Entity's own vtable (originally PTR_FUN_00d7494c)
    this->vtable = (void**)&g_EntityVTable;
    return this;
}