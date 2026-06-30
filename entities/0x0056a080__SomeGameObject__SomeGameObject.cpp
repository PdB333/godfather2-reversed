// FUNC_NAME: SomeGameObject::SomeGameObject
// Address: 0x0056a080 - Constructor for a game object with optional extended initialization
// Call to base constructor at 0x0056a0a0
// If param_2 bit 0 is set, calls extended initialization at 0x009c8eb0 (likely placement new or additional setup)

__thiscall SomeGameObject::SomeGameObject(void *this, byte flags) {
    // Base class constructor (e.g. EARSObject or similar)
    SomeGameObjectBase::SomeGameObjectBase(); // 0x0056a0a0

    if ((flags & 1) != 0) {
        // Extended initialization (e.g. allocating resources, setting up child components)
        SomeGameObject::extendedInit(this); // 0x009c8eb0
    }

    return (undefined4)this;
}