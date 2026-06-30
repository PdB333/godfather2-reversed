// FUNC_NAME: GameObject::constructor
// Address: 0x0049ea00
// Role: Constructor with optional registration for the game object hierarchy

// Places a call to the base class constructor and optionally registers the object with a manager.
void * __thiscall GameObject::constructor(void *this, byte flags)
{
    // Call base constructor (FUN_0049e970)
    baseConstructor(this);

    // If bit 0 of flags is set, register this object with some manager (FUN_009c8eb0)
    if ((flags & 1) != 0) {
        registerWithManager(this);
    }

    return this;
}