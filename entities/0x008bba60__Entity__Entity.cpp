//FUNC_NAME: Entity::Entity
// Address: 0x008bba60
// Role: Constructor for Entity class. Calls base constructor and optionally performs additional initialization based on flag.

void* __thiscall Entity::Entity(void* this, byte initFlags)
{
    // Call base class constructor (likely EARSObject or similar)
    BaseEntity::BaseEntity(this);
    
    // If the lowest bit of initFlags is set, call initialization routine with size 0x290
    if (initFlags & 1) {
        Entity::Initialize(this, 0x290); // 0x290 = sizeof(Entity)
    }
    
    return this;
}