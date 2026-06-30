// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(Entity *this, byte isDynamic)
{
    // Base class constructor (at 0x004f0e80)
    baseClassConstructor(this);
    if (isDynamic & 1) {
        // Conditional cleanup/destructor (at 0x009c8eb0)
        cleanupFunction(this);
    }
    return (undefined4)this;
}