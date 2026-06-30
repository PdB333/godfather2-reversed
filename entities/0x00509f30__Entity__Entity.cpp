// FUNC_NAME: Entity::Entity
// Address: 0x00509f30
// Role: Entity constructor with optional post-initialization.
// Calls base Object constructor, and if the low bit of flags is set, performs post-construction setup.

Entity* __thiscall Entity::Entity(Entity* this, byte flags)
{
    // Call base class (Object) constructor (original: FUN_00509d70)
    Object::Object(this);

    if ((flags & 1) != 0) {
        // Perform additional initialization, e.g., allocate dynamic memory or register with manager (original: FUN_009c8eb0)
        Entity::postConstruct(this);
    }

    return this;
}