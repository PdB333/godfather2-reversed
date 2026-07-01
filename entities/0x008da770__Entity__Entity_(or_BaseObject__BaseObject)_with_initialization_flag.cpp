// FUNC_NAME: Entity::Entity (or BaseObject::BaseObject) with initialization flag
// Function address: 0x008da770
// Role: Constructor that calls base class initializer and optionally allocates/initializes a 0x1e0 byte buffer

undefined4 __thiscall Entity::Entity(Entity* this, byte initFlag)
{
    Entity::baseConstructor(this); // FUN_008da600 - base class initialization
    if ((initFlag & 1) != 0) {
        Entity::allocateBuffer(this, 0x1e0); // FUN_0043b960 - allocate or zero memory of size 0x1e0
    }
    return this;
}