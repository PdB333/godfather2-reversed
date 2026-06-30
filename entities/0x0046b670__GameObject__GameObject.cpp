// FUNC_NAME: GameObject::GameObject
// Address: 0x0046b670
// Role: Derived class constructor for a game object (e.g., Entity, Actor).
// Sets base vtable, calls base constructor (EARSObject), then sets derived vtable.
__thiscall void GameObject::GameObject(void* this) {
    // Set vtable to base class (EARSObject vtable at 0x00e3275c)
    *reinterpret_cast<void**>(this) = &PTR_FUN_00e3275c;
    // Call base constructor (EARSObject constructor at 0x0043e380)
    FUN_0043e380(this); // EARSObject::EARSObject
    // Set vtable to derived class (GameObject vtable at 0x00e30ea0)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00e30ea0;
}