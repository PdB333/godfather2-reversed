// FUNC_NAME: DerivedGameObject::DerivedGameObject
// Function at 0x0046a8d0: Constructor for a derived game object. Sets vtable to base (0x00e3269c), calls base constructor (0x0043e380), then overrides with own vtable (0x00e30ea0).
void __thiscall DerivedGameObject::DerivedGameObject(DerivedGameObject *this)
{
    // Set vtable pointer to base class (presumably NetObject or EARSObject)
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00e3269c);
    // Call base class constructor
    NetObject::NetObject(reinterpret_cast<NetObject*>(this));
    // Override with derived class vtable
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00e30ea0);
}