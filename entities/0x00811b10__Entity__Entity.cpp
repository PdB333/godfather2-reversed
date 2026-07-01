// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(Entity* this)
{
    // Set vtable pointers
    this->vtable = &PTR_FUN_00d72f34;                 // +0x00: main vtable
    this->interfaceVtable1 = &PTR_LAB_00d72f24;       // +0x3C: interface vtable (e.g., IEntity)
    this->interfaceVtable2 = &PTR_LAB_00d72f20;       // +0x48: second interface vtable

    // Initialize base subobjects (probably reference counting)
    FUN_004086d0(&g_SomeGlobal1);                     // likely base class constructor (e.g., RefCount)
    FUN_004086d0(&g_SomeGlobal2);                     // another base subobject
    FUN_00408310(&this->subobjectAt0xA0);             // +0xA0: subobject (e.g., Transform, Physics)

    // Check if this entity is already registered in the global entity list
    uint index = 0;
    if (g_entityCount != 0)
    {
        while (g_entityList[index] != this)
        {
            index++;
            if (g_entityCount <= index)
            {
                // Not found – just add to list
                FUN_0046c640();                       // addToEntityList(this)
                return;
            }
        }
        // Duplicate found – remove old entry first
        FUN_00811340(index);                          // removeEntityFromList(index)
    }
    // Register this entity (or re-register after removal)
    FUN_0046c640();                                   // addToEntityList(this)
}