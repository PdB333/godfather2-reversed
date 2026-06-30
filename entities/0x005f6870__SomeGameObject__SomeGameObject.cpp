// FUNC_NAME: SomeGameObject::SomeGameObject
// Function address: 0x005f6870
// This is the constructor for SomeGameObject. It calls the base class constructor then conditionally
// invokes a cleanup/destruction routine based on the flag's bit 0 (likely related to heap allocation).

undefined4 __thiscall SomeGameObject::SomeGameObject(SomeGameObject* this, byte flag)
{
    // Call base class constructor (likely GameObjectBase at 0x005f68e0)
    GameObjectBase::GameObjectBase(this);
    // If bit 0 of flag is set, call a deletion or cleanup function (0x009c8eb0)
    if ((flag & 1) != 0) {
        SomeGameObject::deleteOrCleanup(this);
    }
    return this;  // Return the constructed object pointer
}