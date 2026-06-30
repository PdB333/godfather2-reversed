// FUNC_NAME: Entity::constructor
Entity* __thiscall Entity::constructor(Entity* this, byte flags)
{
    // Call base class constructor (likely EARSObject or similar)
    baseConstructor(this); // FUN_0051f260

    // If bit 0 of flags is set, perform additional initialization
    if ((flags & 1) != 0) {
        additionalInit(this); // FUN_009c8eb0
    }

    return this;
}