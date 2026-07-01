//FUNC_NAME: Entity::Entity
// Address: 0x0084b190
// Role: Constructor for Entity class, calls base class initialization and optionally additional initialization based on flag

undefined4 __thiscall Entity::Entity(Entity* this, byte initFlag)
{
    // Call base class initialization (EARSObject::init at 0x0084a340)
    EARSObject::init(this);
    
    // If the lowest bit of initFlag is set, perform additional initialization
    if ((initFlag & 1) != 0) {
        Entity::init(this); // Additional initialization at 0x009c8eb0
    }
    
    return (undefined4)this;
}